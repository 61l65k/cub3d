CC := gcc
INCLUDE_DIRS := includes libft
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := cub3d
LIBFT := libft/libft.a
SRCS := main.c utils/utils.c
SRCS_MANDATORY := $(addprefix srcs/, $(SRCS))
OBJS_MANDATORY := $(SRCS_MANDATORY:.c=.o)

# Check for OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    FLAGS := -Wall -Wextra -Werror -g -L./minilibx-linux -lmlx -lX11 -lXext -lm
	MINILIBX = minilibx-linux
	INCLUDES += -I./minilibx-linux
else ifeq ($(UNAME_S),Darwin)
    FLAGS := -Wall -Wextra -Werror -g -L./minilibx-macos -lmlx -framework OpenGL -framework AppKit -lm
	MINILIBX = minilibx-macos
	INCLUDES += -I./minilibx-macos
else
    $(error "Unsupported operating system ($(UNAME_S))")
	exit 1
endif

all: libft minilibx $(NAME) 

libft:
	@make -s -C libft/

minilibx:
	@make -s -C $(MINILIBX)

%.o : %.c
	@$(CC) -c $^ -o $@ $(INCLUDES)
	@printf "\033[0;33mCompiling $< 🔨\033[0m\n"

$(NAME) : $(OBJS_MANDATORY) 
	$(CC) $(FLAGS) $^ -o $@ $(INCLUDES) $(LIBFT)

clean:
	@rm -f $(OBJS_MANDATORY)
	@$(MAKE) -s -C libft/ clean
	@$(MAKE) -s -C $(MINILIBX) clean
	@printf "\033[0;31mCleaning up $(OBJS_MANDATORY) 🗑️\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C libft/ fclean

re: fclean all

.PHONY: libft minilibx all clean fclean re
