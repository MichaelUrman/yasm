YASM_RE2C(
    ${CMAKE_CURRENT_SOURCE_DIR}/arch/lc3b/lc3bid.re
    ${CMAKE_CURRENT_BINARY_DIR}/lc3bid.c
    -s
    )

YASM_ADD_MODULE(arch_lc3b
    arch/lc3b/lc3barch.c
    arch/lc3b/lc3bbc.c
    lc3bid.c
    )

YASM_ADD_OUT_TEST(lc3b_test modules/arch/lc3b/tests "lc3b arch" "-a lc3b -f bin" "")
