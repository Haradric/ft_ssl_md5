#!/bin/bash

tests=15

test_sha256_01()
{
    result="$(echo "pickle rick" | $EXECUTABLE sha256 2>&1)"
    reference=$'a9c55180c67a4bc62753d836843f46fa47af28874600cdc637de921d711937ed'
    result_compare "$result" "$reference"
}

test_sha256_02()
{
    result="$(echo "Do not pity the dead, Harry." | $EXECUTABLE sha256 -p 2>&1)"
    reference=$'Do not pity the dead, Harry.\n7197000d32ca5a13cf923ba196286a72daa06e9f168c4dd5753f917568ea373f'
    result_compare "$result" "$reference"
}

test_sha256_03()
{
    result="$(echo "Pity the living." | $EXECUTABLE sha256 -q -r 2>&1)"
    reference=$'40133cfe543247c1cae0ffb0003c1179ce9fb0046bee19f9fca167380643ba45'
    result_compare "$result" "$reference"
}

test_sha256_04()
{
    echo "And above all," > file
    result="$($EXECUTABLE sha256 file 2>&1)"
    reference=$'SHA256(file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_05()
{
    result="$($EXECUTABLE sha256 -s "pity those that aren't following baerista on spotify." 2>&1)"
    reference=$'SHA256("pity those that aren\'t following baerista on spotify.") = 7838c25c9debff86c584245d67b429186d3850c89da31c0b49b8d0380a3e14bf'
    result_compare "$result" "$reference"
}

test_sha256_06()
{
    echo "And above all," > file
    result="$(echo "be sure to handle edge cases carefully" | $EXECUTABLE sha256 -p file 2>&1)"
    reference=$'be sure to handle edge cases carefully\nef9241f878a1da676104a81239792a2817bc0390a427ca20bad1a59030fd20c2\nSHA256(file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_07()
{
    echo "And above all," > file
    result="$(echo "some of this will not make sense at first" | $EXECUTABLE sha256 file 2>&1)"
    reference=$'SHA256(file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_08()
{
    echo "And above all," > file
    result="$(echo "some of this will not make sense at first" | $EXECUTABLE sha256 -r file 2>&1)"
    reference=$'f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_09()
{
    echo "And above all," > file
    result="$(echo "but eventually you will understand" | $EXECUTABLE sha256 -p -r file 2>&1)"
    reference=$'but eventually you will understand\n43da940057fd3b7453ee91b3a056a41343e6f0bce315570ed27e06c993a539da\nf9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_10()
{
    echo "And above all," > file
    result="$(echo "GL HF let's go" | $EXECUTABLE sha256 -p -s "foo" file 2>&1)"
    reference=$'GL HF let\'s go\nf33201f3d70c9dccccec022e2ff0df2006e016f153f600407917d14955fbec22\nSHA256("foo") = 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae\nSHA256(file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_11()
{
    echo "And above all," > file
    result="$(echo "one more thing" | $EXECUTABLE sha256 -r -p -s "foo" file -s "bar" 2>&1)"
    reference=$'one more thing\n720bbf63077e0bea3b70c87954123daa6fcf32f973f4d646622bd016b140ec75\n2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae "foo"\nf9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file\nft_ssl: sha256: No such file or directory: -s\nft_ssl: sha256: No such file or directory: bar'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_12()
{
    echo "And above all," > file
    result="$(echo "just to be extra clear" | $EXECUTABLE sha256 -r -q -p -s "foo" file 2>&1)"
    reference=$'just to be extra clear\n41c3da28172faf72bb777d6a428b6d801427d02513c56cd9e3672f44383f8eee\n2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae\nf9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_13()
{
    echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > file
    result="$($EXECUTABLE sha256 -q file 2>&1)"
    reference=$'a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_14()
{
    echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > file
    result="$($EXECUTABLE sha256 file 2>&1)"
    reference=$'SHA256(file) = a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9'
    rm -f file
    result_compare "$result" "$reference"
}

test_sha256_15()
{
    result="$($EXECUTABLE sha256 -s "wubba lubba dub dub" 2>&1)"
    reference=$'SHA256("wubba lubba dub dub") = 23a0944d11b5a54f1970492b5265c732044ae824b7d5656acb193e7f0e51e5fa'
    result_compare "$result" "$reference"
}

