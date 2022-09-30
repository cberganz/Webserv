#!/bin/bash

#
#	This script MUST be launch from the parent directory
#	with the command `make test`.
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
	printf "${red}Error:${white} This script must be launch from the makefile in the parent directory using the command \`make ParsingTester\`.${reset}"
	exit 0
fi

echo
errors=0
clang++ ${CFLAGS} ${TESTER_PATH}Tester.cpp -L.. -lWebserv
rm -f ${TESTER_PATH}outfiles/*.out ${TESTER_PATH}outfiles/*.debug
files=`ls ./${TESTER_PATH}confFiles`
files=`echo $files | sed 's/\n/ /g'`
for test in $files
do
	printf "${Cyan}${test}	${Purple}${reset}"
    ./a.out "${TESTER_PATH}confFiles/$test" > ${TESTER_PATH}outfiles/${test}.out 2>&1
	ret_diff=`diff ${TESTER_PATH}outfiles/${test}.out ${TESTER_PATH}outfiles/${test}.model`
	if [ "$ret_diff" != "" ]
	then
		errors = $(($errors+1))
		echo $ret_diff > ${TESTER_PATH}outfiles/${test}.debug
    	printf "❌${red} Check diff at ${TESTER_PATH}outfiles/${test}.debug\n"
    else
    	printf "✅\n"
	fi
done
#rm a.out
if [ $errors == 0 ]; then
	printf "${Purple}Number of errors: ${green}${errors}${reset}\n\n"
	exit 0
else
	printf "${Purple}Number of errors: ${red}${errors}${reset}\n\n"
	exit 1
fi
