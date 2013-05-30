#
# Intempo - C++ template library for signal interpolation
#
# Copyright (C) 2012-2013  Ignacio Mellado-Bataller
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

cmake_minimum_required(VERSION 2.6)
project(INTEMPO)

# Installation
macro(install_with_dir PREFIX_TO_CUT)
 
 string(LENGTH ${PREFIX_TO_CUT} PREFIX_LEN)

 foreach(F ${ARGN})
   string(REGEX MATCH "(.*)[/\\]" DIR ${F})
   string(LENGTH ${DIR} DIR_LEN)
   math(EXPR DIR_KEEP "${DIR_LEN} - ${PREFIX_LEN}")
   string(SUBSTRING ${DIR} ${PREFIX_LEN} ${DIR_KEEP} DIR2)
   install(FILES ${F} DESTINATION include/${DIR2})
 endforeach(F)
          
endmacro(install_with_dir)
           

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/intempo/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/intempo/*.hh)
install_with_dir(${CMAKE_CURRENT_SOURCE_DIR} ${HEADER_FILES})
install_with_dir(${CMAKE_CURRENT_SOURCE_DIR} ${SOURCE_FILES})

install(FILES install/intempo-config.cmake DESTINATION lib/intempo)
install(FILES install/intempo.pc DESTINATION lib/pkgconfig)
