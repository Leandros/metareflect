/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */

#ifndef METAREFLECT_CLASSFINDER_HPP
#define METAREFLECT_CLASSFINDER_HPP
#pragma once

#include "utils.hpp"
#include "reflectedclass.hpp"


class ClassFinder : public MatchFinder::MatchCallback
{
public:
    virtual void
    run(MatchFinder::MatchResult const &result) override
    {
        m_context = result.Context;
        m_sourceman = result.SourceManager;

        CXXRecordDecl const *record =
            result.Nodes.getNodeAs<clang::CXXRecordDecl>("id");
        if (record)
            return FoundRecord(record);

        FieldDecl const *field = result.Nodes.getNodeAs<clang::FieldDecl>("id");
        if (field)
            return FoundField(field);

        FunctionDecl const *function =
            result.Nodes.getNodeAs<clang::FunctionDecl>("id");
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
        /* For stdout output. */
        /* raw_fd_ostream os(1, false); */
        std::error_code ec;
        raw_fd_ostream os(m_fileName, ec);
        assert(!ec && "error opening file");
        for (auto &ref : m_classes)
            ref.Generate(m_context, os);
    }


protected:
    void
    FoundRecord(CXXRecordDecl const *record)
    {
        m_fileName = m_sourceman->getFilename(record->getLocation());
        m_fileName.erase(m_fileName.end() - 4, m_fileName.end());
        m_fileName.append(".generated.hxx");
        m_classes.emplace_back(ReflectedClass(record));
    }

    void
    FoundField(FieldDecl const *field)
    {
        m_classes.back().AddField(field);
    }

    void
    FoundFunction(FunctionDecl const *function)
    {
        m_classes.back().AddFunction(function);
    }

protected:
    ASTContext *m_context;
    SourceManager *m_sourceman;
    std::vector<ReflectedClass> m_classes;
    std::string m_fileName;
};

#endif /* METAREFLECT_CLASSFINDER_HPP */

