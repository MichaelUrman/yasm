YASM_ADD_MODULE(dbgfmt_dwarf2
    dbgfmts/dwarf2/dwarf2-dbgfmt.c
    dbgfmts/dwarf2/dwarf2-line.c
    dbgfmts/dwarf2/dwarf2-aranges.c
    dbgfmts/dwarf2/dwarf2-info.c
    )

YASM_ADD_OUT_TEST(dwarf2_gen64_test modules/dbgfmts/dwarf2/tests/gen64 "dwarf2 dbgfmt gen64" "-f elf64 -g dwarf2" ".o")
YASM_ADD_OUT_TEST(dwarf2_pass32_test modules/dbgfmts/dwarf2/tests/pass32 "dwarf2 dbgfmt pass32" "-f elf -p gas -g dwarf2" ".o")
YASM_ADD_OUT_TEST(dwarf2_pass64_test modules/dbgfmts/dwarf2/tests/pass64 "dwarf2 dbgfmt pass64" "-f elf64 -p gas -g dwarf2" ".o")
YASM_ADD_OUT_TEST(dwarf2_passwin64_test modules/dbgfmts/dwarf2/tests/passwin64 "dwarf2 dbgfmt passwin64" "-f win64 -p gas -g dwarf2" ".o")
