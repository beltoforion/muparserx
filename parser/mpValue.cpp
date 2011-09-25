/*
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
#include "mpValue.h"
#include "mpError.h"
#include "mpValueCache.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  /** \brief Construct an empty value object of a given type. 
      \param cType The type of the value to construct (default='v').
  */
  Value::Value(char_type cType)
    :IValue(cmVAL)
    ,m_val(0,0)
    ,m_psVal(NULL)
    ,m_pvVal(NULL)
    ,m_cType(cType)
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {
    // strings and arrays must allocate their memory
    switch (cType)
    {
    case 's': m_psVal = new string_type(); break;
    case 'a': m_pvVal = new array_type(0, Value(0)); break;
    }
  }

  //---------------------------------------------------------------------------
  Value::Value(int_type a_iVal)
    :IValue(cmVAL)
    ,m_val((float_type)a_iVal, 0)
    ,m_psVal(NULL)
    ,m_pvVal(NULL)
    ,m_cType('i')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  Value::Value(bool_type a_bVal)
    :IValue(cmVAL)
    ,m_val((float_type)a_bVal, 0)
    ,m_psVal(NULL)
    ,m_pvVal(NULL)
    ,m_cType('b')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  Value::Value(string_type a_sVal)
    :IValue(cmVAL)
    ,m_val()
    ,m_psVal(new string_type(a_sVal))
    ,m_pvVal(NULL)
    ,m_cType('s')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  Value::Value(int_type array_size, float_type v)
    :IValue(cmVAL)
    ,m_val()
    ,m_psVal(NULL)
    ,m_pvVal(new array_type(array_size, Value(v)))
    ,m_cType('a')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  /** \brief Create a m x n matrix
  */
  Value::Value(int_type m, int_type n, float_type v)
    :IValue(cmVAL)
    ,m_val()
    ,m_psVal(NULL)
    ,m_pvVal(new array_type(m, n, Value(v)))
    ,m_cType('a')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  Value::Value(const char_type *a_szVal)
    :IValue(cmVAL)
    ,m_val()
    ,m_psVal(new string_type(a_szVal))
    ,m_pvVal(NULL)
    ,m_cType('s')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  Value::Value(const cmplx_type &v)
    :IValue(cmVAL)
    ,m_val(v)
    ,m_psVal(NULL)
    ,m_pvVal(NULL)
    ,m_cType('c')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {
    if ( (m_val.real()==(int_type)m_val.real()) && (m_val.imag()==0) )
      m_cType = 'i';
    else
      m_cType = (m_val.imag()==0) ? 'f' : 'c';
  }

  //---------------------------------------------------------------------------
  Value::Value(float_type val)
    :IValue(cmVAL)
    ,m_val(val, 0)
    ,m_psVal(NULL)
    ,m_pvVal(NULL)
    ,m_cType((val==(int_type)val) ? 'i' : 'f')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  Value::Value(const array_type &val)
    :IValue(cmVAL)
    ,m_val()
    ,m_psVal(NULL)
    ,m_pvVal(new array_type(val))
    ,m_cType('a')
    ,m_iFlags(flNONE)
    ,m_pCache(NULL)
  {}

  //---------------------------------------------------------------------------
  Value::Value(const Value &a_Val)
    :IValue(cmVAL)
    ,m_psVal(NULL)
    ,m_pvVal(NULL)
    ,m_pCache(NULL)
  {
    Assign(a_Val);
  }

  //---------------------------------------------------------------------------
  Value::Value(const IValue &a_Val)
    :IValue(cmVAL)
    ,m_psVal(NULL)
    ,m_pvVal(NULL)
    ,m_pCache(NULL)
  {
    Reset();

    switch(a_Val.GetType())
    {
    case 'i': 
    case 'f': 
    case 'b': m_val = cmplx_type(a_Val.GetFloat(), 0);
              break;


    case 'c': m_val = cmplx_type(a_Val.GetFloat(), a_Val.GetImag());
              break;

    case 's': if (!m_psVal)
                m_psVal = new string_type(a_Val.GetString());
              else
               *m_psVal = a_Val.GetString();
              break;

    case 'a': if (!m_pvVal) 
                m_pvVal = new array_type(a_Val.GetArray());
              else
               *m_pvVal  = a_Val.GetArray();  
              break;

    case 'v': break;
    default:  MUP_FAIL(INVALID_TYPE_CODE);
    }
    
    m_cType = a_Val.GetType();
  }

  //---------------------------------------------------------------------------
  Value& Value::operator=(const Value &a_Val)
  {
    Assign(a_Val);
    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::At(int nRow, int nCol)
  {
    if (m_cType!='a' || m_pvVal==NULL)
      throw ParserError( ErrorContext(ecAPI_NOT_AN_ARRAY) ); 

    if (nRow>=m_pvVal->GetRows() || nCol>=m_pvVal->GetCols())
      throw ParserError( ErrorContext(ecINDEX_OUT_OF_BOUNDS) ); 

    return m_pvVal->At(nRow, nCol);
  }

  //---------------------------------------------------------------------------
  Value::~Value()
  {
    delete m_psVal;
    delete m_pvVal;
  }

  //---------------------------------------------------------------------------
  IToken* Value::Clone() const
  {
    return new Value(*this);
  }

  //---------------------------------------------------------------------------
  Value* Value::AsValue()
  {
    return this;
  }

  //---------------------------------------------------------------------------
  /** \brief Copy constructor. */
  void Value::Assign(const Value &ref)
  {
    if (this==&ref)
      return;

    m_val    = ref.m_val;
    m_cType  = ref.m_cType;
    m_iFlags = ref.m_iFlags;

    // allocate room for a string
    if (ref.m_psVal)
    {
      if (!m_psVal)
        m_psVal = new string_type(*ref.m_psVal);
      else
       *m_psVal = *ref.m_psVal;
    }
    else
    {
      delete m_psVal;
      m_psVal = NULL;
    }

    // allocate room for a vector
    if (ref.m_pvVal)
    {
      if (m_pvVal==NULL)
        m_pvVal = new array_type(*ref.m_pvVal);
      else
       *m_pvVal = *ref.m_pvVal;
    }
    else
    {
      delete m_pvVal;
      m_pvVal = NULL;
    }

    // Do NOT access ref beyound this point! If you do, "unboxing" of
    // a 1 x 1 matrix using:
    //
    // this->Assign(m_pvVal->At(0,0));
    // 
    // will blow up in your face since ref will become invalid at them very
    // moment you delete m_pvVal!
  }

  //---------------------------------------------------------------------------
  void Value::Reset()
  {
    m_val = cmplx_type(0,0);

    delete m_psVal;
    m_psVal = NULL;
		
    delete m_pvVal;
    m_pvVal = NULL;

    m_cType = 'f';
    m_iFlags = flNONE;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator=(bool val)
  {
    m_val = cmplx_type((float_type)val,0);

    delete m_psVal;
    m_psVal = NULL;

    delete m_pvVal;
    m_pvVal = NULL;

    m_cType = 'b';
    m_iFlags = flNONE;
    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator=(int_type a_iVal)
  {
    m_val = cmplx_type(a_iVal,0);

    delete m_psVal;
    m_psVal = NULL;

    delete m_pvVal;
    m_pvVal = NULL;

    m_cType = 'i';
    m_iFlags = flNONE;
    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator=(float_type val)
  {
    m_val = cmplx_type(val, 0);

    delete m_psVal;
    m_psVal = NULL;

    delete m_pvVal;
    m_pvVal = NULL;

    m_cType = (val==(int_type)val) ? 'i' : 'f';
    m_iFlags = flNONE;
    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator=(string_type a_sVal)
  {
    m_val = cmplx_type();
    
    if (!m_psVal)
      m_psVal = new string_type(a_sVal);
    else
     *m_psVal = a_sVal;

    delete m_pvVal;
    m_pvVal = NULL;

    m_cType = 's';
    m_iFlags = flNONE;
    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator=(const char_type *a_szVal)
  {
    m_val = cmplx_type();

    if (!m_psVal)
      m_psVal = new string_type(a_szVal);
    else
     *m_psVal = a_szVal;

    delete m_pvVal;
    m_pvVal = NULL;

    m_cType = 's';
    m_iFlags = flNONE;
    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator=(const array_type &a_vVal)
  {
    m_val = cmplx_type(0,0);

    delete m_psVal;
    m_psVal = NULL;
		
    if (m_pvVal==NULL)
      m_pvVal = new array_type(a_vVal);
    else
      *m_pvVal = a_vVal;
    
    m_cType = 'a';
    m_iFlags = flNONE;

    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator=(const cmplx_type &val)
  {
    m_val = val;

    delete m_psVal;
    m_psVal = NULL;

    delete m_pvVal;
    m_pvVal = NULL;

    m_cType = (m_val.imag()==0) ? ( (m_val.real()==(int)m_val.real()) ? 'i' : 'f' ) : 'c';
    m_iFlags = flNONE;

    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator+=(const IValue &val)
  {
    if (IsScalar() && val.IsScalar())
    {
      // Scalar/Scalar addition
      m_val += val.GetComplex();
    }
    else if (IsArray() && val.IsArray())
    {
      // Matrix/Matrix addition
      assert(m_pvVal);
      *m_pvVal += val.GetArray();
    }
    else if (IsString() && val.IsString())
    {
      // string/string addition
      assert(m_psVal);
      *m_psVal += val.GetString();
    }
    else
    {
      // Type conflict
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, _T("+"), GetType(), val.GetType(), 2));
    }

    return *this;
  }

  //---------------------------------------------------------------------------
  IValue& Value::operator-=(const IValue &val)
  {
    if (IsScalar() && val.IsScalar())
    {
      // Scalar/Scalar addition
      m_val -= val.GetComplex();
    }
    else if (IsArray() && val.IsArray())
    {
      // Matrix/Matrix addition
      assert(m_pvVal);
      *m_pvVal -= val.GetArray();
    }
    else
    {
      // There is a typeconflict:
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, _T("-"), GetType(), val.GetType(), 2));
    }

    return *this;
  }

  //---------------------------------------------------------------------------
  /** \brief Assign a value with multiplication
      \param val The value to multiply to this

    When multiplying to values with each value representing a matrix type
    the result is checked whether it is a 1 x 1 matrix. If so the value is
    "unboxed" and stored directly in this value object. It is no longer 
    treated as a matrix internally.
  */
  IValue& Value::operator*=(const IValue &val)
  {
    if (IsScalar() && val.IsScalar())
    {
      // Scalar/Scalar multiplication
      m_val *= val.GetComplex();
      
      // Check whether we're dealing with a complex or integer result, if so set the 
      // type flag accordingly
      if (m_val.imag()!=0)
        m_cType = 'c';
      else if ((double)(int)m_val.real()==m_val.real())
        m_cType = 'i';
    }
    else if (IsArray() && val.IsArray())
    {
      // Matrix/Matrix addition
      assert(m_pvVal);
      *m_pvVal *= val.GetArray();

      // The result may actually be a scalar value, i.e. the scalar product of
      // two vectors.
      if (m_pvVal->GetCols()==1 && m_pvVal->GetRows()==1)
      {
        Assign(m_pvVal->At(0,0));
      }
    }
    else if ( IsArray() && val.IsScalar() )
    {
      *m_pvVal *= val;
    }
    else if ( IsScalar() * val.IsArray() )
    {
      // transform this into a matrix and multiply with rhs
      Value prod = val * (*this);
      Assign(prod);
    }
    else
    {
      // Type conflict
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, _T("*"), GetType(), val.GetType(), 2));
    }

    return *this;
  }

  //---------------------------------------------------------------------------
  char_type Value::GetType() const
  {
    return m_cType;
  }

  //---------------------------------------------------------------------------
  /** \brief Return the value as an integer. 
    
    This function should only be called if you really need an integer value and
    want to make sure your either get one or throw an exception if the value
    can not be implicitely converted into an integer.
  */
  int_type Value::GetInteger() const
  {
    float_type v = m_val.real();

    if (m_cType!='i') //!IsScalar() || (int_type)v-v!=0)
    {
      ErrorContext err;
      err.Errc  = ecTYPE_CONFLICT;
      err.Type1 = m_cType;
      err.Type2 = 'i';
      
      if (GetIdent().length())
      {
        err.Ident = GetIdent();
      }
      else
      {
        stringstream_type ss;
        ss << *this;
        err.Ident = ss.str();
      }

      throw ParserError(err);
    }

    return (int_type)v;
  }

  //---------------------------------------------------------------------------
  float_type Value::GetFloat() const
  {
/*
    if (!IsScalar() && m_cType!='b')
    {
      ErrorContext err;
      err.Errc  = ecTYPE_CONFLICT;
      err.Type1 = m_cType;
      err.Type2 = 'c';
      
      if (GetIdent().length())
      {
        err.Ident = GetIdent();
      }
      else
      {
        stringstream_type ss;
        ss << *this;
        err.Ident = ss.str();
      }

      throw ParserError(err);
    }
*/
    return m_val.real();
  }

  //---------------------------------------------------------------------------
  float_type Value::GetImag() const
  {
    if (!IsScalar())
    {
      ErrorContext err;
      err.Errc  = ecTYPE_CONFLICT;
      err.Type1 = m_cType;
      err.Type2 = 'c';
      
      if (GetIdent().length())
      {
        err.Ident = GetIdent();
      }
      else
      {
        stringstream_type ss;
        ss << *this;
        err.Ident = ss.str();
      }

      throw ParserError(err);
    }

    return m_val.imag();
  }

  //---------------------------------------------------------------------------
  const cmplx_type& Value::GetComplex() const
  {
    return m_val;
  }

  //---------------------------------------------------------------------------
  const string_type& Value::GetString() const
  {
    CheckType('s');
    assert(m_psVal!=NULL);
    return *m_psVal;
  }

  //---------------------------------------------------------------------------
  bool Value::GetBool() const
  {
    CheckType('b');
    return m_val.real()==1;
  }

  //---------------------------------------------------------------------------
  const array_type& Value::GetArray() const
  {
    CheckType('a');
    assert(m_pvVal!=NULL);
    return *m_pvVal;
  }

  //---------------------------------------------------------------------------
  int Value::GetRows() const
  {
    return (GetType()!='a') ? 1 : GetArray().GetRows();
  }
  
  //---------------------------------------------------------------------------
  int Value::GetCols() const
  {
    return 1;
  }

  //---------------------------------------------------------------------------
  void Value::CheckType(char_type a_cType) const
  {
    if (m_cType!=a_cType)
    {
      ErrorContext err;
      err.Errc  = ecTYPE_CONFLICT;
      err.Type1 = m_cType;
      err.Type2 = a_cType;
      
      if (GetIdent().length())
      {
        err.Ident = GetIdent();
      }
      else
      {
        stringstream_type ss;
        ss << *this;
        err.Ident = ss.str();
      }

      throw ParserError(err);
    }
  }

  //---------------------------------------------------------------------------
  bool Value::IsVolatile() const
  {
    return IsFlagSet(IValue::flVOLATILE);
//    return true;
  }

  //---------------------------------------------------------------------------
  string_type Value::AsciiDump() const
  {
    stringstream_type ss;

    ss << g_sCmdCode[ GetCode() ];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; type=\"") << GetType() << _T("\"");
    ss << _T("; val=");

    switch(m_cType)
    {
    case 'i': ss << (int_type)m_val.real(); break;
    case 'f': ss << m_val.real(); break;
    case 'a': ss << _T("(array)"); break;
    case 's': 
              assert(m_psVal!=NULL);
              ss << _T("\"") << m_psVal << _T("\""); break;
    }

    ss << ((IsFlagSet(IToken::flVOLATILE)) ? _T("; ") : _T("; not ")) << _T("volatile");
    ss << _T("]");

    return ss.str();
  }

  //---------------------------------------------------------------------------
  void Value::Release()
  {
    if (m_pCache)
      m_pCache->ReleaseToCache(this);
    else
      delete this;
  }

  //---------------------------------------------------------------------------
  void Value::BindToCache(ValueCache *pCache)
  {
    m_pCache = pCache;
  }
}  // namespace mu
