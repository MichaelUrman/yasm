YASM_GENMACRO(
    ${CMAKE_CURRENT_SOURCE_DIR}/parsers/nasm/nasm-std.mac
    ${CMAKE_CURRENT_BINARY_DIR}/nasm-macros.c
    nasm_standard_mac
    )

SET_SOURCE_FILES_PROPERTIES(parsers/nasm/nasm-parser.c PROPERTIES
    OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/nasm-macros.c
    )

YASM_RE2C(
    ${CMAKE_CURRENT_SOURCE_DIR}/parsers/nasm/nasm-token.re
    ${CMAKE_CURRENT_BINARY_DIR}/nasm-token.c
    -b
    )

YASM_ADD_MODULE(parser_nasm
    parsers/nasm/nasm-parser.c
    parsers/nasm/nasm-parse.c
    nasm-token.c
    )

YASM_ADD_OUT_TEST(nasm_test modules/parsers/nasm/tests "nasm-compat parser" "-f bin" "")
YASM_ADD_OUT_TEST(nasm_worphan_test modules/parsers/nasm/tests/worphan "nasm-compat parser" "-Worphan-labels -f bin" "")
