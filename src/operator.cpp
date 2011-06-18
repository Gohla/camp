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


#include <camp/operator.hpp>


namespace camp
{
//-------------------------------------------------------------------------------------------------
std::string operatorTypeName( OperatorType type )
{
    switch(type)
    {
        case noop: return "noop";
        case add: return "add";
        case sub: return "sub";
        case mul: return "mult";
        case div: return "div";
        case uplus: return "uplus";
        case umin: return "umin";
        case mod: return "mod";
        case preinc: return "preinc";
        case postinc: return "postinc";
        case predec: return "predec";
        case postdec: return "postdec";
        case eq: return "eq";
        case neq: return "neq";
        case lt: return "lt";
        case lte: return "lte";
        case gt: return "gt";
        case gte: return "gte";
        case not: return "not";
        case and: return "and";
        case or: return "or";
    }
    return "unknown";
}

} // namespace camp
