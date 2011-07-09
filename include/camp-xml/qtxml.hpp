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

#ifndef CAMP_XML_QTXML_HPP
#define CAMP_XML_QTXML_HPP

#include <camp-xml/common.hpp>
#include <QDomDocument>
#include <QDomElement>

namespace camp
{
namespace xml
{
namespace detail
{
/**
 * \brief Proxy that adapts the camp::xml functions to the QtXml library
 */
struct QtXml
{
    typedef QDomElement NodeType;

    static NodeType addChild(NodeType node, const std::string& name)
    {
        QDomElement child = node.ownerDocument().createElement(name.c_str());
        node.appendChild(child);
        return child;
    }

    static void setText(NodeType node, const std::string& text)
    {
        node.appendChild(node.ownerDocument().createTextNode(text.c_str()));
    }

    static NodeType findFirstChild(NodeType node, const std::string& name)
    {
        return node.firstChildElement(name.c_str());
    }

    static NodeType findNextSibling(NodeType node, const std::string& name)
    {
        return node.nextSiblingElement(name.c_str());
    }

    static std::string getText(NodeType node)
    {
        return node.text().toStdString();
    }

    static bool isValid(NodeType node)
    {
        return !node.isNull();
    }
};

} // namespace detail

/**
 * \brief Serialize a CAMP object into a QtXml QDomElement
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
 * \param tags Tags to include or exclude from the serialization process.
 * \param include Set this to true to make the tags including tags, false for excluding tags.
 * \param throwExceptions Set this to false to ignore thrown exceptions.
 */
inline void serialize(const UserObject& object, QDomElement node, const Args& tags = Args::empty,
    bool include = false, bool throwExceptions = true)
{
    detail::serialize<detail::QtXml>(object, node, tags, include, throwExceptions);
}

/**
 * \brief Deserialize a CAMP object from a QtXml QDomElement
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
 * \param throwExceptions Set this to false to ignore thrown exceptions.
 */
inline void deserialize(const UserObject& object, QDomElement node, const Value& tag = Value::nothing,
    bool include = false, bool throwExceptions = true)
{
    detail::deserialize<detail::QtXml>(object, node, tag, include, throwExceptions);
}

} // namespace xml

} // namespace camp

#endif // CAMP_XML_QTXML_HPP
