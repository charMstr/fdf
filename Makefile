# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 17:46:05 by charmstr          #+#    #+#              #
#    Updated: 2024/02/11 01:53:10 by charmstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################ INCLUDE OTHER MAKEFILE ###########################
###############################################################################
#-include <file_name>.mk
# '-' so if the file does not exist --> silent
###############################################################################
###############################################################################


############################ SETTINGS #########################################
###############################################################################
CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = fdf
IFLAGS = -I $(INCLUDE_PATH_PROJECT) -I $(INCLUDE_PATH_MLX)
LDFLAGS = -lm -lmlx -framework OpenGL -framework AppKit -lft

LIBFT = libft/libft.a 
MINILIBX = minilibx_opengl/libmlx.a
DEPS = $(INCLUDES)
#DEPS_BONUS = $(INCLUDES_BONUS)
###############################################################################
###############################################################################

########################### PARAMETERS ########################################
###############################################################################
ifeq ($(f), n)
CFLAGS 		=
VALGRIND 	=
else ifeq ($(f), f)
CFLAGS 		+=  -fsanitize=address,undefined -g3
VALGRIND 	=
else ifeq ($(f), v)
CFLAGS 		+= -g3
SHOW_LEAK 	= --show-leak-kinds=definite
VALGRIND 	= valgrind --track-origins=yes --leak-check=full $(SHOW_LEAK)
endif
###############################################################################
###############################################################################


############################ PATHS ############################################
###############################################################################
OBJ_PATH = ./objects/
SRC_PATH = ./sources/
INCLUDE_PATH_PROJECT = ./includes/
INCLUDE_PATH_MLX = ./minilibx_opengL/
LIB_PATH = -L ./libft/ -L ./minilibx_opengl/
###############################################################################
###############################################################################


########################### HEADER FILES ######################################
###############################################################################
H_FILES = fdf\
		  get_next_line\
		  error_handling\
		  structures_fdf\
		  defines_fdf\
		  structures_drawings\
		  debug\
		  matrix_operations\
		  render\
		  

#H_FILES_BONUS = #somefile\
				#someotherFile\

INCLUDES := $(patsubst %, $(INCLUDE_PATH_PROJECT)%.h, $(H_FILES))

# ADD EXTRANEOUS INCLUDES HERE
INCLUDES := $(INCLUDES) ./libft/libft.h

#INCLUDES_BONUS := $(patsubst %, $(INCLUDE_PATH_PROJECT)%.h, $(H_FILES_BONUS))
#INCLUDES_BONUS := $(INCLUDES_BONUS) ./libft/libft.h
###############################################################################
###############################################################################


########################### SRC/OBJ & BONUS FILES #############################
###############################################################################
SRC_FILES = main\
			get_next_line\
			get_next_line_utils\
			error_handling\
			hooks_set_functions\
			exit_properly\
			rendering_loop\
			render_vertices1\
			render_vertices2\
			image_create\
			draw_square\
			draw_line1\
			draw_line2\
			3dpoints\
			init_structures\
			parse_map\
			parse_map_assist\
			debug\
			init_world\
			matrix_operations\
			vectors_operations\
			update_transformation_matrix\
			render_fdf_style\
			pixel_shadow_map\

			#ft_printf\
			
#BONUS_FILES = 

SRC = $(patsubst %, $(SRC_PATH)%.c, $(SRC_FILES))
OBJ = $(patsubst %, $(OBJ_PATH)%.o, $(basename $(notdir $(SRC))))

#SRC_BONUS = $(patsubst %, $(SRC_PATH)%.c, $(BONUS_FILES))
#OBJ_BONUS = $(patsubst %, $(OBJ_PATH)%.o, $(basename $(notdir $(SRC_BONUS))))
###############################################################################
###############################################################################

###############################################################################
############################### COLOR CODE ####################################
REMOVE_FG = \033[38;5;196m 
CREAT_FG = \033[38;5;46m
BLACK_FG = \033[38;5;0m
BLACK_BG = \033[48;5;0m
CLEAR_COLOR = \033[m
NAME_BG = \033[48;5;39m 
OBJECTS_BG = \033[48;5;11m
###############################################################################
###############################################################################

all: $(NAME) | silent

silent:
	@:

.PHONY: all clean fclean re break_implicit_r

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@echo "\t\t$(CREAT_FG)created the $(OBJECTS_BG)$(BLACK_FG)$@ $(BLACK_BG)$(CREAT_FG) repository$(CLEAR_COLOR) for $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG)"

$(NAME): $(INCLUDES) $(MINILIBX) $(LIBFT) $(OBJ)
	@echo "\t\t$(CREAT_FG)building binary $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG)...$(CLEAR_COLOR)"
	@$(CC) $(CFLAGS) $(LIB_PATH) $(OBJ) -o $@ $(LDFLAGS)
	@echo "\t\t$(CREAT_FG)used the flags: $(CFLAGS)$(CLEAR_COLOR)\n"

$(OBJ): $(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPS) | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

bonus:

$(LIBFT): break_implicit_r
	@make -C ./libft

$(MINILIBX): break_implicit_r
	@make -C ./minilibx_opengl

break_implicit_r: 

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make fclean -C ./libft
	@make clean -C ./minilibx_opengl
	@rm -rf $(MINILIBX)
	@rm -rf $(NAME)

re: fclean all
