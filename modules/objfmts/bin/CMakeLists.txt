YASM_ADD_MODULE(objfmt_bin
    objfmts/bin/bin-objfmt.c
    )

YASM_ADD_OUT_TEST(bin_test modules/objfmts/bin/tests "bin objfmt" "-f bin" "")
#TODO: YASM_ADD_OUT_TEST(bin_multi_test modules/objfmts/bin/tests/multisect ...)
