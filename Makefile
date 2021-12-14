# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 09:21:36 by joopark           #+#    #+#              #
#    Updated: 2021/12/13 22:55:43 by joopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_42TESTER = 42tester
NAME_TESTER = tester
CODE_42TESTER = ./main.cpp
CODE_TESTER = ./mytest.cpp ./vector_module_tester.cpp ./map_module_tester.cpp ./stack_module_tester.cpp
OBJS_NAME_42TESTER = ${CODE_42TESTER:%.cpp=%.o}
OBJS_NAME_TESTER = ${CODE_TESTER:%.cpp=%.o}
COMPILER = clang++
CFLAGS = -Wall -Wextra -Werror
HEADER_CONTAINER = ./ft
HEADER_UTILS = ./ftutils
HEADER_REIMPLEMENT = ./reimplement

all: $(NAME_42TESTER) $(NAME_TESTER)

clean:
	rm -f $(OBJS_NAME_42TESTER) $(OBJS_NAME_TESTER)

fclean: clean
	rm -f $(NAME_42TESTER) $(NAME_TESTER)

%.o: %.cpp
	$(COMPILER) ${CFLAGS} -I${HEADER_CONTAINER} -I${HEADER_UTILS} -I${HEADER_REIMPLEMENT} -c -o $@ $<

$(NAME_42TESTER): $(OBJS_NAME_42TESTER)
	$(COMPILER) $(CFLAGS) $(OBJS_NAME_42TESTER) -I$(HEADER_CONTAINER) -I$(HEADER_UTILS) -I$(HEADER_REIMPLEMENT) -o $(NAME_42TESTER)

$(NAME_TESTER): $(OBJS_NAME_TESTER)
	$(COMPILER) $(CFLAGS) $(OBJS_NAME_TESTER) -I$(HEADER_CONTAINER) -I$(HEADER_UTILS) -I$(HEADER_REIMPLEMENT) -o $(NAME_TESTER)

re: fclean all