set(LLVM_LINK_COMPONENTS Support)

add_clang_executable(metareflect
    reflect.cpp
    reflectedclass.cpp
    annotations.hpp
    classfinder.hpp
    reflectedclass.hpp
    utils.hpp
    utils.cpp
)

target_link_libraries(metareflect
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)

