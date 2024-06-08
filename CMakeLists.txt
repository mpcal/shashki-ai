cmake_minimum_required(VERSION 3.12)

project(shashki_ai LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-15)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -g -march=native")  # assertions still enabled

# set include and library directories
include_directories(include)
link_directories(lib)

# find sources
file(GLOB_RECURSE SOURCES src/*.cc src/**/*.cc)

# find external objects libraries to link in
file(GLOB_RECURSE OBJS lib/*.o)
SET_SOURCE_FILES_PROPERTIES(
  ${OBJS}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

# declare executable
add_executable(shashki_ai ${OBJS} ${SOURCES})

# Pistache: link statically
target_include_directories(shashki_ai PRIVATE pistache/prefix/include)
target_link_directories(shashki_ai PRIVATE pistache/build/src)
target_link_libraries(shashki_ai PRIVATE pistache)

# Eigen3 (header-only), only needed when building against CMA-ES (global optimization
# technique), see `experimental` directory for details
#
# find_package(Eigen3 3.3 REQUIRED)
# target_link_libraries(shashki_ai Eigen3::Eigen)

# Catboost model loader, only needed when we use Yandex's gradient boosting framework,
# see `experimental` dir; libcatboostmodel.so needs to be built separately
#
# target_link_libraries(shashki_ai catboostmodel)
