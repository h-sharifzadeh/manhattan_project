cmake_minimum_required(VERSION 3.1)
project(DELFT_SOCCER)

add_library(geom
        geom/src/angle_deg.cpp
        geom/src/vector_2d.cpp
        geom/src/triangle_2d.cpp
        geom/src/segment_2d.cpp
        geom/src/sector_2d.cpp
        geom/src/rect_2d.cpp
        geom/src/ray_2d.cpp
        geom/src/polygon_2d.cpp
        geom/src/matrix_2d.cpp
        geom/src/line_2d.cpp
        geom/src/convex_hull.cpp
        geom/src/circle_2d.cpp
        )

add_library(soccer
        common/ai_base.cpp
        soccer/src/soccer.cpp
        soccer/src/skills/kick.cpp
        soccer/src/skills/fast.cpp
        soccer/src/skills/move.cpp
        soccer/src/control.cpp
        soccer/src/roles/defense.cpp
        soccer/src/roles/attacker.cpp
        soccer/src/roles/gk.cpp
        soccer/src/coach.cpp
        soccer/include/field.h soccer/include/worldmodel.h soccer/include/gamestate.h)

add_executable(DELFT_SOCCER  soccer/src/main.cpp)

find_package(Threads REQUIRED)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS random regex system thread) # VC require regex, don't know why

include_directories(
        common
        geom/include
        extlibs/autobahn-cpp/include
        extlibs/msgpack-c/include
        soccer/include
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(
        DELFT_SOCCER
        Threads::Threads
        geom
        soccer
        ${Boost_LIBRARIES}
)

set_property(TARGET DELFT_SOCCER PROPERTY CXX_STANDARD 14)

if(WIN32)
  if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    include_directories(../extlibs/openssl/include)
  else()
    include_directories(../extlibs/openssl/include64)
  endif()
  add_definitions(-D_WIN32_WINNT=0x0500 -D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif()
