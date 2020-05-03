cmake_minimum_required(VERSION 3.10.2)

project(VerifyURl)

set(W_FLAGS, "-Wall -Wextra -Werror")

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

find_package(CURL REQUIRED)

add_executable(VerifyURl src/main.cpp
                         src/utility.cpp
                         src/url_content.cpp)

target_link_libraries(VerifyURl PRIVATE ${CURL_LIBRARIES})