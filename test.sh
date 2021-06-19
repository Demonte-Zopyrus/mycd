#! /bin/bash
echo Please input the file name for testing!
read NAME
echo Testing $NAME!
./$NAME / abc > test.results

./$NAME /abc/def ghi >> test.results

./$NAME /abc/def .. >> test.results

./$NAME /abc/def /abc >> test.results

./$NAME /abc/def /abc/klm >> test.results

./$NAME /abc/def ../.. >> test.results

./$NAME /abc/def ../../.. >> test.results

./$NAME /abc/def . >> test.results

./$NAME /abc/def ..klm >> test.results

./$NAME /abc/def ////// >> test.results

./$NAME /abc/def ...... >> test.results

./$NAME /abc/def ../gh///../klm/. >> test.results

if cmp -s "test.results" "correct.results"; then
    printf '\e[32mResults are correct! \n\e[0m'
else
    printf '\n\e[31mResults differ!\n\n\e[34mResults got:\n\e[31m'
    cat test.results
    printf '\e[34m\nCorrect answers:\n\e[32m'
    cat correct.results
    printf '\e[0m\n'
fi