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


#ifndef CAMP_LUA_CONFIG_HPP
#define CAMP_LUA_CONFIG_HPP


// We define the CAMP_LUA_API macro according to the
// current operating system and build mode
#if defined(_WIN32) || defined(__WIN32__)

    #ifndef CAMP_STATIC

        // Windows platforms need specific keywords for import / export
        #ifdef CAMP_LUA_EXPORTS

            // From DLL side, we must export
            #define CAMP_LUA_API __declspec(dllexport)

        #else

            // From client application side, we must import
            #define CAMP_LUA_API __declspec(dllimport)

        #endif

    #else

        // No specific directive needed for static build
        #define CAMP_LUA_API

    #endif

#else

    // Other platforms don't need to define anything
    #define CAMP_LUA_API

#endif


#endif // CAMP_LUA_CONFIG_HPP
