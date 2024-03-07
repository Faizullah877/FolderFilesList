# CMakeList.txt : CMake project for files_list, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (files_list "files_list.cpp" "files_list.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET files_list PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
