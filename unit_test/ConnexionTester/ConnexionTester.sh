#!/bin/bash

#
#	This script MUST be launch from the root directory
#	of the repository with the command `make test`.
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
	printf "${red}Error:${white} This script must be launch from the makefile in the root directory using the command \`make test\`.${reset}"
	exit 0
fi

echo
printf "${yell}---------------------------${reset}\n"
printf "${yell}|    Connexion Tester     |${reset}\n"
printf "${yell}---------------------------${reset}\n"

errors=0
rm -f ${TESTER_PATH}outs/*.out ${TESTER_PATH}outs/*.debug
files=`ls ./${TESTER_PATH}mains`
files=`echo $files | sed 's/\n/ /g'`
for test in $files
do
    clang++ ${CFLAGS} ${TESTER_PATH}mains/$test -L.. -lWebserv
    ./a.out ../config_files/default.conf > /dev/null 2>&1 &
    WEBSERV_PID=$!
	sleep 1;
    ret_curl=`curl http://localhost:8080 2>&1`
    if (( $? != 0 )); then
		errors=$(($errors+1))
    	printf "❌ ${Cyan}${test}	${reset}\n"
		printf "${yell}curl return:\n${red}%s${reset}\n" "$ret_curl"
    else
    	printf "✅ ${Cyan}${test}	${reset}\n"
	fi
    kill $WEBSERV_PID
done
if [ $errors == 0 ]; then
	printf "${Purple}Number of errors: ${green}${errors}${reset}\n\n"
	exit 0
else
	printf "${Purple}Number of errors: ${red}${errors}${reset}\n\n"
	exit 1
fi
