# Setup testing
enable_testing()
message(STATUS "Enable testing with GoogleTest")
set(TEST_NAME ${CMAKE_PROJECT_NAME}_test)

add_executable(${TEST_NAME})
target_sources(
  ${TEST_NAME} PRIVATE
  test_main.cpp
  TextBufferTest.cpp
  CursorManagerTest.cpp
  ScreenRendererTest.cpp
  MoveCursorCommandsTest.cpp
  EditorControlCommandsTest.cpp
  ModifyTextCommandsTest.cpp
)

target_include_directories(
  ${TEST_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src/ObserverPattern
  ${CMAKE_SOURCE_DIR}/src/TextBuffer
  ${CMAKE_SOURCE_DIR}/src/CursorManager
  ${CMAKE_SOURCE_DIR}/src/ScreenRenderer
  ${CMAKE_SOURCE_DIR}/src/InputHandler
)

target_link_libraries(
  ${TEST_NAME} PRIVATE
  GTest::gtest_main
  GTest::gmock_main
  TextBuffer
  CursorManager
  ScreenRenderer
  InputHandler
  CommandPattern
)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

add_custom_target(
  ${TEST_NAME}_execution ALL
  DEPENDS ${TEST_NAME}
)

add_custom_command(
  TARGET ${TEST_NAME}_execution
  POST_BUILD
  COMMAND ctest --output-on-failure
  VERBATIM
)
