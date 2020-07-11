YASM_ADD_MODULE(dbgfmt_stabs
    dbgfmts/stabs/stabs-dbgfmt.c
    )

YASM_ADD_OUT_TEST(stabs_test modules/dbgfmts/stabs/tests "stabs dbgfmt" "-f elf -g stabs" ".o")
