cmake_minimum_required(VERSION 3.22)
project(PongProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(PongProject src/main.cpp src/Game/GameController.cpp src/Game/GameController.h src/Controller/Controller.cpp src/Controller/Controller.h src/Loop/Loop.cpp src/Loop/Loop.h src/Time/Time.cpp src/Time/Time.h src/Events/EventManager.cpp src/Events/EventManager.h src/Screen/Screen.cpp src/Screen/Screen.h src/Error/Error.cpp src/Error/Error.h src/Entity/Entity.cpp src/Entity/Entity.h src/Entity/Collider.cpp src/Entity/Collider.h src/Console/ConsoleMessage.cpp src/Console/ConsoleMessage.h src/Static.h src/Structs/HierarchyTree.h src/Coords/Coordinates.cpp src/Coords/Coordinates.h src/Misc.cpp src/Misc.h src/Screen/Layer.cpp src/Screen/Layer.h src/Structs/Geometry.cpp src/Structs/Geometry.h src/Structs/Borrowed.cpp src/Structs/Borrowed.h)


find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${SDL2_CFLAGS_OTHER})