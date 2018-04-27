#include <stdio.h>
// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/RecursiveASTVisitor.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

static llvm::cl::OptionCategory g_ToolCategory("metareflect options");


DeclarationMatcher const g_ReflectClassMatcher = cxxRecordDecl(decl().bind("id"), hasAttr(attr::Annotate));
DeclarationMatcher const g_PropertyMatcher = fieldDecl(decl().bind("id"), hasAttr(attr::Annotate));
DeclarationMatcher const g_FunctionMatcher = functionDecl(decl().bind("id"), hasAttr(attr::Annotate));

struct TypeVisitor : public RecursiveASTVisitor<TypeVisitor>
{
    explicit TypeVisitor(ASTContext *context)
        : m_context(context)
    {}

    bool VisitType(clang::Type *type)
    {
        m_leaf = type;
        return true;
    }

    ASTContext *m_context;
    clang::Type *m_leaf;
};

struct PropertyAnnotations {
    PropertyAnnotations()
        : serialized(false)
    {}

    bool serialized : 1;
};

struct FunctionAnnotations {
    FunctionAnnotations()
        : replicated(false)
    {}

    bool replicated : 1;
};

struct ReflectedClass {
    CXXRecordDecl const *record;
    std::vector<FieldDecl const *> fields;
    std::vector<FunctionDecl const *> functions;

    void 
    Generate(ASTContext *ctx, raw_ostream &os)
    {
        SmallString<64> str;
        SmallString<64> type;
        raw_svector_ostream stos(type);
        record->printQualifiedName(stos);
       
        /* File header: */
        os << "/* this file is generated. do not edit! */\n";
        os << "#pragma once\n";
        os << "#include <metareflect.hxx>\n";
        os << "namespace metareflect\n{\n\n";

        SmallVector<PropertyAnnotations, 8> propertyAnnotations;
        SmallVector<FunctionAnnotations, 8> functionAnnotations;

        /* Verify CLASS annotation. */
        for (auto &attr : record->attrs()) {
            if (attr->getKind() == attr::Annotate) {
                auto ref = GetAnnotations(attr, str);
                assert(ref.startswith("reflect-class") && "incorrect annotation");
            }
        }
                
        /* Generate PROPERTY annotations. */
        for (auto &field : fields) {
            Attr *attr = GetAnnotateAttr(field);
            assert(attr != nullptr);
            propertyAnnotations.push_back(
                GenerateFieldAttributes(GetAnnotations(attr, str)));
        }

        /* Generate FUNCTION annotations. */
        for (auto &func : functions) {
            Attr *attr = GetAnnotateAttr(func);
            assert(attr != nullptr);
            functionAnnotations.push_back(
                GenerateFunctionAttributes(GetAnnotations(attr, str)));
        }

        /* Mark class as serializable if one or more fields are serialized. */
        bool isSerializable = std::any_of(
            propertyAnnotations.begin(), 
            propertyAnnotations.end(), 
            [](auto &v) { return v.serialized; });
        os << "template<> struct IsSerializable<" 
            << type 
            << "> { static constexpr bool value = "
            << (isSerializable ? "true" : "false")
            << "; };\n";

        os << "template<> struct HasBeforeSerialize<" 
            << type 
            << "> { static constexpr bool value = "
            << (HasFunctionOfName("BeforeSerialize") ? "true" : "false")
            << "; };\n";

        os << "template<> struct HasAfterSerialize<" 
            << type 
            << "> { static constexpr bool value = "
            << (HasFunctionOfName("AfterSerialize") ? "true" : "false")
            << "; };\n";

        os << "template<> struct HasCustomSerialize<" 
            << type 
            << "> { static constexpr bool value = "
            << (HasFunctionOfName("Serialize") ? "true" : "false")
            << "; };\n";

        os << "\n";
        os << "template<>\n"
            << "detail::ClassStorage<" 
                << fields.size() 
                << ", " 
                << functions.size() << ">"
            << "::ClassStorage() noexcept\n";
        os << "{\n";

        /* Fields */
        int i = 0;
        SmallString<64> fname;
        raw_svector_ostream fname_os(fname);
        SmallString<64> tname;
        raw_svector_ostream tname_os(tname);
        for (auto &field : fields) {
            fname.clear();
            tname.clear();
            field->printName(fname_os);
            GetRealTypeName(ctx, field->getType(), tname_os);

            os << "/* Field " << (i + 1) << " */\n";
            os << "static Type type" << i << "(sizeof(" << tname << "), Hash(\"" << tname << "\"));\n";
            os << "fields[" << i << "].m_type = &type" << i << ";\n";
            os << "fields[" << i << "].m_flags = 0/* TODO */;\n";
            os << "fields[" << i << "].m_serializedWidth = 0/* TODO */;\n";
            os << "fields[" << i << "].m_offset = offsetof(" << type << ", " << fname << ");\n";
            os << "fields[" << i << "].m_qualifier = " << GenerateQualifier(ctx, field->getType()) << ";\n";
            i++;
        }

        /* Functions */
        i = 0;
        for (auto &func : functions) {
            fname.clear();
            tname.clear();

            GetRealTypeName(ctx, func->getReturnType(), tname_os);
            os << "/* Function " << (i + 1) << "*/\n";
            os << "static Type functionRetType" << i << "(sizeof(" << tname << "), Hash(\"" << tname << "\"));\n";
            os << "static FunctionReturn functionRet" << i << ";\n";
            os << "functionRet" << i << ".m_type = &functionRetType" << i << ";\n";
            os << "functionRet" << i << ".m_flags = 0/*TODO*/;\n";
            os << "functionRet" << i << ".m_serializedWidth = 0/*TODO*/;\n";
            os << "functionRet" << i << ".m_qualifier = " << GenerateQualifier(ctx, func->getReturnType()) << ";\n";
            os << "\n";
            os << "static FunctionParameter functionParameters" << i << "[" << std::max(func->getNumParams(), 1u) << "];\n";
            for (int j = 0, n = func->getNumParams(); j < n; ++j) {
                clang::ParmVarDecl const *param = func->getParamDecl(j);
                tname.clear();
                GetRealTypeName(ctx, param->getOriginalType(), tname_os);
                os << "static Type functionParameterType" << i << j << "(sizeof(" << tname << "), Hash(\"" << tname << "\"));\n";
                os << "functionParameters" << i << "[" << j << "].m_type = &functionParameterType" << i << j << ";\n";
                os << "functionParameters" << i << "[" << j << "].m_flags = 0/*TODO*/;\n";
                os << "functionParameters" << i << "[" << j << "].m_serializedWidth = 0/*TODO*/;\n";
                os << "functionParameters" << i << "[" << j << "].m_qualifier = " << GenerateQualifier(ctx, param->getOriginalType()) << ";\n";
            }

            os << "functions[" << i << "].m_returnType = &functionRet" << i << ";\n";
            os << "functions[" << i << "].m_parameters = &functionParameters" << i << "[0];\n";
            os << "functions[" << i << "].m_parametersEnd = &functionParameters" << i << "[" << func->getNumParams() << "];\n";
            os << "functions[" << i << "].m_flags = 0/*TODO*/;\n";

            i++;
        }
        
        os << "}\n";

        /* GetClass Function */
        os << "template<>\n";
        os << "Class const *\n";
        os << "GetClass<" << type << ">() noexcept\n";
        os << "{\n";
            os << "static detail::ClassStorage<"
                << fields.size() 
                << ", " 
                << functions.size() << ">"
                << " reflected;\n";
            os << "static Class cache(\n"
                << "sizeof(" << type << "),\n"
                << "Hash(\"" << type << "\"),\n"
                << "nullptr/*TODO: baseclass*/,\n"
                << "reflected.fields,\n"
                << "reflected.fields + reflected.numFields,\n"
                << "reflected.functions,\n"
                << "reflected.functions + reflected.numFunctions);\n";
            os << "return &cache;\n";
        os << "}\n";

        os << "\n} /* namespace metareflect */\n\n";
    }

