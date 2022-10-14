
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
#    Updated: 2022/09/30 17:12:15 by cberganz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: test

test:
	@bash ParsingTester/ParsingTester.sh
	@bash ResponseTester/ResponseMakerTester.sh
	@bash ConnexionTester/ConnexionTester.sh
	@rm -f a.out

clean:
	rm -f ParsingTester/outfiles/*.out
	rm -f ResponseTester/outfiles/*.out

fclean: clean
	rm -f a.out

re: fclean all

.PHONY : all clean fclean test re
