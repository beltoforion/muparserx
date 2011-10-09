/** \file
    \brief Definition of the virtual base class used for all parser values.

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
#ifndef MUP_IVALUE_H
#define MUP_IVALUE_H

#include "mpIToken.h"
#include "mpFwdDecl.h"

MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  /** \brief Interface to be implemented by all classes representing values. 
  
    IValue is the common base class of both the Value and Variable classes.
  */
  class IValue : public IToken
  {
  friend std::ostream& operator<<(std::ostream &a_Stream, const IValue &a_Val);
  friend std::wostream& operator<<(std::wostream &a_Stream, const IValue &a_Val);

  public:

    explicit IValue(ECmdCode a_iCode);
    IValue(ECmdCode a_iCode, const string_type &a_sIdent);
    
    bool operator==(const IValue &a_Val) const;
    bool operator!=(const IValue &a_Val) const;
    bool operator< (const IValue &a_Val) const;
    bool operator> (const IValue &a_Val) const;
    bool operator<=(const IValue &a_Val) const;
    bool operator>=(const IValue &a_Val) const;

    virtual ICallback* AsICallback();
    virtual IValue* AsIValue();
    virtual Value* AsValue() = 0;

    virtual IValue& operator=(int_type val) = 0;
    virtual IValue& operator=(float_type val) = 0;
    virtual IValue& operator=(string_type val) = 0;
    virtual IValue& operator=(bool_type val) = 0;
    virtual IValue& operator=(const cmplx_type &val) = 0;
    virtual IValue& operator=(const matrix_type &val) = 0;
            IValue& operator=(const IValue &ref);

    virtual IValue& operator+=(const IValue &ref) = 0;
    virtual IValue& operator-=(const IValue &ref) = 0;
    virtual IValue& operator*=(const IValue &ref) = 0;

    virtual IValue& At(int nRow, int nCol = 0) = 0;
    virtual IValue& At(const IValue &nRows, const IValue &nCols) = 0;

    virtual int_type GetInteger() const = 0;
    virtual float_type GetFloat() const = 0;
    virtual float_type GetImag() const = 0;
    virtual bool GetBool() const = 0;
    virtual const cmplx_type& GetComplex() const = 0;
    virtual const string_type&  GetString() const = 0;
    virtual const matrix_type& GetArray() const = 0;
    virtual char_type GetType() const = 0;
    virtual int GetRows() const = 0;
    virtual int GetCols() const = 0;

    virtual bool IsVolatile() const = 0;
    virtual string_type ToString() const;
  
    //---------------------------------------------------------------------------
    /** \brief Returns the dimension of the value represented by a value object.
        
        The value represents the dimension of the object. Possible value are:
        <ul>
          <li>0 - scalar</li>
          <li>1 - vector</li>
          <li>2 - matrix</li>
        </ul>
    */
    inline int GetDim() const
    {
      return (IsMatrix()) ? GetArray().GetDim() : 0;
    }

    //---------------------------------------------------------------------------
    /** \brief Returns true if the type is either floating point or interger. 
        \throw nothrow
    */
    inline bool IsNonComplexScalar() const
    {
      char_type t = GetType();
      return t=='f' || t=='i';
    }

    //---------------------------------------------------------------------------
    /** \brief Returns true if the type is not a vector and not a string.
        \throw nothrow
    */
    inline bool IsScalar() const
    {
      char_type t = GetType();
      return t=='f' || t=='i' || t=='c';
    }

    //---------------------------------------------------------------------------
    /** \brief Returns true if this value is a noncomplex integer. 
        \throw nothrow
    */
    inline bool IsInteger() const
    {
      // checking the type is is insufficient. The integer could be disguised
      // as a float or a complex value
      return IsScalar() && GetImag()==0 && GetFloat()==(int_type)GetFloat();
    }

    //---------------------------------------------------------------------------
    /** \brief Returns true if this value is an array. 
        \throw nothrow
    */  
    inline bool IsMatrix() const 
    {
      return GetType() == 'm';  
    }

    //---------------------------------------------------------------------------
    /** \brief Returns true if this value is a complex value. 
        \throw nothrow
    */
    inline bool IsComplex() const
    {
      return GetType() == 'c' && GetImag()!=0;
    }

    //---------------------------------------------------------------------------
    /** \brief Returns true if this value is a string value. 
        \throw nothrow
    */
    inline bool IsString() const 
    {
      return GetType() == 's';  
    }

  protected:
    virtual ~IValue();
  }; // class IValue

  //---------------------------------------------------------------------------------------------
  Value operator*(const IValue& lhs, const IValue& rhs);

/*
  //---------------------------------------------------------------------------------------------
  IValue operator+(const IValue& lhs, const IValue& rhs)
  {
    return Value(lhs) += rhs;
  }

  //---------------------------------------------------------------------------------------------
  IValue operator-(const IValue& lhs, const IValue& rhs)
  {
    return Value(lhs) -= rhs;
  }
*/
}  // namespace mu

#endif


