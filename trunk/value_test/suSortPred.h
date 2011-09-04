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
#ifndef SU_PRED_H
#define SU_PRED_H

#include <functional>


/** \brief Namespace containing utility functions and classes for string processing. */
namespace su
{
  namespace pred
  {
    /** \brief Sort two strings based on their length.
    */
    template<class TString>
	  struct SortByLength
      :public std::binary_function<TString, TString, bool>
	  {	
	    bool operator()(const TString& a_sLeft, const TString& a_sRight) const
		  {	
        if (a_sLeft.length() == a_sRight.length())
        {
          return a_sLeft < a_sRight;
        }
        else
        {
          return a_sLeft.length() < a_sRight.length();
        }
		  }
	  };
  } // namespace pred
} // end of namespace


#endif
