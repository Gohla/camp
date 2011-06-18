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


#ifndef CAMP_OPERATOR_HPP
#define CAMP_OPERATOR_HPP


#include <string>


namespace camp
{
/**
 * \brief Enumeration of operators supported by CAMP
 */
enum OperatorType
{
    noop,	    ///< No operator 
    add,        ///< Addition
    sub,        ///< Subtraction
    mul,        ///< Multiplication
    div,        ///< Division
    uplus,      ///< Unary plus
    umin,       ///< Unary minus
    mod,        ///< Modulo
    preinc,     ///< Pre increment
    postinc,    ///< Post increment
    predec,     ///< Pre decrementat
    postdec,    ///< Post decrementat
    eq,         ///< Equality
    neq,        ///< Non-equality
    lt,         ///< Less than
    lte,        ///< Lett than or equal
    gt,         ///< Greater than
    gte,        ///< Greater than or equals
    not,        ///< Logical not
    and,        ///< Logical and
    or          ///< Logical or
};

/**
 * \brief Returns a string representation of the given operator type
 *
 * \param type Operator type
 *
 * \return String representation of given operator type
 */
std::string operatorTypeName(OperatorType type);

} // namespace camp


#endif // CAMP_OPERATOR_HPP
