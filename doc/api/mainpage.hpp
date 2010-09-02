/*! \mainpage CAMP C++ library documentation
 *
 * \htmlonly
 * <div class="logo">
 * \endhtmlonly
 * \image html logo_camp.png
 * \htmlonly
 * </div>
 * \endhtmlonly
 *
 * \section overview Overview
 *
 * CAMP is a C++ library which provides runtime reflection for types.
 * It provides an abstraction for most of the high-level concepts of C++:
 *
 * \li Classes
 * \li Enumerations
 * \li Properties
 * \li Functions
 * \li Objects
 * \li Variables
 *
 * By wrapping all these concepts into abstract structures, CAMP provides an extra layer of
 * flexibility to programs, and allow them to fully expose their data structures at runtime.
 *
 * Many applications can take advantage of CAMP, in order to automate tasks which would
 * otherwise require a huge amount of work. For example, CAMP can be used to expose and edit
 * objects' attributes into a graphical user interface. It can also be used to do
 * automatic binding of C++ classes to script languages such as Python or Lua.
 * Another possible application would be the serialization of objects to XML, text or
 * binary formats. Or you can even combine all these examples to provide a powerful
 * and consistent interface for manipulating your objects outside C++ code.
 *
 * \section example Quick example
 * 
 * Here is a simple example of how to use CAMP:
 *
 * \code
 * #include <camp/camptype.hpp>
 * #include <camp/class.hpp>
 * #include <string>
 * #include <iostream>
 * 
 * // Let's define a class for handling persons
 * class Person
 * {
 * public:
 * 
 *     // Construct a person from its name
 *     Person(const std::string& name) : m_name(name), m_age(0)
 *     {
 *     }
 * 
 *     // Retrieve the name of a person
 *     std::string name() const
 *     {
 *         return m_name;
 *     }
 * 
 *     // Retrieve the age of a person
 *     unsigned int age() const
 *     {
 *         return m_age;
 *     }
 * 
 *     // Set the age of a person
 *     void setAge(unsigned int age)
 *     {
 *         m_age = age;
 *     }
 * 
 *     // Make a person speak (tell about its name and age)
 *     void speak()
 *     {
 *         std::cout << "Hi! My name is " << m_name << " and I'm " << m_age << " years old." << std::endl;
 *     }
 * 
 * private:
 * 
 *     std::string m_name;
 *     unsigned int m_age;
 * };
 * 
 * // Make the Person type available to CAMP
 * CAMP_TYPE(Person)
 * 
 * 
 * int main()
 * {
 *     // Bind our Person class to CAMP
 *     camp::Class::declare<Person>("Person")
 *         .constructor1<std::string>()
 *         .property("name", &Person::name)
 *         .property("age", &Person::age, &Person::setAge)
 *         .function("speak", &Person::speak);
 * 
 *     // Retrieve the metaclass by its name
 *     const camp::Class& metaclass = camp::classByName("Person");
 * 
 *     // Use the metaclass to construct a new person named John
 *     camp::UserObject john = metaclass.construct(camp::Args("John"));
 *
 *     // Print its name
 *     std::cout << "John's name is: " << john.get("name") << std::endl;
 *
 *     // Set its age to 24
 *     john.set("age", 24);
 *
 *     // Make John say something
 *     john.call("speak");
 * 
 *     // Kill John
 *     metaclass.destroy(john);
 * 
 *     return 0;
 * }
 * \endcode
 *
 * \section license License
 *
 * CAMP is distributed under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version of the License, or (at your option) any later version.
 *
 * \verbatim
 * Copyright (C) 2009-2010 TECHNOGERMA Systems France and/or its subsidiary(-ies).
 * Contact: Technogerma Systems France Information (contact@technogerma.fr)
 * 
 * This file is part of the CAMP library.
 * 
 * CAMP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CAMP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with CAMP.  If not, see <http://www.gnu.org/licenses/>.
 * \endverbatim
 *
 */
