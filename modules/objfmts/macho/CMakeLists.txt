YASM_ADD_MODULE(objfmt_macho
    objfmts/macho/macho-objfmt.c
    )
list(APPEND YASM_MODULES objfmt_macho32)
list(APPEND YASM_MODULES objfmt_macho64)

YASM_ADD_OUT_TEST(macho_gas32_test modules/objfmts/macho/tests/gas32 "GAS 32-bit macho objfmt" "-f macho32 -p gas" ".o")
YASM_ADD_OUT_TEST(macho_gas64_test modules/objfmts/macho/tests/gas64 "GAS 64-bit macho objfmt" "-f macho64 -p gas" ".o")
YASM_ADD_OUT_TEST(macho_nasm32_test modules/objfmts/macho/tests/nasm32 "32-bit macho objfmt" "-f macho32" ".o")
YASM_ADD_OUT_TEST(macho_nasm64_test modules/objfmts/macho/tests/nasm64 "64-bit macho objfmt" "-f macho64" ".o")
