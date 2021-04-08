# SPDX-License-Identifier: Apache-2.0

wasmedge_add_executable(wasiTests
  wasi.cpp
)

add_test(wasiTests wasiTests)

target_link_libraries(wasiTests
  PRIVATE
  ${GTEST_BOTH_LIBRARIES}
  wasmedgeHostModuleWasi
)

if(WASMEDGE_BUILD_COVERAGE)
  add_test(
    NAME wasi-test
    COMMAND bash -c "[ -e \"$HOME/.cargo/env\" ] && . \"$HOME/.cargo/env\"; \"${PROJECT_SOURCE_DIR}\"/utils/wasi-test/run-wasi-test.sh \"${PROJECT_BINARY_DIR}/tools/wasmedge\""
  )
endif()

add_test(NAME wasiSocketTests
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/socketTests.py)

set(DEFS PORT=5566 BUF_SIZE=1024)

add_executable(TCPclient socket/TCPclient.cpp)
target_compile_definitions(TCPclient PRIVATE ${DEFS})

add_executable(TCPserver socket/TCPserver.cpp)
target_compile_definitions(TCPserver PRIVATE ${DEFS})
