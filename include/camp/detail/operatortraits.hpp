/****************************************************************************
**
** Copyright (C) 2009-2010 TECHNOGERMA Systems France and/or its subsidiary(-ies).
** Contact: Technogerma Systems France Information (contact@technogerma.fr)
**
** This file is part of the CAMP library.
**
** CAMP is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** CAMP is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with CAMP.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/


#ifndef CAMP_OPERATORTRAITS_HPP
#define CAMP_OPERATORTRAITS_HPP


#include <camp/operator.hpp>


namespace camp
{
namespace detail
{
/**
 * \class OperatorFunction4
 *
 * \brief Helper structure to generate signatures and function pointers for operators.
 */

/**
 * General case with separate return and argument types, Op template parameter must be specialized
 */
template <OperatorType Op, typename T, typename R, typename A>
struct OperatorFunction4;

/**
 * Specialization for addition operator
 */
template <typename T, typename R, typename A>
struct OperatorFunction4<camp::add, T, R, A>
{
    typedef R (T::*Signature)(A) const;
    static Signature op() {return static_cast<R(T::*)(A)const>(&T::operator+);}
};

/**
 * Specialization for subtraction operator
 */
template <typename T, typename R, typename A>
struct OperatorFunction4<camp::sub, T, R, A>
{
    typedef R (T::*Signature)(A) const;
    static Signature op() {return static_cast<R(T::*)(A)const>(&T::operator-);}
};

/**
 * Specialization for multiplication operator
 */
template <typename T, typename R, typename A>
struct OperatorFunction4<camp::mul, T, R, A>
{
    typedef R (T::*Signature)(A) const;
    static Signature op() {return static_cast<R(T::*)(A)const>(&T::operator*);}
};

/**
 * Specialization for division operator
 */
template <typename T, typename R, typename A>
struct OperatorFunction4<camp::div, T, R, A>
{
    typedef R (T::*Signature)(A) const;
    static Signature op() {return static_cast<R(T::*)(A)const>(&T::operator/);}
};

/**
 * Specialization for modulo operator
 */
template <typename T, typename R, typename A>
struct OperatorFunction4<camp::mod, T, R, A>
{
    typedef R (T::*Signature)(A) const;
    static Signature op() {return static_cast<R(T::*)(A)const>(&T::operator%);}
};

/**
 * \class OperatorFunction3
 *
 * \brief Helper structure to generate signatures and function pointers for operators.
 */

/**
 * General case with return or argument type, Op template parameter must be specialized
 */
template <OperatorType Op, typename T, typename ROrA>
struct OperatorFunction3;

/**
 * Specialization for equality operator
 */
template <typename T, typename A>
struct OperatorFunction3<camp::eq, T, A>
{
    typedef bool (T::*Signature)(A) const;
    static Signature op() {return static_cast<bool(T::*)(A)const>(&T::operator==);}
};

/**
 * Specialization for non-equality operator
 */
template <typename T, typename A>
struct OperatorFunction3<camp::neq, T, A>
{
    typedef bool (T::*Signature)(A) const;
    static Signature op() {return static_cast<bool(T::*)(A)const>(&T::operator!=);}
};

/**
 * Specialization for less than operator
 */
template <typename T, typename A>
struct OperatorFunction3<camp::lt, T, A>
{
    typedef bool (T::*Signature)(A) const;
    static Signature op() {return static_cast<bool(T::*)(A)const>(&T::operator<);}
};

/**
 * Specialization for less than or equals operator
 */
template <typename T, typename A>
struct OperatorFunction3<camp::lte, T, A>
{
    typedef bool (T::*Signature)(A) const;
    static Signature op() {return static_cast<bool(T::*)(A)const>(&T::operator<=);}
};

/**
 * Specialization for greater than operator
 */
template <typename T, typename A>
struct OperatorFunction3<camp::gt, T, A>
{
    typedef bool (T::*Signature)(A) const;
    static Signature op() {return static_cast<bool(T::*)(A)const>(&T::operator>);}
};

/**
 * Specialization for greater than or equals operator
 */
template <typename T, typename A>
struct OperatorFunction3<camp::gte, T, A>
{
    typedef bool (T::*Signature)(A) const;
    static Signature op() {return static_cast<bool(T::*)(A)const>(&T::operator>=);}
};

/**
 * Specialization for unary minus operator
 */
template <typename T, typename R>
struct OperatorFunction3<camp::umin, T, R>
{
    typedef R (T::*Signature)(void) const;
    static Signature op() {return static_cast<R(T::*)(void)const>(&T::operator-);}
};

} // namespace detail

} // namespace camp


#endif // CAMP_OPERATORTRAITS_HPP
