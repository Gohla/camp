#include <string>
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


#ifndef CAMP_LUA_CALLBACK_HPP
#define CAMP_LUA_CALLBACK_HPP

#include <camp-lua/config.hpp>
#include <camp-lua/conversion.hpp>
#include <camp/operator.hpp>
#include <string>

struct lua_State;

namespace camp
{

namespace lua
{

/**
 * \brief Callback called when a Lua userdata holding a camp::UserObject triggers the '__index' event.
 *
 * \param L Lua stack holding the userdata
 * \return Number of return value pushed on the stack
 */
int indexCallback(lua_State* L);

/**
 * \brief Callback called when a Lua userdata holding a camp::UserObject triggers the '__newindex'
 * event.
 *
 * \param L Lua stack holding the userdata
 * \return Number of return value pushed on the stack
 */
int newIndexCallback(lua_State* L);

/**
 * \brief Callback called when a Lua C closure used to wrap a CAMP function call is called.
 *
 * \param L Lua stack holding the userdata
 * \return Number of return value pushed on the stack
 */
int callCallback(lua_State* L);

/**
 * \brief Callback called when a factory "new" function is called.
 *
 * \param L Lua stack holding the metaclass
 * \return Number of return value pushed on the stack
 */
int constructCallback(lua_State* L);

/**
 * \brief Callback called before a camp::UserObject is garbage collected.
 *
 * \param L Lua stack holding the userdata
 * \return Number of return value pushed on the stack
 */
int destructCallback(lua_State* L);

/**
 * \brief Callback called when an operator is called in Lua.
 *
 * \param L Lua stack holding the userdata
 * \return Number of return value pushed on the stack
 */
template<OperatorType Op>
int operatorCallback(lua_State* L)
{
    // Check args
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Invalid args count (got %d, expected at least the object instance and one other argument)", argc);
    if (!lua_isuserdata(L, 1))
        return luaL_error(L, "First arg must be a userdata (got %s)", lua_typename(L, lua_type(L, 1)));

    // Get args
    camp::UserObject* userdata = static_cast<camp::UserObject*>(lua_touserdata(L, 1));
    camp::Value arg = camp::lua::valueFromLua(L, 2);

    try
    {
        // Retrieve the function to be called
        const camp::Function& function = userdata->getClass().getOperator(Op, arg.typeInfo());

        // Clear the stack
        lua_settop(L, 0);

        // Call the function.
        camp::Value result = function.call(*userdata, camp::Args(arg));

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

/**
 * \brief Callback called when umin is called in Lua.
 *
 * \param L Lua stack holding the userdata
 * \return Number of return value pushed on the stack
 */
int uminCallback(lua_State* L);

} // namespace lua

} // namespace camp

#endif // CAMP_LUA_CALLBACK_HPP

