#根据CMake的规则，在根目录下和每个子目录下加入 CMakeLists.txt 文件。
#project(name)：设置project的名字为name。
#add_dependencies：设置依赖关系
#add_subdirectory：添加子目录
#add_executable：添加可执行文件
#add_library：添加库
#cmake_minimum_required：设置cmake最低版本要求
#include_directories：包含目录
#target_link_libraries：链接库
#set：可以用于设置变量
#aux_source_directory(. SOURCE_FILES)：查找当前CMakeLists.txt所在目录下的所有源文件，并将名称保存到SOURCE_FILES变量
#补充命令：
#file(GLOB_RECURSE HEADER_FILES dir/*.h??)
#此命令可以用来收集源文件 HEADER_FILES 作为变量保存收集的结果。 后面为文件过滤器，其中dir为起始搜索的文件夹，即在dir目录下，开始收集，而且会遍历子目录。 ? 代表 a-z。

cmake_minimum_required(VERSION 3.10)
project(exam)
# 当使用 project(name) 命令时，CMake会自动生成两个变量 name_SOURCE_DIR 和 name_BINARY_DIR，
# 前一个指向使用 project 命令的 CMakeLists.txt 所在的文件夹，
# 后一个指向用cmake构建时，Build 目录下对应的目录。
# 同时cmake还预定义了 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR 变量。
# 在实际的应用中，强烈推荐使用 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR 变量

include_directories(/Volumes/Documents/Projects/inf/include)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_STANDARD 11)

set(EXAM_SOURCE_FILES
        CodilityTest.cpp
        )

add_executable(examTest ${EXAM_SOURCE_FILES})
target_link_libraries(examTest /Volumes/Documents/Projects/inf/lib/libgtest.a)

set(HELL_SOURCE_FILES
        Hell.cpp)

add_executable(hell ${HELL_SOURCE_FILES})
target_link_libraries(hell /Volumes/Documents/Projects/inf/lib/libgtest.a)

add_executable(kvs KeyValues.cpp)

add_executable(ben benchmark.cpp)
target_link_libraries(ben /Volumes/Documents/Projects/inf/lib/libbenchmark.a)

set(MATCHENGINE_SOURCE_FILES
        MatchEngine.cpp
        )

add_executable(matchEngine ${MATCHENGINE_SOURCE_FILES})