#!/bin/bash
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# ------------------------------------------------------------------------
# Input arguments
# ------------------------------------------------------------------------
TEST_TYPE=$1                   # First argument: which test type to build/run
SUNSPEC_ROOT_DIR=$2        # Second argument: root directory of the project
BACKEND=$3
TESTS_TO_RUN=$4

# ------------------------------------------------------------------------
# Derived directories
# ------------------------------------------------------------------------
SOURCE_DIR="$SUNSPEC_ROOT_DIR/tests/${TEST_TYPE}"      # Path to the source directory for the selected test type
BUILD_DIR="$SUNSPEC_ROOT_DIR/build/tests/${TEST_TYPE}" # Path to the build directory for the selected test type
PICOTOOL_PATH=${HOME}/.pico-sdk/picotool/2.2.0/picotool/picotool
# ------------------------------------------------------------------------
# Color definitions for terminal output
# ------------------------------------------------------------------------
RED='\033[0;31m'        # Red text (used for errors)
GREEN='\033[0;32m'      # Green text (success messages)
YELLOW='\033[1;33m'     # Yellow text (warnings)
BLUE='\033[0;34m'       # Blue text
MAGENTA='\033[0;35m'    # Magenta text
NC='\033[0m'            # No Color / reset
BOLD='\033[1m'
BG_BLUE='\033[44m'
BOLD_RED='\033[1;31m'
BOLD_GREEN='\033[1;32m'

function run_test(){
    local TEST_TO_RUN=$1

    if [[ ${TEST_TYPE,,} == "target" ]]; then
    # Target test selected
    # A more complex logic is needed for target to know when the test was successful and to start flashing the new code.
        ${PICOTOOL_PATH} load -fx ${BUILD_DIR}/${TEST_TO_RUN}/${TEST_TO_RUN}_test.uf2
    else
    # Host test selected
        if [[ -f "${BUILD_DIR}/${TEST_TO_RUN}/${TEST_TO_RUN}_test" ]]; then
            "${BUILD_DIR}/${TEST_TO_RUN}/${TEST_TO_RUN}_test"
        else
            echo -e "${BOLD_RED}Program ${BUILD_DIR}/${TEST_TO_RUN}/${TEST_TO_RUN}_test not found${NC}"
        fi
    fi
}

source $SCRIPT_DIR/dual_target_test_build.sh $1 $2 $3 

if [[ $? -ne 0 ]]; then
    echo -e "${BOLD_RED}Build failed!!! :(${NC}"
    exit 1
else
    echo -e "${GREEN}Building $TEST_TYPE tests Successfully${NC}"

    if [[ -z $TESTS_TO_RUN ]]; then
        echo -e "${MAGENTA}No test to be run.${NC}"
    else
        for TEST_TO_RUN in $TESTS_TO_RUN; do
            echo -e "${MAGENTA}Now Running ${TEST_TO_RUN^^} test on ${TEST_TYPE^^}${NC}"
            run_test $TEST_TO_RUN
            if [[ $? -ne 0 ]]; then
                echo -e "${BOLD_RED}${TEST_TO_RUN^^} test on ${TEST_TYPE^^} FAILED!!! :(${NC}"
                exit 1
            else
                echo -e "${BOLD_GREEN}${TEST_TO_RUN^^} test on ${TEST_TYPE^^} passed successfully :)${NC}"
            fi
        done
    fi
fi