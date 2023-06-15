include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(UU_Encode_test UU_Encode_test.c)

target_link_libraries(UU_Encode_test
  PRIVATE
  GTest::GTest
  Encoders)

add_test(UU_Encode_gtests UU_Encode_test)