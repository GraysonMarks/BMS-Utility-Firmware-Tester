
cmake_minimum_required(VERSION 3.10)
project(BMS-Utility-Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#cmake_policy(SET CMP0144 NEW)

# Use pkg-config to find LibSerial
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSERIAL REQUIRED libserial)

# Include LibSerial headers
include_directories(${LIBSERIAL_INCLUDE_DIRS})

# Add Source Files to EXE
add_executable(
    ${PROJECT_NAME} 
    source/main.cpp 
    source/BMSUtilityGuy.cpp 
    source/USBJoe.cpp
)

# Link Libraries to Target
target_link_libraries(
    ${PROJECT_NAME}
    ${LIBSERIAL_LIBRARIES} 
)