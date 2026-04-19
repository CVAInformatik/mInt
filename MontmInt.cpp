/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#include "mInt.h"
#include "MontmInt.h"

	mIntType MontmIntType::tomInt() const
	{
		mIntType temp(val);
	  mIntType quotient;
		temp *= Rinv;
	  temp %= N ;
	  return temp ;
	}
	
 	MontmIntType   &MontmIntType::frommInt(const mIntType &a){
 		  mIntType quotient;
 		  mIntType temp(a);
 		  val = 0;
 		  temp <<= ((Rdigits  - 1) * mIntType::DIGITSIZE) ;
 		  DivRem(temp, N, quotient, val);
 		  return *this;
 	}

	void REDC(  const mIntType &R, const mIntType &N, const mIntType &Ninv,mIntType &a){
		mIntType m(a);
		/* m mod R */ 
		while( m.Digits() > (R.Digits()-1)) m.val.pop_back();
		while( m.val.size() && (m.val.back() == 0)) m.val.pop_back();
		m *= Ninv;
		while( m.Digits() > (R.Digits()- 1) ) m.val.pop_back();
		while( m.val.size() && (m.val.back() == 0)) m.val.pop_back();
		mIntType t = N;
		t *= m;
		t += a;
    a.val.clear();
    for(int i = R.val.size()-1; i < t.val.size(); i++)		
      a.val.push_back(t.val[i]);
		while( a.val.size() && (a.val.back() == 0)) a.val.pop_back();
		if( N == a) a = 0;
		else if ( N< a) a -= N;
	}

/* returns the actual value, not the Montgomery-mapped value */
std::string iToA(const MontmIntType &a ) {
	  mIntType t = a.tomInt();
	  return iToA( t);
}

