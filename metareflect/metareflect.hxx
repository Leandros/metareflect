/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */
#ifndef METAREFLECT_HXX
#define METAREFLECT_HXX
#pragma once

#include <stdint.h>
#include <string.h>
#include <stddef.h>

namespace metareflect
{

/* ========================================================================= */
/* Reflect Macros                                                            */
/* ========================================================================= */
#ifdef __METAREFLECT__
    #define CLASS(...) class __attribute__((annotate("reflect-class;" #__VA_ARGS__)))
    #define UNION(...) union __attribute__((annotate("reflect-class;" #__VA_ARGS__)))
    #define PROPERTY(...) __attribute__((annotate("reflect-property;" #__VA_ARGS__)))
    #define FUNCTION(...) __attribute__((annotate("reflect-function;" #__VA_ARGS__)))
    #define META_OBJECT
#else /* else __METAREFLECT__ */
    #define CLASS(...) class
    #define UNION(...) union
    #define PROPERTY(...)
    #define FUNCTION(...)
    #define META_OBJECT \
        template<class T> \
        friend constexpr bool AfterSerialize(T *) noexcept; \
        template<class T> \
        friend constexpr bool BeforeSerialize(T *) noexcept;
#endif /* __METAREFLECT__ */


/* ========================================================================= */
/* Traits                                                                    */
/* ========================================================================= */
template<class T>
struct IsSerializable;

template<class T>
struct HasBeforeSerialize;

template<class T>
struct HasAfterSerialize;

template<class T>
struct HasCustomSerialize;


/* ========================================================================= */
/* Public API                                                                */
/* ========================================================================= */
class Class;
class Type;

template<class T>
Type const *
GetType() noexcept;

template<class T>
Class const *
GetClass() noexcept;


/* ========================================================================= */
/* Serialization                                                             */
/* ========================================================================= */
template<class T, class Serializer>
struct Serialize;


/* ========================================================================= */
/* Helper Functions                                                          */
/* ========================================================================= */
template<class T, class Serializer>
constexpr bool
AfterSerialize(T *_this) noexcept
{
    if constexpr (HasAfterSerialize<T>::value)
        return _this->AfterSerialize();
    return true;
}

template<class T, class Serializer>
constexpr bool
BeforeSerialize(T *_this) noexcept
{
    if constexpr (HasBeforeSerialize<T>::value)
        return _this->BeforeSerialize();
    return true;
}

template<class T, class Serializer>
constexpr bool
CustomSerialize(T *_this) noexcept
{
    if constexpr (HasCustomSerialize<T>::value)
        return _this->Serialize();
    return true;
}

} /* namespace metareflect */

#endif /* METAREFLECT_HXX */


/* ========================================================================= */
/* Detail                                                                    */
/* ========================================================================= */
#include "metareflect_detail.hxx"
