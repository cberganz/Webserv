# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdine <cdine@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
#    Updated: 2022/10/01 19:25:12 by cdine            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libWebserv.a

CC			= clang++

INCLUDE		= include/

CFLAGS		= #-Wall -Wextra -Werror -std=c++98 -g

SRC_NAME	= srcs/config_lexer_parser/Config.cpp		\
			  srcs/config_lexer_parser/Parser.cpp		\
			  srcs/config_lexer_parser/Lexer.cpp			\
			  srcs/config_lexer_parser/Context.cpp		\
			  srcs/config_lexer_parser/ContextBase.cpp	\
			  srcs/config_lexer_parser/ParserConfig.cpp	\
			  srcs/socket_connexion/PollingManager.cpp	\
			  srcs/socket_connexion/ServerConnexion.cpp	\
			  srcs/socket_connexion/ChunkedRequests.cpp	\
			  #unit_test/test.cpp

#SRC_DIR		= srcs/
SRC			= ${SRC_NAME} #${addprefix ${SRC_DIR}, ${SRC_NAME}}

OBJ_DIR		= objs/
OBJ_DIRS	= ${sort ${dir ${OBJ}}}
OBJ_NAME	= ${SRC_NAME:.cpp=.o}
OBJ			= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${NAME}

${NAME}: ${OBJ}
	#$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@ar rcs ${NAME} ${OBJ}

${OBJ_DIRS}:
	@mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	${CC} ${CFLAGS} -c $< -o $@

test: all
	@make -sC ./unit_test
	@make fclean -sC ./unit_test

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${NAME}
	rm a.out

re: fclean all

server_connexion: all
	c++ unit_test/ConnexionTester/mains/basic.cpp -L. -lWebserv
	./a.out unit_test/ParsingTester/confFiles/basicTest.conf 	

.PHONY : all clean fclean test re server_connexion