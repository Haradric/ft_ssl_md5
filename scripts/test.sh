#!/bin/bash
. ../tests/common.sh
. ../tests/test_md5.sh
. ../tests/test_sha256.sh

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
test_md5_13
test_md5_14
test_md5_15

test_sha256_01
test_sha256_02
test_sha256_03
test_sha256_04
test_sha256_05
test_sha256_06
test_sha256_07
test_sha256_08
test_sha256_09
test_sha256_10
test_sha256_11
test_sha256_12
test_sha256_13
test_sha256_14
test_sha256_15
