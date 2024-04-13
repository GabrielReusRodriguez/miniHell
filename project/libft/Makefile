# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 01:34:53 by greus-ro          #+#    #+#              #
#    Updated: 2024/02/15 21:36:10 by greus-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CFLAGS=-Wall -Wextra -Werror -MMD -MP

BIN_DIR=./bin
SRC_DIR=./src
INC_DIR=./inc
FT_BIN_DIR=./bin/ft
GET_NEXT_BIN_DIR=./bin/ft_get_next_line
PRINTF_BIN_DIR=./bin/ft_printf

FT_DIR 			= ${SRC_DIR}/ft 
GET_NEXT_DIR 	= ${SRC_DIR}/ft_get_next_line
FT_PRINTF_DIR 	= ${SRC_DIR}/ft_printf 

FT_HDR 			= ${INC_DIR}/libft.h
GET_NEXT_HDR 	= ${INC_DIR}/ft_get_next_line.h
FT_PRINTF_HDR 	= ${INC_DIR}/ft_printf.h

all:${NAME}

${NAME}: ${BIN_DIR} ${FT_BIN_DIR} ${GET_NEXT_BIN_DIR} ${PRINTF_BIN_DIR} ${BIN_DIR}/ft/ft_utils.a ${BIN_DIR}/ft_get_next_line/ft_get_next_line.a ${BIN_DIR}/ft_printf/ft_printf.a  Makefile	
#ar -rcsT ${NAME} ${BIN_DIR}/ft/ft_utils.a  ${BIN_DIR}/ft_get_next_line/ft_get_next_line.a ${BIN_DIR}/ft_printf/ft_printf.a	
#	ar -rcs ${NAME} ${BIN_DIR}/ft/ft_utils.a  ${BIN_DIR}/ft_get_next_line/ft_get_next_line.a ${BIN_DIR}/ft_printf/ft_printf.a	
	ar -rcs ${NAME} ${BIN_DIR}/ft/*.o  ${BIN_DIR}/ft_get_next_line/*.o ${BIN_DIR}/ft_printf/*.o	
#	cp ${NAME} ${BIN_DIR}/libft.a
	
${BIN_DIR}/ft/ft_utils.a:
	make all -C ${FT_DIR}

${BIN_DIR}/ft_get_next_line/ft_get_next_line.a: ${BIN_DIR}/ft/ft_utils.a
	make all -C ${GET_NEXT_DIR}

${BIN_DIR}/ft_printf/ft_printf.a: ${BIN_DIR}/ft/ft_utils.a
	make all -C ${FT_PRINTF_DIR}
	
${BIN_DIR}:
	mkdir -p ${BIN_DIR}

${FT_BIN_DIR}:
	mkdir -p ${FT_BIN_DIR}
	
${GET_NEXT_BIN_DIR}:
	mkdir -p ${GET_NEXT_BIN_DIR}

${PRINTF_BIN_DIR}:
	mkdir -p ${PRINTF_BIN_DIR}
#clean:
#	make clean -C  ${FT_DIR}
#	make clean -C  ${GET_NEXT_DIR}
#	make clean -C  ${FT_PRINTF_DIR}

fclean: 
	make fclean -C  ${FT_DIR}
	make fclean -C  ${GET_NEXT_DIR}
	make fclean -C  ${FT_PRINTF_DIR}
	rm -f ${BIN_DIR}/${NAME}
	rm -f ${NAME}
	
re: fclean all

#bonus:${BONUS_OBJ_FILES} ${LIBFT_OBJ_FILES}
#	ar -rcs ${NAME} ${LIBFT_OBJ_FILES} ${BONUS_OBJ_FILES}
#	@touch bonus

#-include ${LIBFT_DEP_FILES}
#-include ${BONUS_DEP_FILES}

.PHONY= all clean fclean re