    /* ===--------------------------------------------------=== */
    /* Helper                                                   */                        
    /* ===--------------------------------------------------=== */
private:
    template<class T>
    Attr *
    GetAnnotateAttr(T *decl)
    {
        for (auto &attr : decl->attrs()) {
            if (attr->getKind() == attr::Annotate) {
                return attr;
            }
        }

        return nullptr;
    }

    template<size_t N>
    StringRef
    GetAnnotations(Attr const *attr, SmallString<N> &str)
    {
        str.clear();
        raw_svector_ostream os(str);
        LangOptions langopts;
        PrintingPolicy policy(langopts);
        attr->printPretty(os, policy);
        return str.slice(26, str.size() - 4);
    }

    template<class Lambda>
    bool
    ForEachProperty(StringRef const &annotations, Lambda &&lambda)
    {
        int j = 0;
        for (int i = 0, n = annotations.size(); i < n; ++i) {
            if (annotations[i] == ',') {
                if (!lambda(annotations.slice(j, i - 1)))
                    return false;
                j = i + 1;
            }
        }

        if (!lambda(annotations.slice(j, annotations.size())))
            return false;
        return true;
    }

    bool
    HasFunctionOfName(char const *name)
    {
        SmallString<64> str;
        return std::any_of(
            functions.begin(),
            functions.end(),
            [&str, &name](auto &v) { 
                str.clear();
                raw_svector_ostream fos(str);
                v->printName(fos);
                return str == name;
            });
    }

