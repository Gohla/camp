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

#ifndef CAMPTEST_OPERATOR_HPP
#define CAMPTEST_OPERATOR_HPP

#include <camp/camptype.hpp>
#include <camp/class.hpp>
#include <camp/operator.hpp>

namespace OperatorTest
{
    struct MyType
    {
        MyType(): m_number(0.0) {}
        MyType(float number): m_number(number) {}

        float m_number;
    };

    struct MyClass
    {
        MyClass(): m_number(0) {}
        MyClass(int number): m_number(number) {}

        MyClass operator+(const MyClass& rhs) const {return MyClass(m_number + rhs.m_number);}
        MyType operator+(const MyType& rhs) const {return MyType(m_number + rhs.m_number);}

        MyClass operator-(const MyClass& rhs) const {return MyClass(m_number - rhs.m_number);}

        MyClass operator*(const MyClass& rhs) const {return MyClass(m_number * rhs.m_number);}

        MyClass operator/(const MyClass& rhs) const {return MyClass(m_number / rhs.m_number);}

        MyClass operator-() const {return MyClass(-m_number);}

        int m_number;
    };

    void declare()
    {
        camp::Class::declare<MyType>("OperatorTest::MyType")
            .constructor1<float>()
            .property("number", &MyType::m_number);

        camp::Class::declare<MyClass>("OperatorTest::MyClass")
            .constructor1<int>()
            .property("number", &MyClass::m_number)
            .addOperator(camp::add, (MyClass(MyClass::*)(const MyClass&)const)&MyClass::operator+)
            .addOperator<camp::add, MyClass, const MyClass&>() // Test removal of duplicates
            .addOperator<camp::add, MyType, const MyType&>() // Test different types of same operators
            .addOperator<camp::sub, MyClass, const MyClass&>()
            .addOperator<camp::mul, MyClass, const MyClass&>()
            .addOperator<camp::div, MyClass, const MyClass&>()
            .addOperator<camp::umin, MyClass>();
    }
}

CAMP_AUTO_TYPE(OperatorTest::MyType, &OperatorTest::declare)
CAMP_AUTO_TYPE(OperatorTest::MyClass, &OperatorTest::declare)

#endif // CAMPTEST_OPERATOR_HPP
