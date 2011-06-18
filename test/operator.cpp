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

#include "operator.hpp"
#include <boost/test/unit_test.hpp>

using namespace OperatorTest;

//-----------------------------------------------------------------------------
struct OperatorFixture
{
    OperatorFixture() : myClass(camp::classByType<MyClass>()) {}
    const camp::Class& myClass;
};

//-----------------------------------------------------------------------------
//                         Tests for operators
//-----------------------------------------------------------------------------
BOOST_FIXTURE_TEST_SUITE(OPERATOR, OperatorFixture)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(operatorCount)
{
    BOOST_CHECK_EQUAL(myClass.operatorCount(), 6);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(hasOperator)
{
    BOOST_CHECK(myClass.hasOperator(camp::add, camp::classByTypeSafe<MyClass>()));
    BOOST_CHECK(myClass.hasOperator(camp::add, camp::classByTypeSafe<MyType>()));
    BOOST_CHECK(!myClass.hasOperator(camp::add, camp::intType));
    BOOST_CHECK(myClass.hasOperator(camp::add));
    BOOST_CHECK(myClass.hasOperator(camp::sub, camp::classByTypeSafe<MyClass>()));
    BOOST_CHECK(!myClass.hasOperator(camp::sub, camp::intType));
    BOOST_CHECK(myClass.hasOperator(camp::sub));
    BOOST_CHECK(myClass.hasOperator(camp::mul, camp::classByTypeSafe<MyClass>()));
    BOOST_CHECK(!myClass.hasOperator(camp::mul, camp::intType));
    BOOST_CHECK(myClass.hasOperator(camp::mul));
    BOOST_CHECK(myClass.hasOperator(camp::div, camp::classByTypeSafe<MyClass>()));
    BOOST_CHECK(!myClass.hasOperator(camp::div, camp::intType));
    BOOST_CHECK(myClass.hasOperator(camp::div));
    BOOST_CHECK(myClass.hasOperator(camp::umin, camp::noType));
    BOOST_CHECK(myClass.hasOperator(camp::umin));
    BOOST_CHECK(!myClass.hasOperator(camp::umin, camp::intType));
}

BOOST_AUTO_TEST_SUITE_END()
