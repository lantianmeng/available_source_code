#CMake最低版本要求
cmake_minimum_required(VERSION 2.8)

#项目信息
project(learn_boost)

#依赖头文件目录
include_directories(E:\\Tool\\boost_1_63_0)

#链接的库文件目录
link_directories("E:\\Tool\\boost_1_63_0\\stage\\lib")

#查找当前目录下的所有源文件，并保存到变量DIR_SRCS
aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(learn_boost ${DIR_SRCS})