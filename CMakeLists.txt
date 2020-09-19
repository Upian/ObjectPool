cmake_minimum_required(VERSION 3.0.0)
project(ObjectPool 
    LANGUAGES   CXX   
    VERSION     0.1.0
    )

include(CTest)
enable_testing()

set( CMAKE_BUILD_TYPE Debug ) #debug, release 여부
set( CMAKE_VERBOSE_MAKEFILE false )
#set (CMAKE_CXX_COMPILER=/usr/local/bin/g++)
set( CMAKE_CXX_STANDARD 20) #버전 

#파일 목록
set(LIB_FILE

)
set(BIN_FILES
    src/Main.cpp
)
 
#출력 경로
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY output/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY output/${CMAKE_BUILD_TYPE}/lib)

#출력
#add_library(ObjectPool STATIC ${LIB_FILES})

add_executable(TEST_ObjectPool ${BIN_FILES})
#target_link_libraries(TEST_ObjectPool ObjectPool) #link

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
