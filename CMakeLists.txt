cmake_minimum_required(VERSION 3.10)
project(BowlingGameTest)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

# ------------------------------
# Coverage flags
# ------------------------------
option(CODE_COVERAGE "Enable code coverage support" ON)

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Enabling code coverage flags")
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

# ------------------------------
# GTest
# ------------------------------
set(GTEST_INCLUDE_DIR /opt/homebrew/opt/googletest/include)
set(GTEST_LIB_DIR /opt/homebrew/opt/googletest/lib)

include_directories(${GTEST_INCLUDE_DIR} src)
link_directories(${GTEST_LIB_DIR})

# ------------------------------
# Application target
# ------------------------------
add_executable(BowlingGameExecutable
    main.cpp
    src/Player.cpp
    src/Frame.cpp
    src/BowlingGame.cpp
)

# ------------------------------
# Test target
# ------------------------------
add_executable(AllTests
    tests/PlayerTest.cpp
    tests/FrameTest.cpp
    tests/BowlingGameTest.cpp
    src/Player.cpp
    src/Frame.cpp
    src/BowlingGame.cpp
)

target_link_libraries(AllTests gtest gtest_main pthread)
add_test(NAME AllTests COMMAND AllTests)

# ------------------------------
# Coverage target
# ------------------------------
if(CODE_COVERAGE)
    find_program(LCOV_EXECUTABLE lcov)
    find_program(GENHTML_EXECUTABLE genhtml)

    if(LCOV_EXECUTABLE AND GENHTML_EXECUTABLE)
            add_custom_target(coverage
            COMMENT "Generating coverage report in reports/html..."
            COMMAND ${LCOV_EXECUTABLE} --directory . --capture --output-file coverage.info
                    --ignore-errors inconsistent,format,unsupported,deprecated
                    --branch-coverage
            COMMAND ${LCOV_EXECUTABLE} --remove coverage.info '/opt/*' '*/tests/*' '/usr/*' '*gtest*' '*main.cpp*'
                    --output-file coverage.cleaned.info --ignore-errors unused
            COMMAND ${GENHTML_EXECUTABLE} coverage.cleaned.info --output-directory reports/html
            COMMAND ${CMAKE_COMMAND} -E remove coverage.info coverage.cleaned.info
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS AllTests
        )

    else()
        message(WARNING "lcov or genhtml not found. Coverage target will not be available.")
    endif()
endif()
