#! /bin/sh

YASM_TEST_SUITE=1
export YASM_TEST_SUITE

asm="$2"
args="$3"
obj="$4"

a=`echo ${asm} | sed 's,^.*/,,;s,.asm$,,'`
test="$1/${a}"
o=results/${a}${obj}
oh=results/${a}.hx
og=`echo ${asm} | sed 's,.asm$,.hex,'`
e=results/${a}.ew
eg=`echo ${asm} | sed 's,.asm$,.errwarn,'`
m=results/${a}.map
mg=`echo ${asm} | sed 's,.asm$,.map,'`
mf=
if test -f ${mg}; then
    mf=--mapfile=${m}
fi
if test \! -f ${eg}; then
    eg=/dev/null
fi

# Run within a subshell to prevent signal messages from displaying.
sh -c "cat ${asm} | ${YASM:=./yasm} ${args} ${mf} -o ${o} - 2>${e}" >/dev/null 2>/dev/null
status=$?
if test $status -gt 128; then
    # We should never get a coredump!
    echo "  ${test}: crashed!"
    exit 2
elif test $status -gt 0; then
    if echo ${asm} | grep -v err >/dev/null; then
        echo "  *** ${test}: returned unexpected error (code ${status})"
        diff -u -w /dev/null ${e} | head -n 30 | sed 's/^/    /'
        exit 1
    elif ! diff -w ${eg} ${e} >/dev/null; then
        echo "  *** ${test}: errors and warnings did not match"
        diff -u -w ${eg} ${e} --label="want: ${eg##${srcdir}/}" --label="got: ${e}" | head -n 30 | sed 's/^/    /'
        exit 1
    else
        exit 0
    fi
fi

if echo ${asm} | grep err >/dev/null; then
    # YASM didn't detect errors but should have!
    echo "  *** ${test}: did not return an error code!"
    diff -u -w ${eg} /dev/null | head -n 30 | sed 's/^/    /'
    exit 1
fi

status=0
# Verify warnings
if ! diff -w ${eg} ${e} >/dev/null; then
    status=1
    echo "  *** ${test}: warnings did not match"
    diff -u -w ${eg} ${e} --label="want: ${eg##${srcdir}/}" --label="got: ${e}" | head -n 30 | sed 's/^/    /'
fi

# Verify object file
${TEST_HD:=./test_hd} ${o} > ${oh}
if ! diff -w ${og} ${oh} >/dev/null; then
    status=1
    echo "  *** ${test}: object file did not match!"
    diff -u -w ${og} ${oh} | head -n 30 | sed 's/^/    /'
fi

# Verify map file, if present
if test -f ${mg} && ! diff -w ${mg} ${m} >/dev/null; then
    status=1
    echo "  *** ${test}: map file did not match!"
    diff -u -w ${mg} reults/${m} | head -n 30 | sed 's/^/    /'
fi

exit ${status}
