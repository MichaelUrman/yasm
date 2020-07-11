YASM_ADD_MODULE(objfmt_xdf
    objfmts/xdf/xdf-objfmt.c
    )

YASM_ADD_OUT_TEST(xdf_test modules/objfmts/xdf/tests "xdf objfmt" "-f xdf" ".xdf")
