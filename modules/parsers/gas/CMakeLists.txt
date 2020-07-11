YASM_RE2C(
    ${CMAKE_CURRENT_SOURCE_DIR}/parsers/gas/gas-token.re
    ${CMAKE_CURRENT_BINARY_DIR}/gas-token.c
    -b
    )

YASM_ADD_MODULE(parser_gas
    parsers/gas/gas-parser.c
    parsers/gas/gas-parse.c
    parsers/gas/gas-parse-intel.c
    gas-token.c
    )

YASM_ADD_OUT_TEST(gas_test modules/parsers/gas/tests "gas-compat parser" "-f elf -p gas" ".o")
YASM_ADD_OUT_TEST(gas_bin_test modules/parsers/gas/tests/bin "gas-compat parser bin output" "-f bin -p gas" "")
