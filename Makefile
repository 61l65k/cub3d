NAME                :=      cub3D
CC					:=		gcc
RM 					:=		rm -rf
OS					:=		$(shell uname -s)

PATH_BUILD          :=      build
PATH_LIBFT          :=      libft
PATH_LIBMLX_MAC     :=      dependencies/minilibx-macos
PATH_LIBMLX_LINUX   :=      dependencies/minilibx-linux

SRCS_COMMON := \
    srcs/exit/exit.c \
	srcs/exit/free_assets.c \
    srcs/extract/extract_main.c \
    srcs/extract/extract_map.c \
    srcs/extract/extract_map_finalize.c \
    srcs/extract/extract_scene.c \
    srcs/extract/extract_scene_extras.c \
    srcs/extract/extract_utils.c \
    srcs/extract/validate_map.c \
    srcs/extract/validate_scene.c \
    srcs/main.c \
    srcs/play/draw/walls_ceiling_floor/draw_wall_ray.c \
    srcs/play/draw/walls_ceiling_floor/draw_floor_ceiling.c \
    srcs/play/draw/walls_ceiling_floor/get_wall_data_ray.c \
    srcs/play/draw/extras/draw_gun.c \
    srcs/play/draw/extras/draw_sprites.c \
    srcs/play/draw/extras/draw_take_damage.c \
    srcs/play/draw/extras/draw_healthbars.c \
    srcs/play/draw/extras/draw_crosshair.c \
    srcs/play/draw/menus/game_menu.c \
    srcs/play/draw/menus/game_over.c \
    srcs/play/draw/minimap/minimap.c \
    srcs/play/play.c \
    srcs/play/prepare/prepare_rays.c \
    srcs/play/prepare/prepare_player.c \
    srcs/play/prepare/textures/prepare_load_textures.c \
    srcs/play/prepare/textures/prepare_load_items.c \
    srcs/play/prepare/textures/prepare_load_weapons.c \
    srcs/play/prepare/textures/prepare_map_specials.c \
    srcs/play/prepare/textures/prepare_weapon_pos_dmg.c \
	srcs/play/prepare/hooks/events.c \
	srcs/play/prepare/hooks/keyboard_movement.c \
    srcs/play/renderables/collect_renderables.c \
    srcs/play/renderables/renderables.c \
    srcs/play/update/cast_ray/ray_cast.c \
    srcs/play/update/player/player_pos.c \
    srcs/play/update/player/player_taking_damage.c \
    srcs/play/update/shooting/handle_shooting.c \
    srcs/play/update/shooting/handle_shooting_hits.c \
    srcs/play/update/shooting/handle_shooting_traverse.c \
    srcs/play/update/shooting/switch_weapon.c \
    srcs/play/update/sprites/update_sprite_render_info.c \
    srcs/play/update/sprites/update_sprites_utils.c \
    srcs/play/update/sprites/update_sprites.c \
    srcs/play/update/sprites/update_sprite_position.c \
    srcs/play/update/sprites/update_items.c \
    srcs/play/update/sprites/spawn_items.c \
    srcs/utils/blend_colors.c \
    srcs/utils/free_str_utils.c \
    srcs/utils/math_utils.c \
    srcs/utils/t_map.c \
	srcs/utils/t_map2.c \
    srcs/utils/str_to_long.c
    
FLAG_INC			:= 		$(addprefix -I, includes $(PATH_LIBFT))

ifeq ($(OS),Linux)
    FLAG_INC += -I$(PATH_LIBMLX_LINUX)
    SRCS_PLATFORM := \
        srcs/exit/free_mlx_linux.c \
        srcs/play/prepare/hooks/mouse_linux.c \
		srcs/play/draw/menus/input_game_over_linux.c
else
    FLAG_INC += -I$(PATH_LIBMLX_MAC)
    SRCS_PLATFORM := \
        srcs/exit/free_mlx_macos.c \
        srcs/play/prepare/hooks/mouse_macos.c \
		srcs/play/draw/menus/input_game_over_macos.c
endif

SRCS := $(SRCS_COMMON) $(SRCS_PLATFORM)
OBJS				:=		$(SRCS:%.c=$(PATH_BUILD)/%.o)
DEPS				:=		$(OBJS:.o=.d)

FLAGS_COMP			:= 		-O3 -Wall -Wextra -Werror $(FLAG_INC) -MMD -MP -g 

FLAG_LIBFT			:=		-L$(PATH_LIBFT) -lft 
FLAG_LIBMLX_MAC		:=		-L$(PATH_LIBMLX_MAC) -lmlx -framework OpenGL -framework AppKit -lz
FLAG_LIBMLX_LINUX	:=		-L$(PATH_LIBMLX_LINUX) -lmlx -lX11 -lXext

ifeq ($(OS),Linux)
    FLAGS_LINKING := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_LINUX)
    FLAGS_COMP += -D LINUX
else
    FLAGS_LINKING := -lm $(FLAG_LIBFT) $(FLAG_LIBMLX_MAC)
endif

all:						init $(NAME)
							@printf "\033[0;32mGame $(NAME) created. 🎮\033[0m\n"

init:
							@ make -s -C $(PATH_LIBFT)
ifeq ($(OS),Linux)
	@ make -C $(PATH_LIBMLX_LINUX)
else
	@ make -C $(PATH_LIBMLX_MAC)
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

fclean:						clean
							@ $(RM) $(NAME)
							@ make -s -C $(PATH_LIBFT) fclean

re:							fclean all

.PHONY:						all clean fclean re

-include $(DEPS)
