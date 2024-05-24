NAME	= libft.a

CC		= gcc
DFLAGS	= -fsanitize=address -g
CFLAGS	= -Wall -Wextra -Werror #$(DFLAGS)
AR		= ar rcs
RM		= rm -f
RMDIR	= rm -rf
MKDIR	= mkdir -p

NOCOLOR = \033[0;39m
GRAY    = \033[0;90m
RED     = \033[0;91m
GREEN   = \033[0;92m
YELLOW  = \033[0;93m
BLUE    = \033[0;94m
MAGENTA = \033[0;95m
CYAN    = \033[0;96m
WHITE   = \033[0;97m

SRC_D   = src
BUILD_D = build
INCLUDE = .

HDRS	= libft.h
SRC		= ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen \
		  ft_memset ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_strlcat \
		  ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp ft_memchr \
		  ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strdup ft_substr \
		  ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
		  ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd
SRCS	= $(addprefix $(SRC_D)/, $(addsuffix .c, $(SRC)))			
OBJS	= $(addprefix $(BUILD_D)/, $(addsuffix .o, $(SRC)))
BSRC	= ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus \
		  ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
		  ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus
BSRCS	= $(addprefix $(SRC_D)/, $(addsuffix .c, $(BSRC)))			
BOBJS	= $(addprefix $(BUILD_D)/, $(addsuffix .o, $(BSRC)))

$(NAME):	$(OBJS) 
	@$(AR) $(NAME) $?
	@echo "$(GREEN)Library $(NAME) linked! $(NOCOLOR)"

bonus:		$(OBJS) $(BOBJS)
	@$(AR) $(NAME) $?
	@echo "$(GREEN)Library $(NAME) linked with bonus! $(NOCOLOR)"

$(BUILD_D)/%.o: $(SRC_D)/%.c $(HDRS) Makefile | $(BUILD_D) 
	@echo "$(YELLOW)CC: $< $(NOCOLOR)"
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(BUILD_D):
	@$(MKDIR) $(BUILD_D)

clean:
	@$(RMDIR) $(BUILD_D) 
	@echo "$(BLUE)Build files for $(NAME) cleaned! $(NOCOLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Library $(NAME) cleaned! $(NOCOLOR)"

all: $(NAME)

re: fclean all

norm:
	@norminette | grep -v OK || echo "$(GREEN)Norminette: OK $(NOCOLOR)"

.PHONY: bonus norm clean fclean re all
