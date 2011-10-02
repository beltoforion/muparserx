/** \file mpIOprt.h
    \brief Definition of base classes needed for parser operator definitions.

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
#ifndef MUP_IPARSER_OPERATOR_H
#define MUP_IPARSER_OPERATOR_H

#include "mpICallback.h"
#include "mpIPrecedence.h"


MUP_NAMESPACE_START

    //------------------------------------------------------------------------------
    /** \brief Interface for binary operators.
        \ingroup binop

      All classes representing binary operator callbacks must be derived from
      this base class.
    */
    class IOprtBin : public ICallback,
                     public IPrecedence
    {
    public:

      IOprtBin(const char_type *a_szIdent, int nPrec, EOprtAsct eAsc);
      virtual ~IOprtBin();
      virtual string_type AsciiDump() const;

      virtual int GetPri() const;
      virtual EOprtAsct GetAssociativity() const;

      //------------------------------------------
      // IPrecedence implementation
      //------------------------------------------

      virtual IPrecedence* AsIPrecedence();

    private:

      void CheckPrototype(const string_type &a_szProt);
      int m_nPrec;
      EOprtAsct m_eAsc;
    }; // class IOperator


    //------------------------------------------------------------------------------
    /** \brief Interface for unary postfix operators.
        \ingroup postfix
    */
    class IOprtPostfix : public ICallback
    {
    public:
        IOprtPostfix(const char_type *a_szIdent);
        virtual ~IOprtPostfix();
        virtual string_type AsciiDump() const;
    }; // class IOperator


    //------------------------------------------------------------------------------
    /** \brief Interface for unary infix operators.
        \ingroup infix
    */
    class IOprtInfix : public ICallback
    {
    public:
        IOprtInfix(const char_type *a_szIdent);
        virtual ~IOprtInfix();
        virtual string_type AsciiDump() const;
    }; // class IOperator

    //------------------------------------------------------------------------------
    /** \brief Interface for index operator tokens.
    */
    class IOprtIndex : public IToken
    {
    public:
        IOprtIndex(int nArgc);
        virtual ~IOprtIndex();
        virtual string_type AsciiDump() const;
        virtual void At(ptr_val_type& ret, const ptr_val_type *arg, int argc) = 0;
        virtual IOprtIndex* AsIOprtIndex();

        int  GetArgc() const;
        int  GetArgsPresent() const;
        void SetNumArgsPresent(int argc);

    private:
        int m_nArgc;          ///< Number of arguments needed for the index operator (dimension of the index)
        int m_nArgsPresent;   ///< Number of arguments actually submitted

    }; // class IOperator
}  // namespace mu

#endif

