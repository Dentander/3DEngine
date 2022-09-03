# ======== PROJECT ========
cmake_minimum_required(VERSION 3.16)
project(3DEngine)
set(CMAKE_CXX_STANDARD 17)
add_executable(3DEngine main.cpp engine/math/vec2.h engine/math/vec3.h engine/graphics/Engine.cpp engine/graphics/Engine.h engine/settings/PlayerControls.h engine/patterns/Singleton.h engine/graphics/Input.cpp engine/graphics/Input.h engine/graphics/Camera.cpp engine/graphics/Camera.h engine/graphics/Transform.cpp engine/graphics/Transform.h engine/objects/Object.cpp engine/objects/Object.h engine/objects/Scene.cpp engine/objects/Scene.h engine/objects/Sphere.cpp engine/objects/Sphere.h engine/graphics/OutputShader.cpp engine/graphics/OutputShader.h)

# ======== SFML ========
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/SFML-2.5.1/include)
target_link_libraries(3DEngine sfml-system sfml-window sfml-graphics sfml-audio)

# ======== PYTHON ========
find_package(PythonInterp REQUIRED)
add_custom_target(
        run ALL
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/build.py ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_BINARY_DIR}
)
add_dependencies(3DEngine run)