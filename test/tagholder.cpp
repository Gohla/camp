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

#include "tagholder.hpp"
#include <camp/classget.hpp>
#include <camp/errors.hpp>
#include <boost/test/unit_test.hpp>

using namespace TagHolderTest;

//-----------------------------------------------------------------------------
struct TagHolderFixture
{
    TagHolderFixture()
    {
        metaclass = &camp::classByType<MyClass>();
    }

    const camp::Class* metaclass;
};

//-----------------------------------------------------------------------------
//                         Tests for camp::TagHolder
//-----------------------------------------------------------------------------
BOOST_FIXTURE_TEST_SUITE(TAGHOLDER, TagHolderFixture)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(declare)
{
    BOOST_CHECK_EQUAL(metaclass->tagCount(), 16);
    BOOST_CHECK_EQUAL(metaclass->property("prop").tagCount(), 2);
    BOOST_CHECK_EQUAL(metaclass->function("func").tagCount(), 2);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(get)
{
    BOOST_CHECK_EQUAL(metaclass->hasTag("a"), true);
    BOOST_CHECK_EQUAL(metaclass->hasTag("b"), true);
    BOOST_CHECK_EQUAL(metaclass->hasTag("x"), false);

    BOOST_CHECK_NO_THROW(metaclass->tagId(0));
    BOOST_CHECK_NO_THROW(metaclass->tagId(1));
    BOOST_CHECK_THROW(metaclass->tagId(100), camp::OutOfRange);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(staticTags)
{
    BOOST_CHECK_EQUAL(metaclass->hasTag(true),    true);
    BOOST_CHECK_EQUAL(metaclass->hasTag(10),      true);
    BOOST_CHECK_EQUAL(metaclass->hasTag(5.25),    true);
    BOOST_CHECK_EQUAL(metaclass->hasTag("hello"), true);
    BOOST_CHECK_EQUAL(metaclass->hasTag(Ten),     true);
    BOOST_CHECK_EQUAL(metaclass->hasTag(object1), true);

    BOOST_CHECK_EQUAL(metaclass->hasTag(false),   false);
    BOOST_CHECK_EQUAL(metaclass->hasTag(20),      false);
    BOOST_CHECK_EQUAL(metaclass->hasTag(8.78),    false);
    BOOST_CHECK_EQUAL(metaclass->hasTag("hi"),    false);
    BOOST_CHECK_EQUAL(metaclass->hasTag(One),     false);
    BOOST_CHECK_EQUAL(metaclass->hasTag(object2), false);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(staticValues)
{
    BOOST_CHECK_EQUAL(metaclass->tag("static1"), camp::Value(true));
    BOOST_CHECK_EQUAL(metaclass->tag("static2"), camp::Value(10));
    BOOST_CHECK_EQUAL(metaclass->tag("static3"), camp::Value(5.25));
    BOOST_CHECK_EQUAL(metaclass->tag("static4"), camp::Value("hello"));
    BOOST_CHECK_EQUAL(metaclass->tag("static5"), camp::Value(Ten));
    BOOST_CHECK_EQUAL(metaclass->tag("static6"), camp::Value(object1));
    BOOST_CHECK_EQUAL(metaclass->tag("xxxxxxx"), camp::Value::nothing);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(dynamicValues)
{
    BOOST_CHECK_EQUAL(metaclass->tag("dynamic1", MyClass(10)), camp::Value(10));
    BOOST_CHECK_EQUAL(metaclass->tag("dynamic2", MyClass(10)), camp::Value("func"));
}

BOOST_AUTO_TEST_SUITE_END()
