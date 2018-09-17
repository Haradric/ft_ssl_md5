#!/bin/bash
. ../tests/common.sh
. ../tests/test_md5.sh

BASEDIR="$(echo "$(cd "$(dirname "$0")/.."; pwd)")"
EXECUTABLE="$BASEDIR/ft_ssl"

[ -f $EXECUTABLE ] || {
    echo "ft_ssl file not found." >&2
    exit 1
}

test_md5_01
test_md5_02
test_md5_03
test_md5_04
test_md5_05
test_md5_06
test_md5_07
test_md5_08
test_md5_09
test_md5_10
test_md5_11
test_md5_12
