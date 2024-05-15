NAME				:=		cub3D

PATH_BUILD			:=		build
PATH_LIBFT			:=		libft
PATH_LIBMLX_MAC		:=		minilibx-macos
PATH_LIBMLX_LINUX	:=		minilibx-linux

SRCS				:=		$(shell find srcs -name *.c)
SRCS_OBJS			:=		$(shell find srcs -name *.o)
OBJS				:=		$(SRCS:%.c=$(PATH_BUILD)/%.o)
DEPS				:=		$(OBJS:.o=.d)

CC					:=		gcc

RM 					:=		rm -rf

OS					:=		$(shell uname -s)

FLAG_INC			:= 		$(addprefix -I, includes libft minilibx-linux minilibx-macos)
FLAGS_COMP			:= 		-O3 -Wall -Wextra -Werror $(FLAG_INC) -MMD -MP -g

FLAG_LIBFT			:=		-L$(PATH_LIBFT) -lft 
FLAG_LIBMLX_MAC		:=		-L$(PATH_LIBMLX_MAC) -lmlx -framework OpenGL -framework AppKit -lz
FLAG_LIBMLX_LINUX	:=		-L$(PATH_LIBMLX_LINUX) -lmlx -lX11 -lXext
ifeq ($(OS),Darwin)
	FLAGS_LINKINKG := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_MAC)
else
	FLAGS_LINKINKG := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_LINUX)
endif

all:						init $(NAME)
							@printf "\033[0;32mGame $(NAME) created. 🎮\033[0m\n"

init:
							@ make -s -C $(PATH_LIBFT)
ifeq ($(OS),Linux)
	@ make -s -C $(PATH_LIBMLX_LINUX)
endif

$(NAME):					$(OBJS)
							@$(CC) $(FLAGS_COMP) -o $@ $(OBJS) $(FLAGS_LINKINKG)


$(PATH_BUILD)/%.o:	%.c
							@mkdir -p $(dir $@)
							@$(CC) $(FLAGS_COMP) -c $< -o $@
							@printf "\033[0;33mCompiling  $< 🔨\033[0m\n"

bonus:						all

clean:
							@ $(RM) $(PATH_BUILD)
							@ $(RM) $(SRCS_OBJS)
							@ make -s -C $(PATH_LIBFT) clean
							@ make -s -C $(PATH_LIBMLX_MAC) clean
							@ make -s -C $(PATH_LIBMLX_LINUX) clean

fclean:						clean
							@ $(RM) $(NAME)
							@ make -s -C $(PATH_LIBFT) fclean

re:							fclean all

.PHONY:						all clean fclean re

-include $(DEPS)
