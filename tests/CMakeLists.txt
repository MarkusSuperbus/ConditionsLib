set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(ConditionsLib REQUIRED)

find_library(NTL ntl)
if(NOT NTL)
  message(FATAL_ERROR "Could not find the ntl library. Set CMAKE_LIBRARY_PATH appropriately.")
else()
  message("Ntl libary located in ${NTL}")
endif()

find_library(GMP gmp)
if(NOT GMP)
  message(FATAL_ERROR "Could not find the gmp library. Set CMAKE_LIBRARY_PATH appropriately.")
else()
  message("Gmp libary located in ${GMP}")
endif()

add_library(TestingUtils utils/Cons.hpp utils/Cons.cc)

add_executable(MinLeavesTest MinLeavesTest.cc)
target_link_libraries(MinLeavesTest ConditionsLib::ConditionsLib TestingUtils ${NTL} ${GMP} Threads::Threads GTest::gtest_main)

gtest_discover_tests(MinLeavesTest)
