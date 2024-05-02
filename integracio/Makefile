# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 13:07:00 by abluis-m          #+#    #+#              #
#    Updated: 2024/05/02 21:19:43 by gabriel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 							Name of the executable							   #
# **************************************************************************** #

NAME	= minishell

# **************************************************************************** #
# 							Commands and flags  							   #
# **************************************************************************** #

CC		= gcc
DFLAGS	+= -g
DFLAGS	+= -fsanitize=address
DFLAGS	+= -DDEBUG_MODE=1
CFLAGS	= -Wall -Wextra -Werror $(DFLAGS) 
RM		= rm -f
RMDIR	= rm -rf
MKDIR	= mkdir -p

# **************************************************************************** #
#						  	Terminal Colors									   #
# **************************************************************************** #

RST		= \033[0;39m
GRAY    = \033[0;90m
RED     = \033[0;91m
GREEN   = \033[0;92m
YELLOW  = \033[0;93m
BLUE    = \033[0;94m
MAGENTA = \033[0;95m
CYAN    = \033[0;96m
WHITE   = \033[0;97m

# **************************************************************************** #
# 							  File paths									   #
# **************************************************************************** #

SRC_D	= src
BUILD_D	= build
INC_D	= include
FT_D	= libft
GNL_D	= gnl

# **************************************************************************** #
# 				  		Sources and build files								   #
# **************************************************************************** #

SRC		= 	main 					\
		  	builtin_exit			\
			cmd						\
			cmd_validator			\
		  	environment 			\
			error_handler			\
			list_utils				\
		  	minishell 				\
		  	minishell_cfg 			\
		  	minishell_stat 			\
			parser					\
			parser_getters_cmd		\
			parser_getters_redirect	\
			parser_utils			\
		  	ptr 					\
		  	signal_handler 			\
		  	tokenizer				\
			tokenizer_parenthesis	\
			tokenizer_quotes		\
			tokenizer_redirect		\
			tokenizer_separators	\
			tokenizer_utils			\
			tokenizer_words			\
			tokens_utils			\
			tokenset_utils			\
			var						\
			tokenizer_debug			\
			cmd_debug				\
			environment_debug		\

SRCS	= $(addprefix $(SR_D)/, $(addsuffix .c, $(SRC)))
OBJS	= $(addprefix $(BUILD_D)/, $(addsuffix .o, $(SRC)))
HDR		= 	minishell.h			\
			builtin.h			\
			cmd.h				\
			datatypes.h			\
			debug.h				\
			environment.h		\
			error_handler.h		\
			parser.h			\
			ptr.h				\
			signal_handler.h	\
			tokens.h			\
			var.h
HDRS	= $(addprefix $(INC_D)/, $(HDR)) 
FT_LIB	= $(FT_D)/libft.a
GNL_LIB = $(GNL_D)/gnl.a

# **************************************************************************** #
# 							  		   Rules	   							   #
# **************************************************************************** #

$(NAME):	libft gnl $(OBJS) $(HDRS) Makefile 
	@echo "$(WHITE)Compiling $(NAME) executable: $(RST)"
	@$(CC) $(CFLAGS) $(OBJS) $(FT_LIB) $(GNL_LIB) -lreadline -o $(NAME)
	@echo "$(GREEN)Binary $(NAME) compiled! $(RST)"

#bonus:	$(NAME)

libft:
	@echo "$(WHITE)Running LIBFT make bonus: $(RST)"
	@$(MAKE) --no-print-directory bonus -C $(FT_D)

gnl: 
	@echo "$(WHITE)Running GNL make: $(RST)"
	@$(MAKE) --no-print-directory -C $(GNL_D)

$(BUILD_D)/%.o:	$(SRC_D)/%.c $(HDRS) Makefile | $(BUILD_D) 
	@echo "$(YELLOW)CC: $< $(RST)"
	@$(CC) $(CFLAGS) -I $(FT_D) -I $(GNL_D) -I $(INC_D) -o $@ -c $<

$(BUILD_D):
	@$(MKDIR) $(BUILD_D)

#brew:
#	brew install readline
#	brew link --force readline
#	cpanm Term::ReadLine::Gnu
#	brew unlink readline

clean:
	@echo "$(WHITE)Running LIBFT make clean: $(RST)"
	@$(MAKE) --no-print-directory clean -C $(FT_D)
	@echo "$(WHITE)Running GNL make clean: $(RST)"
	@$(MAKE) --no-print-directory clean -C $(GNL_D)
	@echo "$(WHITE)Running $(NAME) clean: $(RST)"
	@$(RMDIR) $(BUILD_D)
	@$(RM) $(GNL_LIB)
	@echo "$(BLUE)Build files for $(NAME) cleaned! $(RST)"

fclean:	clean
	@echo "$(WHITE)Running LIBFT make fclean: $(RST)"
	@$(MAKE) --no-print-directory fclean -C $(FT_D)
	@echo "$(WHITE)Running GNL make fclean: $(RST)"
	@$(MAKE) --no-print-directory fclean -C $(GNL_D)
	@echo "$(WHITE)Running $(NAME) fclean: $(RST)"
	@$(RM) $(NAME)
	@echo "$(CYAN)Binary files for $(NAME) cleaned! $(RST)"

re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt $(NAME)! $(RST)"

all:	$(NAME) 

norm:
	@norminette $(SRC_D) $(INC_D) | grep -v OK \
		|| echo "$(GREEN)Norminette: OK $(RST)"

.PHONY:	norm clean fclean re all bonus libft gnl
