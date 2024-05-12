#!/usr/bin/bash

URL="https://github.com/mlabbe/nativefiledialog.git"

rm -rf ./nativefiledialog/
git clone $URL

cd nativefiledialog
touch CMakeLists.txt
touch nativefiledialog-config.cmake

#from https://github.com/moepmoep12/nativefiledialog-cmake and
#https://gist.github.com/fracek/3323924
echo "find_package(PkgConfig REQUIRED)" >> CMakeLists.txt
echo "pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)" >> CMakeLists.txt
echo "set(SOURCES src/nfd_common.c src/nfd_gtk.c)" >> CMakeLists.txt
echo "add_library(nativefiledialog \${SOURCES})" >> CMakeLists.txt
echo "target_include_directories(nativefiledialog PUBLIC ./src/include)" >> CMakeLists.txt
echo "target_include_directories(nativefiledialog PRIVATE \${GTKMM_INCLUDE_DIRS})" >> CMakeLists.txt
echo "install(FILES \${SOURCES} DESTINATION \${CMAKE_INSTALL_INCLUDEDIR})" >> CMakeLists.txt

echo 'get_filename_component(SELF_DIR "\${CMAKE_CURRENT_LIST_FILE}" PATH)' >> nativefiledialog-config.cmake
echo 'include(\${SELF_DIR}/\${CMAKE_BUILD_TYPE}/nativefiledialog.cmake)' >> nativefiledialog-config.cmake
