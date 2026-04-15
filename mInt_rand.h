#pragma once
/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#include "mInt.h"

class Rand_mIntType
{
public:
		Rand_mIntType() {
						dist = new std::uniform_int_distribution<unsigned int>(0, mIntType::UL - 1);
	 			};
	 			
		~Rand_mIntType(){
						delete dist;
				};

			// returns a random number < a, slower than rand1()
			mIntType rand(const mIntType &a){
				    mIntType m ;
				    m = rand1(a);
				    while ( m >= a) m %= a;
				    return m;
				}
				
     //	  returns a 'random number' with the same number of internal DIGITS (!) as the argument     
     //   It is specifically not guaranteed that the returned value is smaller than a.     
     //   If the application has more specific requirements, it will have to enforce these itself.
			mIntType rand1(const mIntType &a){
						mIntType r;	
						while( r.Digits() < a.Digits()) {
									r += _Rand(); 
    							r.mulModulus();
  					}
   					return r;	
				}
			

private:
	
			unsigned int  _Rand(){
						unsigned  int ix2 = dist->operator()(rd);
						return ix2 % mIntType::UL ;
					}; 

			std::random_device rd;
			std::uniform_int_distribution<unsigned int>* dist;
};