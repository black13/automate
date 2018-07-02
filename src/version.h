/*
    This file is part of automate.
      Copyright Joachim Schiele
      
    automate is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    automate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with automate.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
** this file is used via cmake to set the version number globally
** cmake will (when typing 'cmake', before you type 'make') generate a file called version.h
** which can be included in any project cpp or h file to query for the version
**
** something similar is used to set the version for the doxygen documentation, see doc/CMakeLists.txt
*/
#define VERSION "1.0"
