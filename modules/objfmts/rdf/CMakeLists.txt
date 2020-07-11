YASM_ADD_MODULE(objfmt_rdf
    objfmts/rdf/rdf-objfmt.c
    )

YASM_ADD_OUT_TEST(rdf_test modules/objfmts/rdf/tests "rdf objfmt" "-f rdf" ".rdf")
