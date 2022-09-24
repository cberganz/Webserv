# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
#    Updated: 2022/09/24 17:55:16 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ConfigParser.a

CC			= clang++

INCLUDE		= include/

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -g

SRC_NAME	= Config.cpp		\
			  Parser.cpp		\
			  Lexer.cpp			\
			  Context.cpp		\
			  ContextBase.cpp	\
			  ParserConfig.cpp

TEST_FILES	= simpleTest1.conf \
			  simpleTest2.conf

TEST_DIR		= ParsingTester/confFiles/
TEST_PATHS		= ${addprefix ${TEST_DIR}, ${TEST_FILES}}

SRC_DIR		= srcs/
SRC			= ${addprefix ${SRC_DIR}, ${SRC_NAME}}

OBJ_DIR		= objs/
OBJ_DIRS	= ${sort ${dir ${OBJ}}}
OBJ_NAME	= ${SRC_NAME:.cpp=.o}
OBJ			= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${NAME}

${NAME}: ${OBJ}
	@ar rcs ${NAME} ${OBJ}

${OBJ_DIRS}:
	@mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	@${CC} ${CFLAGS} -c $< -o $@

test: all
	@bash ParsingTester/ParsingTester.sh

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${NAME}
	rm -f a.out

re: fclean all

.PHONY : all clean fclean test re
