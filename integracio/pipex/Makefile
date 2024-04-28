# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 13:07:00 by abluis-m          #+#    #+#              #
#    Updated: 2024/04/25 17:07:42 by abluis-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 							Name of the executable							   #
# **************************************************************************** #

NAME	= pipex

# **************************************************************************** #
# 							Commands and flags  							   #
# **************************************************************************** #

CC		= gcc
DFLAGS	+= -DDEBUG_MODE=1
DFLAGS	+= -fsanitize=address # -g
CFLAGS	= -Wall -Wextra -Werror $(DFLAGS)
RM		= rm -f
RMDIR	= rm -rf
MKDIR	= mkdir -p

# **************************************************************************** #
#						  	Terminal Colors									   #
# **************************************************************************** #

NOCOLOR = \033[0;39m
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

# **************************************************************************** #
# 				  		Sources and build files								   #
# **************************************************************************** #

SRC		=	pipex_bonus \
			util \
			error \
			debug \
			heredoc \
			parse_arg \
			parse_quotes \
			get_next_line \
			get_next_line_utils 

SRCS	= $(addprefix $(SR_D)/, $(addsuffix .c, $(SRC)))
OBJS	= $(addprefix $(BUILD_D)/, $(addsuffix .o, $(SRC)))
HDR		= pipex.h
HDRS	= $(addprefix $(INC_D)/, $(HDR))
FT_LIB	= $(FT_D)/libft.a

# **************************************************************************** #
# 							  		   Rules	   							   #
# **************************************************************************** #

$(NAME):	libft $(OBJS) $(HDRS) Makefile 
	@$(CC) $(CFLAGS) $(OBJS) $(FT_LIB) -o $(NAME)
	@echo "$(GREEN)Binary $(NAME) compiled! $(NOCLOR)"

bonus:	$(NAME)

libft:
	@echo "$(WHITE)Running LIBFT make: $(NOCOLOR)"
	@$(MAKE) --no-print-directory -C $(FT_D)
	
$(BUILD_D)/%.o:	$(SRC_D)/%.c $(HDRS) Makefile | $(BUILD_D) 
	@echo "$(YELLOW)CC: $< $(NOCOLOR)"
	@$(CC) $(CFLAGS) -I $(FT_D) -I $(INC_D) -o $@ -c $<

$(BUILD_D):
	@$(MKDIR) $(BUILD_D)

all:	$(NAME)

clean:
	@echo "$(WHITE)Running LIBFT make clean: $(NOCOLOR)"
	@$(MAKE) --no-print-directory clean -C $(FT_D)
	@$(RMDIR) $(BUILD_D)
	@echo "$(BLUE)Build files for $(NAME) cleaned! $(NOCOLOR)"

fclean:	clean
	@echo "$(WHITE)Running LIBFT make fclean: $(NOCOLOR)"
	@$(MAKE) --no-print-directory fclean -C $(FT_D)
	@$(RM) $(NAME)
	@echo "$(CYAN)Binary files for $(NAME) cleaned! $(NOCOLOR)"

re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt $(NAME)! $(NOCOLOR)"

norm:
	@norminette $(SRC_D) $(INC_D) | grep -v OK \
		|| echo "$(GREEN)Norminette: OK $(NOCOLOR)"

.PHONY:	norm clean fclean re all bonus libft
