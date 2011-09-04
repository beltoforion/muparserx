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
#ifndef MUP_RPN_H
#define MUP_RPN_H

#include "mpFwdDecl.h"
#include "mpTypes.h"


MUP_NAMESPACE_START

  //---------------------------------------------------------------------------
  /** \brief A class representing the reverse polnish notation of the expression. 
  
  */
  class RPN
  {
  public:
    
    RPN();
   ~RPN();
    
    void Add(ptr_tok_type tok);
    void AddNewline(ptr_tok_type tok, int n);
    void Pop(int num);
    void Reset();
    void Finalize();
    void AsciiDump() const;

    const token_vec_type& GetData() const;
    std::size_t GetSize() const;

    int GetRequiredStackSize() const;
    void EnableOptimizer(bool bStat);

  private:

    token_vec_type m_vRPN;
    int m_nStackPos;
    int m_nLine;
    int m_nMaxStackPos;
    bool m_bEnableOptimizer;
  };

MUP_NAMESPACE_END

#endif