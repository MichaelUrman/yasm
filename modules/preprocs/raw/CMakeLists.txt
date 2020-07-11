YASM_ADD_MODULE(preproc_raw
    preprocs/raw/raw-preproc.c
    )

YASM_ADD_OUT_TEST(rawpp_test modules/preprocs/raw/tests "raw preproc" "-f bin -r raw" "")