    SmallString<32>
    GenerateQualifier(ASTContext *ctx, QualType type)
    {
        clang::Type const *t = type.getTypePtrOrNull();

        /* CV Qualifier: */
        int cvQual = 0;
        if (type.isConstant(*ctx))
            cvQual |= 0x1;
        if (type.isVolatileQualified())
            cvQual |= 0x2;

        /* RefQualifier: */
        int refQual = 0;
        if (t->isLValueReferenceType())
            refQual = 1;
        if (t->isRValueReferenceType())
            refQual = 2;

        /* StorageClass: */
        int storageClass = 0;
        /* TODO: Implement! */

        /* Pointer detection: */
        int isPointer = t->isPointerType();

        /* Array detection: */
        int isArray = t->isArrayType();
        int arrayLen = 0;
        if (isArray) {
            clang::ArrayType const *arr = t->getAsArrayTypeUnsafe();
        }

        SmallString<32> out;
        raw_svector_ostream os(out);
        os << "Qualifier(" 
            << cvQual << ", " 
            << refQual << ", " 
            << storageClass << ", "
            << isPointer << ", "
            << isArray << ", "
            << arrayLen << ")";
        return out;
    }

    void
    GetRealTypeName(ASTContext *ctx, QualType t, raw_ostream &os)
    {
        TypeVisitor v{ctx};
        v.TraverseType(t);
        clang::Type const *type = v.m_leaf->getUnqualifiedDesugaredType();
        QualType retType(type, 0);
        retType.print(os, ctx->getPrintingPolicy());
    }

    /* ===--------------------------------------------------=== */
    /* Generate Annotations                                     */
    /* ===--------------------------------------------------=== */
    PropertyAnnotations
    GenerateFieldAttributes(StringRef const &attr)
    {
        assert(attr.startswith("reflect-property") && "incorrect annotation");
        auto pair = attr.split(";");

        PropertyAnnotations ret;
        auto setAttributes = [&ret](StringRef const &s) -> bool
        {
            if (s.equals_lower("serialized")) {
                return (ret.serialized = true);
            }

            return false;
        };

        if (!ForEachProperty(pair.second, setAttributes))
            return PropertyAnnotations{};
        return ret;
    }

    FunctionAnnotations
    GenerateFunctionAttributes(StringRef const &attr)
    {
        assert(attr.startswith("reflect-function") && "incorrect annotation");
        auto pair = attr.split(";");

        FunctionAnnotations ret;
        auto setAttributes = [&ret](StringRef const &s) -> bool
        {
            if (s.equals_lower("replicated")) {
                return (ret.replicated = true);
            }

            return false;
        };

        if (!ForEachProperty(pair.second, setAttributes))
            return FunctionAnnotations{};
        return ret;
    }
};


class ClassFinder : public MatchFinder::MatchCallback
{
public:
    virtual void 
    run(MatchFinder::MatchResult const &result) override
    {
        m_context = result.Context;
        m_sourceman = result.SourceManager;
        CXXRecordDecl const *record = result.Nodes.getNodeAs<clang::CXXRecordDecl>("id");
        if (record)
            return FoundRecord(record);

        FieldDecl const *field = result.Nodes.getNodeAs<clang::FieldDecl>("id");
        if (field)
            return FoundField(field);

        FunctionDecl const *function = result.Nodes.getNodeAs<clang::FunctionDecl>("id");
        if (function)
            return FoundFunction(function);
    }

    virtual void
    onStartOfTranslationUnit() override
    {
    }

    virtual void
    onEndOfTranslationUnit() override
    {
        raw_fd_ostream os(1, false);
        for (auto &ref : m_classes)
            ref.Generate(m_context, os);
    }

protected:
    void
    FoundRecord(CXXRecordDecl const *record)
    {
        ReflectedClass rec;
        rec.record = record;
        m_classes.push_back(rec);
    }

    void
    FoundField(FieldDecl const *field)
    {
        m_classes.back().fields.push_back(field);
    }

    void
    FoundFunction(FunctionDecl const *function)
    {
        m_classes.back().functions.push_back(function);
    }

protected:
    ASTContext *m_context;
    SourceManager *m_sourceman;
    std::vector<ReflectedClass> m_classes;
};


/* I HATE std::string !!! */
inline bool 
ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


int main(int argc, const char **argv) 
{
    /* Parse command-line options. */
    CommonOptionsParser optionsParser(argc, argv, g_ToolCategory);
    ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

    /* Create all the generated headers already. */
    for (auto &path : optionsParser.getSourcePathList()) {
        /* TODO: Get path prefix from command line. */
        assert(ends_with(path, ".hxx") && "can only be run on header files");
        SmallString<64> name;
        name.append(path);
        for (int i = 0; i < 4; ++i)
            name.pop_back();
        name.append(".generated.hxx");
        FILE *f = fopen(name.c_str(), "wb");
        fclose(f);
    }

    /* Find all reflected classes. */
    ClassFinder classFinder;
    MatchFinder finder;
    finder.addMatcher(g_ReflectClassMatcher, &classFinder);
    finder.addMatcher(g_PropertyMatcher, &classFinder);
    finder.addMatcher(g_FunctionMatcher, &classFinder);

    return tool.run(newFrontendActionFactory(&finder).get());
}
