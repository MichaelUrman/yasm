#! /bin/sh

YASM_TEST_SUITE=1
export YASM_TEST_SUITE

# arguments: yasm-path test_hd-path test-name test-dir test-description yasm-args out-suffix
SRCDIR=${srcdir:-`dirname $0`}
YASM="$1"
TEST_HD="$2"
TESTSET="$3"
TESTDIR="$4"
TESTDESC="$5"
YASM_ARGS="$6"
YASM_OUT_SUFFIX="$7"
export SRCDIR
export YASM
export YASM_ARGS
export YASM_OUT_SUFFIX
export TEST_HD

mkdir results >/dev/null 2>&1

# XXX: Temporary hack; needed for libyasm_test/incbin to pass in ctest
echo "timestamp for config.h" > stamp-h1

#
# Verify that all test cases match
#

passedct=0
failedct=0

for asm in ${SRCDIR}/${TESTDIR}/*.asm
do
    sh ${SRCDIR}/ci_test.sh "${TESTSET}" "$asm"
    if test $? -gt 0; then
        failedct=`expr $failedct + 1`
    else
        passedct=`expr $passedct + 1`
    fi
done

ct=`expr $failedct + $passedct`
per=`expr 100 \* $passedct / $ct`

echo " +$passedct-$failedct/$ct $per%"

exit $failedct
