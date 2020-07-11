YASM_ADD_MODULE(objfmt_elf
    objfmts/elf/elf.c
    objfmts/elf/elf-objfmt.c
    objfmts/elf/elf-x86-x86.c
    objfmts/elf/elf-x86-amd64.c
    objfmts/elf/elf-x86-x32.c
    )
list(APPEND YASM_MODULES objfmt_elf32)
list(APPEND YASM_MODULES objfmt_elf64)
list(APPEND YASM_MODULES objfmt_elfx32)

YASM_ADD_OUT_TEST(elf_test modules/objfmts/elf/tests "elf objfmt" "-f elf" ".o")
YASM_ADD_OUT_TEST(elf_x32_test modules/objfmts/elf/tests/x32 "elf-x32 objfmt" "-f elf -m x32" ".o")
YASM_ADD_OUT_TEST(elf_amd64_test modules/objfmts/elf/tests/amd64 "elf-amd64 objfmt" "-m amd64 -f elf" ".o")
YASM_ADD_OUT_TEST(elf_gas32_test modules/objfmts/elf/tests/gas32 "GAS elf-x86 objfmt" "-f elf32 -p gas" ".o")
YASM_ADD_OUT_TEST(elf_gas64_test modules/objfmts/elf/tests/gas64 "GAS elf-amd64 objfmt" "-f elf64 -p gas" ".o")
YASM_ADD_OUT_TEST(elf_gasx32_test modules/objfmts/elf/tests/gasx32 "GAS elf-x32 objfmt" "-f elfx32 -p gas" ".o")
