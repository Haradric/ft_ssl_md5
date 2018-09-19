#!/bin/bash

tests=15

test_md5_01()
{
    result="$(echo "pickle rick" | $EXECUTABLE md5 2>&1)"
    reference=$'c5e433c1dbd7ba01e3763a9483e74b04'
    result_compare "$result" "$reference"
}

test_md5_02()
{
    result="$(echo "Do not pity the dead, Harry." | $EXECUTABLE md5 -p 2>&1)"
    reference=$'Do not pity the dead, Harry.\n2d95365bc44bf0a298e09a3ab7b34d2f'
    result_compare "$result" "$reference"
}

test_md5_03()
{
    result="$(echo "Pity the living." | $EXECUTABLE md5 -q -r 2>&1)"
    reference=$'e20c3b973f63482a778f3fd1869b7f25'
    result_compare "$result" "$reference"
}

test_md5_04()
{
    echo "And above all," > file
    result="$($EXECUTABLE md5 file 2>&1)"
    reference=$'MD5(file) = 53d53ea94217b259c11a5a2d104ec58a'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_05()
{
    result="$($EXECUTABLE md5 -s "pity those that aren't following baerista on spotify." 2>&1)"
    reference=$'MD5("pity those that aren\'t following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f'
    result_compare "$result" "$reference"
}

test_md5_06()
{
    echo "And above all," > file
    result="$(echo "be sure to handle edge cases carefully" | $EXECUTABLE md5 -p file 2>&1)"
    reference=$'be sure to handle edge cases carefully\n3553dc7dc5963b583c056d1b9fa3349c\nMD5(file) = 53d53ea94217b259c11a5a2d104ec58a'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_07()
{
    echo "And above all," > file
    result="$(echo "some of this will not make sense at first" | $EXECUTABLE md5 file 2>&1)"
    reference=$'MD5(file) = 53d53ea94217b259c11a5a2d104ec58a'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_08()
{
    echo "And above all," > file
    result="$(echo "some of this will not make sense at first" | $EXECUTABLE md5 -r file 2>&1)"
    reference=$'53d53ea94217b259c11a5a2d104ec58a file'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_09()
{
    echo "And above all," > file
    result="$(echo "but eventually you will understand" | $EXECUTABLE md5 -p -r file 2>&1)"
    reference=$'but eventually you will understand\ndcdd84e0f635694d2a943fa8d3905281\n53d53ea94217b259c11a5a2d104ec58a file'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_10()
{
    echo "And above all," > file
    result="$(echo "GL HF let's go" | $EXECUTABLE md5 -p -s "foo" file 2>&1)"
    reference=$'GL HF let\'s go\nd1e3cc342b6da09480b27ec57ff243e2\nMD5("foo") = acbd18db4cc2f85cedef654fccc4a4d8\nMD5(file) = 53d53ea94217b259c11a5a2d104ec58a'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_11()
{
    echo "And above all," > file
    result="$(echo "one more thing" | $EXECUTABLE md5 -r -p -s "foo" file -s "bar" 2>&1)"
    reference=$'one more thing\na0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 "foo"\n53d53ea94217b259c11a5a2d104ec58a file\nft_ssl: No such file or directory: -s\nft_ssl: No such file or directory: bar'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_12()
{
    echo "And above all," > file
    result="$(echo "just to be extra clear" | $EXECUTABLE md5 -r -q -p -s "foo" file 2>&1)"
    reference=$'just to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8\n53d53ea94217b259c11a5a2d104ec58a'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_13()
{
    echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > file
    result="$($EXECUTABLE md5 -q file 2>&1)"
    reference=$'b1cfd03666d9473ce32e0d7c31d00203'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_14()
{
    echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > file
    result="$($EXECUTABLE md5 file 2>&1)"
    reference=$'MD5(file) = b1cfd03666d9473ce32e0d7c31d00203'
    rm -f file
    result_compare "$result" "$reference"
}

test_md5_15()
{
    result="$($EXECUTABLE md5 -s "wubba lubba dub dub" 2>&1)"
    reference=$'MD5("wubba lubba dub dub") = 914ebdda4b3f36685a4dd8b3421197a3'
    result_compare "$result" "$reference"
}

