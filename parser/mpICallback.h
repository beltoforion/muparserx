/** \file
    \brief Definition of the interface for parser callback objects.

<pre>
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
</pre>
*/
#ifndef MU_IPARSER_CALLBACK_H
#define MU_IPARSER_CALLBACK_H

//--- muParserX framework --------------------------------------------
#include "mpIToken.h"
#include "mpIPackage.h"


MUP_NAMESPACE_START

  /** \brief Interface for callback objects. 
    
    All Parser functions and operators must implement this interface.
  */
  class ICallback : public IToken
  {
  public:
      typedef ParserXBase parent_type;  

      ICallback(ECmdCode a_iCode, 
                const char_type *a_szName, 
                int a_nArgNum = 1,
                const IPackage *a_pPackage = NULL);
      virtual ~ICallback();

      virtual ICallback* AsICallback();
      virtual IValue* AsIValue();

      virtual void Eval(ptr_val_type& ret, const ptr_val_type *arg, int argc) = 0;
      virtual const char_type* GetDesc() const = 0;
      virtual bool IsVolatile() const;
      virtual string_type AsciiDump() const;
        
      int GetArgc() const;
      int GetArgsPresent() const;
      void  SetParent(parent_type *a_pParent);
      void  SetNumArgsPresent(int argc);

  protected:
      parent_type* GetParent();
      void  SetArgc(int argc);

  private:

      parent_type *m_pParent;      ///< Pointer to the parser object using this callback
      const IPackage *m_pPackage;  ///< Pointer to thhe package this callback is belonging to (may be zero)
      int  m_nArgc;                ///< Number of this function can take Arguments.
      int  m_nArgsPresent;         ///< Number of arguments actually submitted
  }; // class ICallback

MUP_NAMESPACE_END

#endif

