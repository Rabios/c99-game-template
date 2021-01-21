cmake_minimum_required(VERSION 3.1)
project(c99-game-template LANGUAGES C)
set(CMAKE_C_STANDARD 99)

# Globals
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MAIN "${SRC_DIR}/main.c")
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLAD_DIR "${LIB_DIR}/glad")
set(MA_DIR "${LIB_DIR}/miniaudio")
set(STB_DIR "${LIB_DIR}/stb")
set(PHYSAC_DIR "${LIB_DIR}/physac")
set(TINYOBJ_DIR "${LIB_DIR}/tinyobj")
set(ENET_DIR "${LIB_DIR}/enet")

# Build all
add_executable(${PROJECT_NAME} ${MAIN} "${TINYOBJ_DIR}/tinyobj_loader_c.h" "${ENET_DIR}/enet.h" "${PHYSAC_DIR}/physac.h" "${MA_DIR}/miniaudio.h" "${MA_DIR}/miniaudio_engine.h" "${STB_DIR}/stb_image.h" "${STB_DIR}/stb_truetype.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC)

# GLAD
add_subdirectory(${GLAD_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE "glad" ${GLAD_LIBS})

# GLFW
add_subdirectory(${GLFW_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")
target_link_libraries(${PROJECT_NAME} PRIVATE "glfw" ${GLFW_LIBS})
