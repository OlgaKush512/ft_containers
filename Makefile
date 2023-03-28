# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okushnir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 17:04:26 by okushnir          #+#    #+#              #
#    Updated: 2022/08/01 17:04:31 by okushnir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	ft_containers

SRCS		=	main.cpp
# SRCS		=	make1.cpp


INCL		=	vector.hpp stack.hpp map.hpp set.hpp type_traits.hpp utility.hpp

OBJS		= 	$(SRCS:.cpp=.o)

NAMESPACE	= -D NS=std

CC			= c++

# CPP_FLAGS	= -Wall -Wextra -Werror -g3 
CPP_FLAGS	= -Wall -Wextra -Werror -std=c++98

OBJS		= ${SRCS:.cpp=.o}

$(NAME):	${OBJS} ${INCL}
			${CC} ${CPP_FLAGS} ${SRCS} -o ft_containers
			${CC} ${CPP_FLAGS} ${SRCS} $(NAMESPACE) -o std_containers
			./ft_containers > ft_file
			./std_containers > std_file

%.o :		%.cpp
			@${CC} ${CPP_FLAGS} -o $@ -c $<

all:		${NAME}

clean:
			rm -rf ${OBJS}

fclean:		clean
			rm -rf ${NAME} ft_containers std_containers ft_file std_file make1.o

re:			fclean all

.PHONY:
			all clean fclean re
