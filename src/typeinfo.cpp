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


#include <camp/typeinfo.hpp>
#include <camp/enum.hpp>
#include <camp/class.hpp>


namespace camp
{
//-------------------------------------------------------------------------------------------------
ArrayType::ArrayType(TypeInfo elementTypeInfo)
    : m_elementType(elementTypeInfo)
{

}

//-------------------------------------------------------------------------------------------------
camp::TypeInfo ArrayType::elements() const
{
    return m_elementType;
}

//-------------------------------------------------------------------------------------------------
bool ArrayType::operator==(const ArrayType& other) const
{
    return m_elementType == other.m_elementType;
}

//-------------------------------------------------------------------------------------------------
bool ArrayType::operator!=(const ArrayType& other) const
{
    return !ArrayType::operator==(other);
}

//-------------------------------------------------------------------------------------------------
bool ArrayType::operator<(const ArrayType& other) const
{
    return m_elementType < other.m_elementType;
}

//-------------------------------------------------------------------------------------------------
DictionaryType::DictionaryType(TypeInfo keyTypeInfo, TypeInfo elementTypeInfo)
    : m_keyType(keyTypeInfo)
    , m_elementType(elementTypeInfo)
{

}

//-------------------------------------------------------------------------------------------------
TypeInfo DictionaryType::keys() const
{
    return m_keyType;
}

//-------------------------------------------------------------------------------------------------
TypeInfo DictionaryType::elements() const
{
    return m_elementType;
}

//-------------------------------------------------------------------------------------------------
bool DictionaryType::operator==(const DictionaryType& other) const
{
    return m_keyType == other.m_keyType && m_elementType == other.m_elementType;
}

//-------------------------------------------------------------------------------------------------
bool DictionaryType::operator!=(const DictionaryType& other) const
{
    return !DictionaryType::operator==(other);
}

//-------------------------------------------------------------------------------------------------
bool DictionaryType::operator<(const DictionaryType& other) const
{
    return m_keyType < other.m_keyType || !( other.m_keyType < m_keyType) 
        && m_elementType < other.m_elementType;
}

//-------------------------------------------------------------------------------------------------
std::string TypeToString::operator()( camp::Type type )
{
    switch(type)
    {
        case noType:            return "Void";
        case boolType:          return "Boolean";
        case intType:           return "Integer";
        case realType:          return "Real";
        case stringType:        return "String";
        case enumType:          return "Enum";
        case arrayType:         return "Array";
        case dictionaryType:    return "Dictionary";
        case valueType:         return "Value";
        case userType:          return "User";
    }
    return "Unknown";
}

//-------------------------------------------------------------------------------------------------
std::string TypeToString::operator()( const camp::Enum* metaenum )
{
    return metaenum->name();
}

//-------------------------------------------------------------------------------------------------
std::string TypeToString::operator()( const camp::Class* metaclass )
{
    return metaclass->name();
}

//-------------------------------------------------------------------------------------------------
std::string TypeToString::operator()( camp::ArrayType type )
{
    return "Array<" + type.elements().apply_visitor(TypeToString()) + ">";
}

//-------------------------------------------------------------------------------------------------
std::string TypeToString::operator()( camp::DictionaryType type )
{
    return "Dictionary<" + type.keys().apply_visitor(TypeToString()) + ", "
        + type.elements().apply_visitor(TypeToString()) + ">";
}

} // namespace camp
