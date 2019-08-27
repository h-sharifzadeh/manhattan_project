cmake_minimum_required(VERSION 3.1)
project(parsian)

add_executable(parsian ../common/ai_base.cpp src/main.cpp src/soccer.cpp)
set(_USE_PROTO OFF)
if (_USE_PROTO)
  add_definitions(-DUSE_PROTO)
  INCLUDE(FindProtobuf)
  FIND_PACKAGE(Protobuf REQUIRED)
  PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER ../proto/messages_parsian_worldmodel.proto)
  ADD_LIBRARY(proto ${PROTO_HEADER} ${PROTO_SRC})
  include_directories(
      ${CMAKE_CURRENT_BINARY_DIR}
      ../proto
      ${PROTOBUF_INCLUDE_DIR}
      ${PROTOBUF_INCLUDE_DIR}/../../
  )
  TARGET_LINK_LIBRARIES(parsian proto ${PROTOBUF_LIBRARY})
endif ()

find_package(Threads REQUIRED)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS random regex system thread) # VC require regex, don't know why

include_directories(
  ../common
  ../geom
  ../extlibs/autobahn-cpp/include
  ../extlibs/msgpack-c/include
  include
  ${Boost_INCLUDE_DIRS}
  )
target_link_libraries(parsian
  Threads::Threads
  ${Boost_LIBRARIES}
  )
set_property(TARGET parsian PROPERTY CXX_STANDARD 14)

if(WIN32)
  if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    include_directories(../extlibs/openssl/include)
  else()
    include_directories(../extlibs/openssl/include64)
  endif()
  add_definitions(-D_WIN32_WINNT=0x0500 -D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif()
