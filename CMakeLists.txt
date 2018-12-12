cmake_minimum_required(VERSION 3.12)
project(PheonixCoinCurrentBranch)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(PheonixCoinCurrentBranch main.cpp BlockChain.h BlockChain.cpp Block.cpp Block.h Transaction.cpp Transaction.h User.cpp User.h Driver.cpp Driver.h Serializer.cpp Serializer.h)