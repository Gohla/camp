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

#ifndef CAMP_XML_LIBXML_HPP
#define CAMP_XML_LIBXML_HPP

#include <camp-xml/common.hpp>
#include <libxml/tree.h>

namespace camp
{
namespace xml
{
namespace detail
{
/**
 * \brief Proxy that adapts the camp::xml functions to the libxml library
 */
struct LibXml
{
    typedef xmlNodePtr NodeType;

    static NodeType addChild(NodeType node, const std::string& name)
    {
        return xmlAddChild(node, xmlNewNode(0, reinterpret_cast<const xmlChar*>(name.c_str())));
    }

    static void setText(NodeType node, const std::string& text)
    {
        xmlNodeSetContent(node, reinterpret_cast<const xmlChar*>(text.c_str()));
    }

    static NodeType findFirstChild(NodeType node, const std::string& name)
    {
        const xmlChar* convertedName = reinterpret_cast<const xmlChar*>(name.c_str());
        NodeType child = xmlFirstElementChild(node);
        while (child)
        {
            if (xmlStrcmp(child->name, convertedName) == 0)
                break;
            else
                child = xmlNextElementSibling(child);
        }

        return child;
    }

    static NodeType findNextSibling(NodeType node, const std::string& name)
    {
        const xmlChar* convertedName = reinterpret_cast<const xmlChar*>(name.c_str());
        NodeType sibling = xmlNextElementSibling(node);
        while (sibling)
        {
            if (xmlStrcmp(sibling->name, convertedName) == 0)
                break;
            else
                node = xmlNextElementSibling(sibling);
        }

        return sibling;
    }

    static std::string getText(NodeType node)
    {
        return reinterpret_cast<const char*>(xmlNodeGetContent(node));
    }

    static bool isValid(NodeType node)
    {
        return node != 0;
    }
};

} // namespace detail

/**
 * \brief Serialize a CAMP object into a libxml xmlNodePtr
 *
 * This function iterates over all the object's properties
 * and transforms them into valid XML nodes. Composed sub-objects
 * are serialized recursively.
 *
 * \a node is the parent node to which the generated child nodes
 * will be appended.
 *
 * You have the possibility to exclude some properties from the
 * generated output with the last (optional) parameter, \a exclude.
 * If it is defined, any property containing this value as a tag
 * will be excluded from the serialization process. It is empty
 * by default, which means that no property will be excluded.
 *
 * \param object Object to serialize
 * \param node Parent for the generated XML nodes
 * \param tag Tag to include or exclude from the serialization process.
 * \param include Set this to true to make the tag an including tag, false for excluding tag.
 */
inline void serialize(const UserObject& object, xmlNodePtr node, const Value& tag = Value::nothing, bool include = false)
{
    detail::serialize<detail::LibXml>(object, node, tag, include);
}

/**
 * \brief Deserialize a CAMP object from a libxml xmlNodePtr
 *
 * This function iterates over all the object's properties
 * and read their value from XML nodes. Composed sub-objects
 * are deserialized recursively.
 *
 * You have the possibility to exclude some properties from
 * being read with the last (optional) parameter, \a exclude.
 * If it is defined, any property containing this value as a tag
 * will be excluded from the deserialization process. It is empty
 * by default, which means that no property will be excluded.
 *
 * \param object Object to fill with deserialized information
 * \param node XML node to parse
 * \param tag Tag to include or exclude from the serialization process.
 * \param include Set this to true to make the tag an including tag, false for excluding tag.
 */
inline void deserialize(const UserObject& object, xmlNodePtr node, const Value& tag = Value::nothing, bool include = false)
{
    detail::deserialize<detail::LibXml>(object, node, tag, include);
}

} // namespace xml

} // namespace camp

#endif // CAMP_XML_LIBXML_HPP
