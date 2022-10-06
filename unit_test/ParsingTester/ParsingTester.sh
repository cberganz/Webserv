#!/bin/bash

#
#	This script MUST be launch from the root directory
#	of the repository with the command `make test`.
#

CFLAGS="-Wall -Wextra -Werror -std=c++98 -g"

TESTER_PATH="ParsingTester/"

Blue='\033[0;34m'
Purple='\033[0;35m'
Cyan='\033[0;36m'
BYellow='\033[1;33m'
white='\033[1;37m'
green='\033[0;32m'
red='\033[0;31m'
yell='\033[0;33m'
reset='\033[0m'

if [ "${PWD##*/}" == "ParsingTester" ]; then
	printf "${red}Error:${white} This script must be launch from the makefile in the root directory using the command \`make test\`.${reset}"
	exit 0
fi

echo
printf "${yell}---------------------------${reset}\n"
printf "${yell}|      Parsing Tester     |${reset}\n"
printf "${yell}---------------------------${reset}\n"

errors=0
clang++ ${CFLAGS} ${TESTER_PATH}Tester.cpp -L.. -lWebserv
rm -f ${TESTER_PATH}outfiles/*.out
# see find and fd instead of ls
files=`ls ./${TESTER_PATH}confFiles`
files=`echo $files | sed 's/\n/ /g'`
for test in $files
do
    ./a.out "${TESTER_PATH}confFiles/$test" > ${TESTER_PATH}outfiles/${test}.out 2>&1
	# Uncomment to recreate models. Check diff before to verify nothing is broken.
    #./a.out "${TESTER_PATH}confFiles/$test" > ${TESTER_PATH}outfiles/${test}.model 2>&1
	ret_diff=`diff ${TESTER_PATH}outfiles/${test}.out ${TESTER_PATH}outfiles/${test}.model`
	if [ "$ret_diff" != "" ]; then
		errors=$(($errors+1))
    	printf "❌ ${Cyan}${test}	${reset}\n"
    	printf "${red} Check ${test}.model and ${test}.out at ${TESTER_PATH}outfiles${reset}\n"
		printf "${red}diff return:\n$ret_diff${reset}\n"
    else
    	printf "✅ ${Cyan}${test}	${reset}\n"
	fi
done
if [ $errors == 0 ]; then
	printf "${Purple}Number of errors: ${green}${errors}${reset}\n\n"
	exit 0
else
	printf "${Purple}Number of errors: ${red}${errors}${reset}\n\n"
	exit 1
fi
