NAME				:=		cub3D

PATH_BUILD			:=		build
PATH_LIBFT			:=		libft
PATH_LIBMLX_MAC		:=		dependencies/minilibx-macos
PATH_LIBMLX_LINUX	:=		dependencies/minilibx-linux
PATH_LIBMLX42		:=		dependencies/MLX42/
SRCS				:=		$(shell find srcs -name *.c)
OBJS				:=		$(SRCS:%.c=$(PATH_BUILD)/%.o)
DEPS				:=		$(OBJS:.o=.d)

CC					:=		gcc

RM 					:=		rm -rf

OS					:=		$(shell uname -s)

FLAG_INC			:= 		$(addprefix -I, includes $(PATH_LIBFT) $(PATH_LIBMLX_LINUX) $(PATH_LIBMLX_MAC) $(PATH_LIBMLX42)include)
FLAGS_COMP			:= 		-O3 -Wall -Wextra -Werror $(FLAG_INC) -MMD -MP -g 

FLAG_LIBFT			:=		-L$(PATH_LIBFT) -lft 
FLAG_LIBMLX_MAC		:=		-L$(PATH_LIBMLX_MAC) -lmlx -framework OpenGL -framework AppKit -lz
FLAG_LIBMLX_LINUX	:=		-L$(PATH_LIBMLX_LINUX) -lmlx -lX11 -lXext
FLAG_LIBMLX42		:= 		-L$(PATH_LIBMLX42)build -lmlx42 -lglfw -ldl

ifeq ($(OS),Linux)
	FLAGS_LINKING := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_LINUX) $(FLAG_LIBMLX42)
	FLAGS_COMP += -D LINUX
else
	FLAGS_LINKING := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_MAC) $(FLAG_LIBMLX42)
	GLFW_PATH_MAC = -L"/Users/$(USER)/.brew/opt/glfw/lib/"
	if [ -d "$(GLFW_PATH_MAC)" ]; then
		FLAGS_LINKING += $(GLFW_PATH_MAC)
	fi
endif

all:						init $(NAME)
							@printf "\033[0;32mGame $(NAME) created. 🎮\033[0m\n"

init:
							@ make -s -C $(PATH_LIBFT)
ifeq ($(OS),Linux)
	@ make -C $(PATH_LIBMLX_LINUX)
	@ cmake -S $(PATH_LIBMLX42) -B $(PATH_LIBMLX42)build && make -C $(PATH_LIBMLX42)build -j4
else
	@ make -C $(PATH_LIBMLX_MAC)
	@ cmake -S $(PATH_LIBMLX42) -B $(PATH_LIBMLX42)build && make -C $(PATH_LIBMLX42)build -j4
endif

$(NAME):					$(OBJS)
							@$(CC) $(OBJS) $(FLAGS_LINKING) -o $@

$(PATH_BUILD)/%.o:	%.c
							@mkdir -p $(dir $@)
							@$(CC) $(FLAGS_COMP) -c $< -o $@
							@printf "\033[0;33mCompiling  $< 🔨\033[0m\n"

bonus:						all

clean:
							@ $(RM) $(PATH_BUILD)
							@ make -s -C $(PATH_LIBFT) clean
							@ make -s -C $(PATH_LIBMLX_MAC) clean
							@ make -s -C $(PATH_LIBMLX_LINUX) clean
							@ make -C $(PATH_LIBMLX42)build clean

fclean:						clean
							@ $(RM) $(NAME)
							@ make -s -C $(PATH_LIBFT) fclean
							@ $(RM) $(PATH_LIBMLX42)build

re:							fclean all

.PHONY:						all clean fclean re

-include $(DEPS)
