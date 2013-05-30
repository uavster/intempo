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
project(INTEMPO_EXAMPLE_QUATERNIONS)

find_package(ATLANTE)
include_directories(${ATLANTE_INCLUDE_DIRS})
link_libraries(${ATLANTE_LIBRARIES})

#
# In your project using Intempo, you should replace the single include_directories command with the following two lines:
# find_package(INTEMPO)
# include_directories(${INTEMPO_INCLUDE_DIRS})
#
include_directories(../../intempo)

add_executable(test test.cpp)

