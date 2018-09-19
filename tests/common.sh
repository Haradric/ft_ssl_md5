#!/bin/bash

result_compare() {

    return=1
    [ "$1" = "$2" ] && {
        sleep 0
        #echo "TEST ${FUNCNAME[1]} PASSED"
    } || {
        echo "----------------"
        echo "TEST ${FUNCNAME[1]} FAILDED"
        printf "expected:\n%s\noutput  :\n%s\n" "$2" "$1"
        echo "----------------"
    }

}
