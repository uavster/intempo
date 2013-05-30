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
