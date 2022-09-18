# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
#    Updated: 2022/09/18 21:16:25 by cberganz         ###   ########.fr        #
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
	@${CC} ${CFLAGS} -Isrcs unit-tests/main.cpp ${NAME}
	@./a.out
	@rm a.out

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY : all clean fclean re
