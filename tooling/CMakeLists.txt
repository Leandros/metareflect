set(LLVM_LINK_COMPONENTS Support)

add_clang_executable(metareflect
    reflect.cpp
)

target_link_libraries(metareflect
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)

