cmake_minimum_required(VERSION 2.8.9)

PROJECT (Naumaxia)

# find_package(OpenGL REQUIRED)
# include_directories(${OPENGL_INCLUDE_DIR})
# find_package(GLUT REQUIRED)
# include_directories(${GLUT_INCLUDE_DIR})

FILE(GLOB SOURCE_FILES *.h *.cpp)
SET(SRC ${SOURCE_FILES})

ADD_EXECUTABLE (naumaxia ${SRC})

# target_link_libraries(naumaxia ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
