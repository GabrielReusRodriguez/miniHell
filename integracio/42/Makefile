# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 13:07:00 by abluis-m          #+#    #+#              #
#    Updated: 2024/04/19 08:34:08 by greus-ro         ###   ########.fr        #
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
DFLAGS	= -g
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

SRC		= 	main				\
			parser				\
			signal_handler		\
			tokens				\
			tokens_creator		\
			tokens_creator2		\
			tokens_debug		\

SRCS	= $(addprefix $(SR_D)/, $(addsuffix .c, $(SRC)))
OBJS	= $(addprefix $(BUILD_D)/, $(addsuffix .o, $(SRC)))
GNL_F	= get_next_line get_next_line_utils
GNL_SRC = $(addprefix $(GNLD)/, $(addsuffix .c, $(GNL_F)))
GNL_OBJ = $(addprefix $(BUILD_D)/, $(addsuffix .c, $(SRC)))
GNL_HDR	= $(GNL_D)/get_next_line.h
HDR		= minishell.h 
HDRS	= $(addprefix $(INC_D)/, $(HDR)) $(GNL_HDR)
FT_LIB	= $(FT_D)/libft.a
GNL_LIB = $(GNL_D)/gnl.a

# **************************************************************************** #
# 							  		   Rules	   							   #
# **************************************************************************** #

$(NAME):	$(OBJS) $(HDRS) Makefile libft gnl
	@$(CC) $(OBJS) $(FT_LIB) $(GNL_LIB) -lreadline -o $(NAME)
	@echo "$(GREEN)Binary $(NAME) compiled! $(RST)"

#bonus:	$(NAME)

libft:
	@$(MAKE) --no-print-directory bonus -C $(FT_D)

gnl: 
	@$(MAKE) --no-print-directory -C $(GNL_D)

$(BUILD_D)/%.o:	$(SRC_D)/%.c $(HDRS) Makefile | $(BUILD_D) 
	@echo "$(YELLOW)CC: $< $(RST)"
#	@$(CC) $(CFLAGS) -I $(FT_D) -I $(GNL_D) -I $(INC_D) -o $@ -c $<
	@$(CC) $(CFLAGS) -I $(FT_D) -I $(INC_D) -o $@ -c $<

$(BUILD_D):
	@$(MKDIR) $(BUILD_D)

all:	$(NAME) 

#brew:
	brew install readline
	brew link --force readline
	cpanm Term::ReadLine::Gnu
	brew unlink readline

clean:
	@$(MAKE) --no-print-directory clean -C $(FT_D)
	@$(MAKE) --no-print-directory clean -C $(GNL_D)
	@$(RMDIR) $(BUILD_D)
	@$(RM) $(GNL_LIB)
	@echo "$(BLUE)Build files for $(NAME) cleaned! $(RST)"

fclean:	clean
	@$(MAKE) --no-print-directory fclean -C $(FT_D)
	@$(MAKE) --no-print-directory fclean -C $(GNL_D)
	@$(RM) $(NAME)
	@echo "$(CYAN)Binary files for $(NAME) cleaned! $(RST)"

re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt $(NAME)! $(RST)"

norm:
	@norminette $(SRC_D) $(INC_D) | grep -v OK \
		|| echo "$(GREEN)Norminette: OK $(RST)"

.PHONY:	norm clean fclean re all libft gnl
