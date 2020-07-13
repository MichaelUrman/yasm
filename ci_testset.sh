#! /bin/sh

YASM_TEST_SUITE=1
export YASM_TEST_SUITE

mkdir results >/dev/null 2>&1

# XXX: Temporary hack; needed for libyasm_test/incbin to pass in ctest
echo "timestamp for config.h" > stamp-h1

#
# Verify that all test cases match
#

passedct=0
failedct=0

for asm in ${srcdir}/$2/*.asm
do
    sh ${srcdir}/ci_test.sh "$1" "$asm" "$4" "$5"
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
