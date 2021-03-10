cmake_minimum_required(VERSION 3.12)

project(shashki_ai LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-10)
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

# statically link against Pistache
set(Pistache_DIR ~/opt/libpistache-210114/lib/cmake/pistache)
find_package(Pistache REQUIRED)
target_include_directories(shashki_ai PRIVATE ${Pistache_INCLUDE_DIRS})
target_link_libraries(shashki_ai ${Pistache_LIBRARIES}/libpistache-0.0.002-git20210107.so.0.0)

# Eigen3 (header-only), only needed when building against CMA-ES (global optimization
# technique), see `experimental` directory for details
#
# find_package(Eigen3 3.3 REQUIRED)
# target_link_libraries(shashki_ai Eigen3::Eigen)

# Catboost model loader, only needed when we use Yandex's gradient boosting framework,
# see `experimental` dir; libcatboostmodel.so needs to be built separately
#
# target_link_libraries(shashki_ai catboostmodel)
