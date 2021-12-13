# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 09:21:36 by joopark           #+#    #+#              #
#    Updated: 2021/12/13 13:05:20 by joopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_42TESTER = 42tester
NAME_TESTER = tester
FILES_NAME_42TESTER = ./main.cpp
OBJS_NAME_42TESTER = ${FILES_NAME_42TESTER:%.cpp=%.o}
COMPILER = clang++
CFLAGS = -Wall -Wextra -Werror
HEADER_CONTAINER = ./ft
HEADER_UTILS = ./ftutils
HEADER_REIMPLEMENT = ./reimplement

all: $(NAME_42TESTER)

clean:
	rm -f $(OBJS_NAME_42TESTER)

fclean: clean
	rm -f $(NAME_42TESTER)

%.o: %.cpp
	$(COMPILER) ${CFLAGS} -I${HEADER_CONTAINER} -I${HEADER_UTILS} -I${HEADER_REIMPLEMENT} -c -o $@ $<

$(NAME_42TESTER): $(OBJS_NAME_42TESTER)
	$(COMPILER) $(CFLAGS) $(OBJS_NAME_42TESTER) -I$(HEADER_CONTAINER) -I$(HEADER_UTILS) -I$(HEADER_REIMPLEMENT) -o $(NAME_42TESTER)

re: fclean all