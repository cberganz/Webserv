# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdine <cdine@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/10/24 14:10:56 by rbicanic         ###   ########.fr        #
=======
#    Updated: 2022/10/24 15:17:04 by cdine            ###   ########.fr        #
>>>>>>> fix_server_connexion
#                                                                              #
# **************************************************************************** #

NAME		= webserv

LIB_NAME	= libWebserv.a

CC			= clang++

INCLUDE		= include/

FLAGS		= -Wall -Wextra -Werror -std=c++98 -g #-fPIC

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


SRC			= ${SRC_NAME}

OBJ_DIR		= objs/
OBJ_DIRS	= ${sort ${dir ${OBJ}}}
OBJ_NAME	= ${SRC_NAME:.cpp=.o}
OBJ			= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${NAME}

${NAME}: lib exec

lib: ${OBJ}
	@ar rcs ${LIB_NAME} ${OBJ}

exec:
	clang++ ${FLAGS} srcs/webserv.cpp -o ${NAME} -L. -lWebserv

${OBJ_DIRS}:
	@mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	${CC} ${FLAGS} -c $< -o $@

server_connexion: all
	# ./webserv
	# ./webserv ./config_files/delete_method.conf
	./webserv ./config_files/demo.conf
	# ./webserv ./config_files/form.conf
	# ./webserv ./config_files/upload_file.conf
	#
test: all
	@make -sC ./unit_test

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${LIB_NAME}
	rm -f ${NAME}
	@make fclean -sC ./unit_test

re: fclean all

.PHONY : all clean fclean test re server_connexion
