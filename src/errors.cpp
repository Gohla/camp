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


#include <camp/errors.hpp>
#include <camp/class.hpp>


namespace camp
{
//-------------------------------------------------------------------------------------------------
BadType::BadType(TypeInfo provided, TypeInfo expected)
    : Error("value of type " + provided.apply_visitor(TypeToString()) + " couldn't be converted to type " + 
            expected.apply_visitor(TypeToString()))
{
}

//-------------------------------------------------------------------------------------------------
BadType::BadType(const std::string& message)
    : Error(message)
{
}

//-------------------------------------------------------------------------------------------------
BadArgument::BadArgument(TypeInfo provided, TypeInfo expected, std::size_t index, const std::string& functionName)
    : BadType("the argument #" + str(index) + " of function " + functionName +
              " couldn't be converted from type " + provided.apply_visitor(TypeToString()) + 
              " to type " + expected.apply_visitor(TypeToString()))
{
}

//-------------------------------------------------------------------------------------------------
ClassAlreadyCreated::ClassAlreadyCreated(const std::string& name, const std::string& type)
    : Error("a metaclass named " + name + ", or bound to the type " + type + " already exists")
{
}

//-------------------------------------------------------------------------------------------------
ClassNotFound::ClassNotFound(const std::string& name)
    : Error("the metaclass " + name + " couldn't be found")
{
}

//-------------------------------------------------------------------------------------------------
ClassUnrelated::ClassUnrelated(const std::string& sourceClass, const std::string& requestedClass)
    : Error("failed to convert from " + sourceClass + " to " + requestedClass + ": it is not a base nor a derived")
{
}

//-------------------------------------------------------------------------------------------------
EnumAlreadyCreated::EnumAlreadyCreated(const std::string& name, const std::string& type)
    : Error("a metaenum named " + name + ", or bound to the type " + type + " already exists")
{
}

//-------------------------------------------------------------------------------------------------
EnumNameNotFound::EnumNameNotFound(const std::string& name, const std::string& enumName)
    : Error("the value " + name + " couldn't be found in metaenum " + enumName)
{
}

//-------------------------------------------------------------------------------------------------
EnumNotFound::EnumNotFound(const std::string& name)
    : Error("the metaenum " + name + " couldn't be found")
{
}

//-------------------------------------------------------------------------------------------------
EnumValueNotFound::EnumValueNotFound(long value, const std::string& enumName)
    : Error("the value " + str(value) + " couldn't be found in metaenum " + enumName)
{
}

//-------------------------------------------------------------------------------------------------
ForbiddenCall::ForbiddenCall(const std::string& functionName)
    : Error("the function " + functionName + " is not callable")
{
}

//-------------------------------------------------------------------------------------------------
ForbiddenRead::ForbiddenRead(const std::string& propertyName)
    : Error("the property " + propertyName + " is not readable")
{
}

//-------------------------------------------------------------------------------------------------
ForbiddenWrite::ForbiddenWrite(const std::string& propertyName)
    : Error("the property " + propertyName + " is not writable")
{
}

//-------------------------------------------------------------------------------------------------
FunctionNotFound::FunctionNotFound(const std::string& name, const std::string& className)
    : Error("the function " + name + " couldn't be found in metaclass " + className)
{
}

//-------------------------------------------------------------------------------------------------
OperatorNotFound::OperatorNotFound(OperatorType operatorType, TypeInfo argType, const std::string& className)
    : Error("the operator " + operatorTypeName(operatorType) + " with argument type " + 
            argType.apply_visitor(TypeToString()) + " couldn't be found in metaclass " + className)
{
}

//-------------------------------------------------------------------------------------------------
OperatorNotFound::OperatorNotFound(OperatorType operatorType, const std::string& className)
    : Error("the unary operator " + operatorTypeName(operatorType) + " couldn't be found in metaclass " + className)
{
}

//-------------------------------------------------------------------------------------------------
NotEnoughArguments::NotEnoughArguments(const std::string& functionName, std::size_t provided, std::size_t expected)
    : Error("not enough arguments for calling " + functionName + " - provided " + str(provided) + ", expected " + str(expected))
{
}

//-------------------------------------------------------------------------------------------------
NullObject::NullObject(const Class* objectClass)
    : Error("trying to use a null metaobject of class " + (objectClass ? objectClass->name() : "unknown"))
{
}

//-------------------------------------------------------------------------------------------------
OutOfRange::OutOfRange(std::size_t index, std::size_t size)
    : Error("the index (" + str(index) + ") is out of the allowed range [0, " + str(size - 1) + "]")
{
}

//-------------------------------------------------------------------------------------------------
ElementNotFound::ElementNotFound()
: Error("the element has not been found")
{
}


//-------------------------------------------------------------------------------------------------
PropertyNotFound::PropertyNotFound(const std::string& name, const std::string& className)
    : Error("the property " + name + " couldn't be found in metaclass " + className)
{
}

} // namespace camp
