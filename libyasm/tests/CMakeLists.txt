ADD_EXECUTABLE(bitvect_test bitvect_test.c)
TARGET_LINK_LIBRARIES(bitvect_test yasmstd libyasm)
add_test(NAME bitvect_test COMMAND bitvect_test)

ADD_EXECUTABLE(floatnum_test floatnum_test.c)
TARGET_LINK_LIBRARIES(floatnum_test yasmstd libyasm)
add_test(NAME floatnum_test COMMAND floatnum_test)

ADD_EXECUTABLE(leb128_test leb128_test.c)
TARGET_LINK_LIBRARIES(leb128_test yasmstd libyasm)
add_test(NAME leb128_test COMMAND leb128_test)

ADD_EXECUTABLE(splitpath_test splitpath_test.c)
TARGET_LINK_LIBRARIES(splitpath_test yasmstd libyasm)
add_test(NAME splitpath_test COMMAND splitpath_test)

ADD_EXECUTABLE(combpath_test combpath_test.c)
TARGET_LINK_LIBRARIES(combpath_test yasmstd libyasm)
add_test(NAME combpath_test COMMAND combpath_test)

ADD_EXECUTABLE(uncstring_test uncstring_test.c)
TARGET_LINK_LIBRARIES(uncstring_test yasmstd libyasm)
add_test(NAME uncstring_test COMMAND uncstring_test)

YASM_ADD_OUT_TEST(libyasm_test libyasm/tests "libyasm" "-f bin" "")
