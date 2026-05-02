/*
Copyright  ©2026 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#include "mInt.h"
#include "mInt_lib.h"
#include "mInt_rand.h"

#include <iostream>
#include <iomanip> 


void testSSM()
{

    mIntType  P; P = aToI("26959946667150639794667015087019630673557916260026308143510066298881");
    mIntType a(P);
    
   			
    for(int i = 0; i < 10; i++)
    {
    	  a *= a ;
    	  std::string s = "dummy "; //iToA(a);
    	  std::cout<< std::setw(5)<< i  << "  "<< std::setw(10)<< s.length()<< " "  << s << std::endl;
    }
        
}


int main(int argc, char **argv)
{
    testSSM();
}
