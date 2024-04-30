NAME	= gnl.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror 
AR		= ar rcs
RM		= rm -f

NOCOLOR = \033[0;39m
GRAY    = \033[0;90m
RED     = \033[0;91m
GREEN   = \033[0;92m
YELLOW  = \033[0;93m
BLUE    = \033[0;94m
MAGENTA = \033[0;95m
CYAN    = \033[0;96m
WHITE   = \033[0;97m


HDRS	= get_next_line.h get_next_line_bonus.h
SRC		= get_next_line get_next_line_utils
SRCS	= $(addsuffix .c, $(SRC))			
OBJS	= $(addsuffix .o, $(SRC))
BSRC	= get_next_line_bonus get_next_line_utils_bonus
BSRCS	= $(addsuffix .c, $(BSRC))			
BOBJS	= $(addsuffix .o, $(BSRC))

$(NAME):	$(OBJS) 
	@$(AR) $(NAME) $?
	@echo "$(GREEN)Library $(NAME) linked! $(NOCOLOR)"

bonus:		$(BOBJS)
	@$(AR) $(NAME) $?
	@echo "$(GREEN)Library $(NAME) linked with bonus! $(NOCOLOR)"

%.o: %.c $(HDRS) Makefile  
	@echo "$(YELLOW)CC: $< $(NOCOLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_D):
	@$(MKDIR) $(BUILD_D)

clean:
	@$(RM) $(OBJS) $(BOBJS) 
	@echo "$(BLUE)Build files for $(NAME) cleaned! $(NOCOLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Library $(NAME) cleaned! $(NOCOLOR)"

all: $(NAME)

re: fclean all

norm:
	@norminette | grep -v OK || echo "$(GREEN)Norminette: OK $(NOCOLOR)"

.PHONY: bonus norm clean fclean re all
