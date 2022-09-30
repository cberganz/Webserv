#!/bin/bash

#
#	This script MUST be launch from the parent directory
#	with the command `make test`.
#

CFLAGS="-Wall -Wextra -Werror -std=c++98 -g"

TESTER_PATH="ConnexionTester/"

Blue='\033[0;34m'
Purple='\033[0;35m'
Cyan='\033[0;36m'
BYellow='\033[1;33m'
white='\033[1;37m'
green='\033[0;32m'
red='\033[0;31m'
yell='\033[0;33m'
reset='\033[0m'

if [ "${PWD##*/}" == "ConnexionTester" ]; then
	printf "${red}Error:${white} This script must be launch from the makefile in the parent directory using the command \`make ParsingTester\`.${reset}"
	exit 0
fi

echo
errors=0
rm -f ${TESTER_PATH}outs/*.out ${TESTER_PATH}outs/*.debug
files=`ls ./${TESTER_PATH}mains`
files=`echo $files | sed 's/\n/ /g'`
for test in $files
do
    clang++ ${CFLAGS} ${TESTER_PATH}mains/$test -L.. -lWebserv
    # ulimit -n 5
    ./a.out ../srcs/config_lexer_parser/default.conf > ${TESTER_PATH}outs/${test}.out 2>&1 &
    WEBSERV_PID=$!
    curl "http://localhost:8080" > /dev/null 2> /dev/null
	printf "${Cyan}${test}	${Purple}${reset}"
    if (( $? != 0))
	then
		errors = $(($errors+1))
		echo $ret_diff > ${TESTER_PATH}outs/${test}.debug
    	printf "❌${red} Check diff at ${TESTER_PATH}outs/${test}.debug\n"
    else
    	printf "✅\n"
	fi

	# ret_diff=`diff ${TESTER_PATH}outfiles/${test}.out ${TESTER_PATH}outfiles/${test}.model`
	# if [ "$ret_diff" != "" ]
	# then
	# 	errors = $(($errors+1))
	# 	echo $ret_diff > ${TESTER_PATH}outfiles/${test}.debug
    # 	printf "❌${red} Check diff at ${TESTER_PATH}outfiles/${test}.debug\n"
    # else
    # 	printf "✅\n"
	# fi
    kill $WEBSERV_PID
done
#rm a.out
if [ $errors == 0 ]; then
	printf "${Purple}Number of errors: ${green}${errors}${reset}\n\n"
	exit 0
else
	printf "${Purple}Number of errors: ${red}${errors}${reset}\n\n"
	exit 1
fi
