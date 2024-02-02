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

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

SRC = mlx_init_loop.m\
		mlx_int_str_to_wordtab.c\
		mlx_mouse.m\
		mlx_new_image.m\
		mlx_new_window.m\
		mlx_opengl.m\
		mlx_png.c\
		mlx_shaders.c\
		mlx_xpm.c\

INCLUDES= mlx_opengl.h\
		  mlx_int.h\
		  mlx.h\
		  mlx_new_window.h\
		  mlx_png.h

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

all: $(NOM) | silent

silent:
	@:

$(NOM):	$(INCLUDES) $(SRC) $(OBJ)
	@echo "\t\t$(CREAT_FG)building Library $(NAME_BG)$(BLACK_FG)$(NOM) $(BLACK_BG)$(CREAT_FG)...$(CLEAR_COLOR)"
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

re: clean all
