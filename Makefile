# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdine <cdine@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
#    Updated: 2022/10/15 19:31:25 by cdine            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libWebserv.a

CC			= clang++

INCLUDE		= include/

CFLAGS		= -fPIC -g #-Wall -Wextra -Werror -std=c++98 -g

SRC_NAME	= srcs/config_lexer_parser/Config.cpp			\
			  srcs/config_lexer_parser/Parser.cpp			\
			  srcs/config_lexer_parser/Lexer.cpp			\
			  srcs/config_lexer_parser/Context.cpp			\
			  srcs/config_lexer_parser/ContextBase.cpp		\
			  srcs/config_lexer_parser/ParserConfig.cpp		\
			  srcs/socket_connexion/PollingManager.cpp		\
			  srcs/socket_connexion/ServerConnexion.cpp		\
			  srcs/socket_connexion/Chunks.cpp				\
			  srcs/client_request/ClientRequest.cpp			\
			  srcs/client_request/ClientRequestParser.cpp	\
			  srcs/response/BodyMaker.cpp					\
			  srcs/response/HeaderMaker.cpp					\
			  srcs/response/HttpCodes.cpp					\
			  srcs/response/Response.cpp					\
			  srcs/response/ResponseMaker.cpp				\
			  srcs/response/ResponseHandler.cpp				\
			  srcs/tools/utility.cpp


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

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${NAME}
	@make fclean -sC ./unit_test

re: fclean all

server_connexion: all
	c++ unit_test/ConnexionTester/mains/basic.cpp -L. -lWebserv
	./a.out ./config_files/form.conf

.PHONY : all clean fclean test re server_connexion
