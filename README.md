# bowling-game
## Prerequisites
I was on macos and below are commands. Use package manager as per your system.
    1. cmake should be installed
        '''
            brew install cmake
        '''
    2. gtest, gcov and lcov should be installed
        '''
            brew install googletest
            brew install lcov
        '''
        gcov is already pesent with most of the systems
## CMakeLists.txt
    'set(CMAKE_CXX_STANDARD 17)' was required for the gtest version installed. If required make changes in this version
    As per your system change below paths
    '''
    set(GTEST_INCLUDE_DIR /opt/homebrew/opt/googletest/include)
    set(GTEST_LIB_DIR /opt/homebrew/opt/googletest/lib)
    '''

## Steps to build
*'mkdir build'
*'cd build'
*'cmake ..'
*'make'

*To execute the program
    './BowlingGameExecutable'

*To run all test cases
    './AllTests'

*To get code coverage report
    'make coverage'
    Go to path build/reports/html/src/index.html
    This will give you a complete code coverage, line coverage, function coverage report as per the unit test cases