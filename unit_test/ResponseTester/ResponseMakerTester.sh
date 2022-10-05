#!/bin/bash

#
#	This script MUST be launch from the root directory
#	of the repository with the command `make test`.
#

CFLAGS="-Wall -Wextra -Werror -std=c++98 -g"

TESTER_PATH="ResponseTester/"

Blue='\033[0;34m'
Purple='\033[0;35m'
Cyan='\033[0;36m'
BYellow='\033[1;33m'
white='\033[1;37m'
green='\033[0;32m'
red='\033[0;31m'
yell='\033[0;33m'
reset='\033[0m'

if [ "${PWD##*/}" == "ResponseTester" ]; then
	printf "${red}Error:${white} This script must be launch from the makefile in the root directory using the command \`make test\`.${reset}"
	exit 0
fi

echo
printf "${yell}---------------------------${reset}\n"
printf "${yell}|     Response Tester     |${reset}\n"
printf "${yell}---------------------------${reset}\n"

errors=0
clang++ ${CFLAGS} ${TESTER_PATH}ResponseMakerTester.cpp -L.. -lWebserv
chmod -r ${TESTER_PATH}scripts/indexNoRead.html
rm -f ${TESTER_PATH}outfiles/*.out
files=`ls ./${TESTER_PATH}conf`
files=`echo $files | sed 's/\n/ /g'`
for file in $files
do
	./a.out "${TESTER_PATH}conf/$file" > ${TESTER_PATH}outfiles/${file}.out 2>&1
	# UNCOMMENT TO GENERATE MODELS
	#./a.out "${TESTER_PATH}conf/$file" > ${TESTER_PATH}outfiles/${file}.model 2>&1
	ret_diff=`diff -u -I 'date.*' ${TESTER_PATH}outfiles/${file}.out ${TESTER_PATH}outfiles/${file}.model`
	if [ "$ret_diff" != "" ]; then
		errors=$(($errors+1))
		printf "❌ ${Cyan}${file}	${reset}\n"
		printf "${red} Check ${file}.model and ${file}.out at ${TESTER_PATH}outfiles${reset}\n"
		printf "${red}diff return:\n$ret_diff${reset}\n"
	else
		printf "✅ ${Cyan}${file}	${reset}\n"
	fi
done
chmod +r ${TESTER_PATH}scripts/indexNoRead.html
if [ $errors == 0 ]; then
	printf "${Purple}Number of errors: ${green}${errors}${reset}\n\n"
	exit 0
else
	printf "${Purple}Number of errors: ${red}${errors}${reset}\n\n"
	exit 1
fi
