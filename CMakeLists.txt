cmake_minimum_required(VERSION 1.0.0)

project(gauthenticator-cli)

file(GLOB_RECURSE SOURCE_FILES *.c *.h)

include_directories("/usr/local/include" ${PROJECT_SOURCE_DIR}/src)

link_directories("/usr/local/lib")

add_executable(gauth-cli ${SOURCE_FILES})
