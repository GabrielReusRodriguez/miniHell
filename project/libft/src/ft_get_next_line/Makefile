# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/13 02:39:39 by greus-ro          #+#    #+#              #
#    Updated: 2024/02/06 19:46:20 by greus-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


INC_DIR=../../inc
BIN_DIR=../../bin/ft_get_next_line
SRC_DIR=./src

NAME		= ${BIN_DIR}/ft_get_next_line.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -MMD -MP
DFLAGS		= -D BUFFER_SIZE=30

SRC_FILES	= 	ft_get_next_line.c 				\
				ft_get_next_line_bonus.c 		\

OBJ_FILES	= $(SRC_FILES:%.c=${BIN_DIR}/%.o)
DEP_FILES	= $(SRC_FILES:%.c=${BIN_DIR}/%.d)

#SRC = $(addprefix ${SRC_DIR}, ${SRC_FILES})

all: ${NAME}
	
${NAME}: ${OBJ_FILES} ${BIN_DIR} 
	ar -rcs ${NAME} ${OBJ_FILES}
	cp ${SRC_DIR}/ft_get_next_line.h ${INC_DIR}/
	
${BIN_DIR}:
	mkdir -p ${BIN_DIR}
	
${BIN_DIR}/%.o:${SRC_DIR}/%.c Makefile
	${CC} ${CFLAGS} ${DFLAGS} -I ${INC_DIR} -o $@ -c $<

clean:
	rm -f ${BIN_DIR}/*.o
	rm -f ${BIN_DIR}/*.d

fclean: clean 
	rm -f ${BIN_DIR}/*.a

re: fclean all

-include ${DEP_FILES}

.PHONY: all clean fclean re
