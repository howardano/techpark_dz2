#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck static_lib --enable=all --inconclusive --error-exitcode=1 -I static_lib --suppress=missingIncludeSystem --suppress=unusedFunction" "\(information\)"

#print_header "RUN clang-tidy"
#check_log "clang-tidy static_lib/*.c static_lib/*.h -extra-arg=-std=c99 -- -Istatic_lib" "Error (?:reading|while processing)"

print_header "SUCCESS"