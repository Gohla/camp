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


#include <camp-lua/valuetoluavisitor.hpp>
#include <camp-lua/callback.hpp>
#include <camp-lua/lua.hpp>
#include <camp/class.hpp>
#include <camp/operator.hpp>

namespace camp
{
namespace lua
{

ValueToLuaVisitor::ValueToLuaVisitor(lua_State* L, bool constructed /*= false*/)
    : m_L(L)
    , m_Constructed(constructed)
{

}

void ValueToLuaVisitor::operator()(camp::NoType value)
{
    // TODO
}

void ValueToLuaVisitor::operator()(bool value)
{
    lua_pushboolean(m_L, value);
}

void ValueToLuaVisitor::operator()(long value)
{
    lua_pushinteger(m_L, value);
}

void ValueToLuaVisitor::operator()(double value)
{
    lua_pushnumber(m_L, value);
}

void ValueToLuaVisitor::operator()(const std::string& value)
{
    lua_pushstring(m_L, value.c_str());
}

void ValueToLuaVisitor::operator()(const camp::EnumObject& value)
{
    lua_pushnumber(m_L, value.value());
}

void ValueToLuaVisitor::operator()(const camp::UserObject& value)
{
    // Create a userdata to hold the user object
    camp::UserObject* userdata = static_cast<camp::UserObject*>(lua_newuserdata(m_L, sizeof(camp::UserObject)));
    new (userdata) camp::UserObject(value); // Call the placement 'new' operator

    // Try to get the metatable corresponding to the metaclass from the Lua registry
    const camp::Class& metaclass = userdata->getClass();
    std::string key = "camp-lua/";
    key += metaclass.name();
    if (luaL_newmetatable(m_L, key.c_str()))
    {
        // A new metatable has been created as the metaclass has not been published previously

        // Set the __index event to call the indexCallback function
        lua_pushstring(m_L, "__index");
        lua_pushcfunction(m_L, &indexCallback);
        lua_rawset(m_L, -3);

        // Set the __newindex event to call the newIndexCallback function
        lua_pushstring(m_L, "__newindex");
        lua_pushcfunction(m_L, &newIndexCallback);
        lua_rawset(m_L, -3);

        if(metaclass.hasOperator(camp::add))
        {
            // Set the __add event to call the operatorCallback function
            lua_pushstring(m_L, "__add");
            lua_pushcfunction(m_L, &operatorCallback<camp::add>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::sub))
        {
            // Set the __sub event to call the operatorCallback function
            lua_pushstring(m_L, "__sub");
            lua_pushcfunction(m_L, &operatorCallback<camp::sub>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::mul))
        {
            // Set the __mul event to call the operatorCallback function
            lua_pushstring(m_L, "__mul");
            lua_pushcfunction(m_L, &operatorCallback<camp::mul>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::div))
        {
            // Set the __div event to call the operatorCallback function
            lua_pushstring(m_L, "__div");
            lua_pushcfunction(m_L, &operatorCallback<camp::div>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::mod))
        {
            // Set the __mod event to call the operatorCallback function
            lua_pushstring(m_L, "__mod");
            lua_pushcfunction(m_L, &operatorCallback<camp::mod>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::eq))
        {
            // Set the __eq event to call the operatorCallback function
            lua_pushstring(m_L, "__eq");
            lua_pushcfunction(m_L, &operatorCallback<camp::eq>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::lt))
        {
            // Set the __lt event to call the operatorCallback function
            lua_pushstring(m_L, "__lt");
            lua_pushcfunction(m_L, &operatorCallback<camp::lt>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::lte))
        {
            // Set the __le event to call the operatorCallback function
            lua_pushstring(m_L, "__le");
            lua_pushcfunction(m_L, &operatorCallback<camp::lte>);
            lua_rawset(m_L, -3);
        }
        if(metaclass.hasOperator(camp::umin))
        {
            // Set the __unm event to call the operatorCallback function
            lua_pushstring(m_L, "__unm");
            lua_pushcfunction(m_L, &uminCallback);
            lua_rawset(m_L, -3);
        }
    }

    if(m_Constructed)
    {
        // Set the __gc event to call the destructCallback function
        lua_pushstring(m_L, "__gc");
        lua_pushcfunction(m_L, &destructCallback);
        lua_rawset(m_L, -3);
    }

    // Set the table as the metatable of the userdata
    lua_setmetatable(m_L, -2);
}

} // namespace lua

} // namespace camp

