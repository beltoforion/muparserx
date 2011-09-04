/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/

  muParserX - A C++ math parser library with array and string support
  Copyright 2010 Ingo Berg

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE
  as published by the Free Software Foundation, either version 3 of 
  the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see http://www.gnu.org/licenses.
*/
#ifndef MUP_STACK_H
#define MUP_STACK_H

#include <cassert>
#include <string>
#include <vector>

#include "mpError.h"


MUP_NAMESPACE_START

  /** \brief Parser stack implementation. 

  Stack implementation based on a std::stack. The behaviour of pop() had been
  slightly changed in order to get an error code if the stack is empty.
  The stack is used within the Parser both as a value stack and as an operator stack.

  \author (C) 2010 Ingo Berg 
  */
  template <typename TVal, typename TCont = std::vector<TVal> >
  class Stack 
  {
  private:
      /** \brief Type of the underlying container. */
      typedef TCont cont_type;
      cont_type m_Cont;

  public:	
      typedef TVal value_type;
    
      //---------------------------------------------------------------------------
      Stack()
        :m_Cont()
      {}

      //---------------------------------------------------------------------------
      virtual ~Stack()
      {
        m_Cont.clear();
      }

      //---------------------------------------------------------------------------
      void clear()
      {
        m_Cont.clear();
      }

      //---------------------------------------------------------------------------
      /** \brief Pop a value from the stack.
      
        Unlike the standard implementation this function will return the value that
        is going to be taken from the stack.

        \throw ParserException in case the stack is empty.
        \sa pop(int &a_iErrc)
      */
      value_type pop()
      {
        if (empty())
          throw ParserError(_T("stack is empty."));

        value_type el = top();
        m_Cont.pop_back();
        return el;
      }

      //---------------------------------------------------------------------------
      void pop(unsigned a_iNum)
      {
        for (unsigned i=0; i<a_iNum; ++i)
          m_Cont.pop_back();
      }

      //---------------------------------------------------------------------------
      /** \brief Push an object into the stack. 
          \param a_Val object to push into the stack.
          \throw nothrow
      */
      void push(const value_type& a_Val) 
      { 
        m_Cont.push_back(a_Val); 
      }

      //---------------------------------------------------------------------------
      /** \brief Return the number of stored elements. */
      unsigned size() const
      { 
        return (unsigned)m_Cont.size(); 
      }

      //---------------------------------------------------------------------------
      /** \brief Returns true if stack is empty false otherwise. */
      bool empty() const
      {
        return m_Cont.empty(); 
      }

      //---------------------------------------------------------------------------
      /** \brief Return reference to the top object in the stack. 
      
          The top object is the one pushed most recently.
      */
      value_type& top() 
      { 
        return m_Cont.back(); 
      }

      //---------------------------------------------------------------------------
      value_type* get_data()
      {
        return &m_Cont[0];
      }

      //---------------------------------------------------------------------------
      const value_type* get_data() const
      {
        return &m_Cont[0];
      }
  };
} // namespace mu

#endif
