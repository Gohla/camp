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


#include <camp-lua/callback.hpp>
#include <camp-lua/conversion.hpp>
#include <camp-lua/lua.hpp>
#include <camp/class.hpp>
#include <camp/property.hpp>
#include <camp/function.hpp>
#include <camp/error.hpp>

namespace camp
{

namespace lua
{

int indexCallback(lua_State* L)
{
    // Check args
    if (lua_gettop(L) != 2)
        return luaL_error(L, "Invalid args count (got %d, expected 2)", lua_gettop(L));
    if (!lua_isuserdata(L, 1))
        return luaL_error(L, "First arg must be a userdata (got %s)", lua_typename(L, lua_type(L, 1)));
    if (!lua_isstring(L, 2))
        return luaL_error(L, "Second arg must be a string (got %s)", lua_typename(L, lua_type(L, 2)));

    // Get args
    camp::UserObject* userdata = static_cast<camp::UserObject*>(lua_touserdata(L, 1));
    std::string key(lua_tostring(L, 2));

    // Clear the stack
    lua_settop(L, 0);

    // Access to the property/function from the metaclass
    const camp::Class& metaclass = userdata->getClass();

    try
    {
        if(metaclass.hasProperty(key))
        {
            // Try to retrieve a property with the requested name
            const camp::Property& property = metaclass.property(key);

            // Call the property
            camp::Value value = property.get(*userdata);

            // Publish to Lua
            camp::lua::valueToLua(L, value);

            return 1; // One value returned
        }
        else if(metaclass.hasFunction(key))
        {
            // Try to retrieve a function
            const camp::Function& function = metaclass.function(key);

            // Push the callback function onto the stack
            // The function to be called is added to the C closure
            lua_pushlightuserdata(L, const_cast<camp::Function*>(&function));
            lua_pushcclosure(L, &callCallback, 1);

            return 1; // One value returned (the C closure)
        }
        else
            return luaL_error(L, "Property or function with name %s does not exist", key.c_str());
    }
    catch (const camp::Error& err)
    {
        return luaL_error(L, err.what());
    }

    return 0;
}

int newIndexCallback(lua_State* L)
{
    // Check args
    if (lua_gettop(L) != 3)
        return luaL_error(L, "Invalid args count (got %d, expected 3)", lua_gettop(L));
    if (!lua_isuserdata(L, 1))
        return luaL_error(L, "First arg must be a userdata (got %s)", lua_typename(L, lua_type(L, 1)));
    if (!lua_isstring(L, 2))
        return luaL_error(L, "Second arg must be a string (got %s)", lua_typename(L, lua_type(L, 2)));

    // Get args
    camp::UserObject* userdata = static_cast<camp::UserObject*>(lua_touserdata(L, 1));
    std::string key(lua_tostring(L, 2));
    camp::Value newValue = camp::lua::valueFromLua(L, 3);

    // Clear the stack
    lua_settop(L, 0);

    // Access to the property from the metaclass
    const camp::Class& metaclass = userdata->getClass();
    try
    {
        // Try to retrieve a property with the requested name
        const camp::Property& property = metaclass.property(key);

        // Call the property
        property.set(*userdata, newValue, 1);

        return 0; // No value returned
    }
    catch (const camp::ForbiddenWrite& err)
    {
        err; // Ignore forbidden write errors
    }
    catch (const camp::Error& err)
    {
        return luaL_error(L, err.what());
    }

    return 0;
}

int callCallback(lua_State* L)
{
    // Check args
    int argc = lua_gettop(L);
    if (argc < 1)
        return luaL_error(L, "Invalid args count (got %d, expected at least the object instance)", argc);
    if (!lua_isuserdata(L, 1))
        return luaL_error(L, "First arg must be a userdata (got %s)", lua_typename(L, lua_type(L, 1)));

    // Get args
    camp::UserObject* userdata = static_cast<camp::UserObject*>(lua_touserdata(L, 1));
    camp::Args args;
    for (int i = 2; i <= argc; ++i)
        args += camp::lua::valueFromLua(L, i);

    // Retrieve the function to be called
    int fctIndex = lua_upvalueindex(1);
    if (!lua_isuserdata(L, fctIndex))
        return luaL_error(L, "The function to be called could not be retrieved");
    camp::Function* function = static_cast<camp::Function*>(lua_touserdata(L, fctIndex));

    // Clear the stack
    lua_settop(L, 0);

    try
    {
        // Call the function.
        camp::Value result = function->call(*userdata, args);

        // Push the result if needed
        if (result.type() == camp::noType)
        {
            return 0;
        }
        else
        {
            camp::lua::valueToLua(L, result);
            return 1;
        }
    }
    catch (const camp::Error& err)
    {
        return luaL_error(L, err.what());
    }

    return 0;
}

int constructCallback(lua_State* L)
{
    // Get args
    camp::Args args;
    int argc = lua_gettop(L);
    for (int i = 1; i <= argc; ++i)
        args += camp::lua::valueFromLua(L, i);

    // Retrieve the subject camp::Class
    int classIndex = lua_upvalueindex(1);
    if (!lua_isuserdata(L, classIndex))
        return luaL_error(L, "The metaclass could not be retrieved");
    camp::Class* metaclass = static_cast<camp::Class*>(lua_touserdata(L, classIndex));

    // Clear the stack
    lua_settop(L, 0);

    // Call the constructor
    camp::UserObject result = metaclass->construct(args);
    if (result == camp::UserObject::nothing)
        return luaL_error(L, "Fail to construct a new '%s'", metaclass->name().c_str());

    // Convert the new object to Lua
    camp::lua::valueToLua(L, result, true);

    return 1;
}

int destructCallback(lua_State* L)
{
    // Get userdata and destroy it
    camp::UserObject* userdata = static_cast<camp::UserObject*>(lua_touserdata(L, 1));
    userdata->getClass().destroy(*userdata);
    return 1;
}

int uminCallback( lua_State* L )
{
    // Check args
    int argc = lua_gettop(L);
    if (argc != 1 || !lua_isuserdata(L, 1))
        return luaL_error(L, "First arg must be a userdata (got %s)", lua_typename(L, lua_type(L, 1)));

    // Get args
    camp::UserObject* userdata = static_cast<camp::UserObject*>(lua_touserdata(L, 1));

    try
    {
        // Retrieve the function to be called
        const camp::Function& function = userdata->getClass().getUnaryOperator(camp::umin);

        // Clear the stack
        lua_settop(L, 0);

        // Call the function.
        camp::Value result = function.call(*userdata);

        // Push the result if needed
        if (result.type() == camp::noType)
        {
            return 0;
        }
        else
        {
            camp::lua::valueToLua(L, result);
            return 1;
        }
    }
    catch (const camp::Error& err)
    {
        return luaL_error(L, err.what());
    }

    return 0;
}

} // namespace lua

} // namespace camp

