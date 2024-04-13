NAME=minishell

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

LIBFT_DIR = ./libft
LIBFT_INC = ${LIBFT_DIR}/inc
LIBFT_BIN = ${LIBFT_DIR}/bin

LIBFT_PRINTF = ${LIBFT_BIN}/ft_printf/ft_printf.a
LIBFT_FT	= ${LIBFT_BIN}/ft/ft_utils.a

SRC_FILES =	minishell.c			\
			ft_environment.c	\
			ft_error.c			\
			ft_parser.c			\
			ft_path.c			\
			ft_ptr.c			\
			ft_tokens.c


#SOURCE = $(addprefix ${SRC_DIR}, ${SRC_FILES})

OBJ_FILES=$(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
DEP_FILES=$(SRC_FILES:%.c=$(OBJ_DIR)/%.d)

#CDEBUG = -g3 -fsanitize=address
CDEBUG = -g3 
CFLAGS = -Werror -Wall  -Wextra -MMD -MP ${CDEBUG} 
LINK_FLAGS = -lreadline

all: ${NAME}

${NAME}: ${OBJ_DIR} ${OBJ_FILES} ${LIBFT_FT} ${LIBFT_PRINTF}
	cc ${LINK_FLAGS} ${OBJ_FILES} -o ${NAME} ${LIBFT_FT} ${LIBFT_PRINTF}

${OBJ_DIR}/%.o : ${SRC_DIR}/%.c Makefile
	cc ${CFLAGS} -I${INC_DIR} -I${LIBFT_INC} -c $< -o $@

${OBJ_DIR} :
	mkdir -p ${OBJ_DIR}

${LIBFT_FT}:
	make -C ${LIBFT_DIR}

${LIBFT_PRINTF}:
	make -C ${LIBFT_FT}

-include ${OBJ_DEPS}

norminette:
	norminette ${SRC_DIR} ${INC_DIR}

clean:
	rm -f ${OBJ_DIR}/*.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fcklean re norminette