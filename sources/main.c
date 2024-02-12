/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:00:32 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 11:52:12 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error_handling.h"
#include "../minilibx_opengl/mlx.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/debug.h"
#include "../includes/matrix_operations.h"

/*
** initialise all the required elements by the mlx for connection with display
** and such and set up of the window size
**
** RETURN: 1 OK, 0 KO
*/

int init_mlx_parameters(t_fdf *fdf)
{
	if (!(fdf->mlx_ptr = mlx_init(&(fdf->screen.height), &(fdf->screen.width))))
		return (print_err("failure initialising mlx connection with display"));
	//resize the window if too big compared to the screen's size
	if (fdf->window.height > fdf->screen.height)
		fdf->window.height = fdf->screen.height;
	if (fdf->window.width > fdf->screen.width)
		fdf->window.width = fdf->screen.width;
	if (!(fdf->window.win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->window.width, fdf->window.height, "fdf de charlie")))
	{
		free_mlx_ptr(fdf);
		return (print_err("failure from mlx creating new window)"));
	}
	set_my_hooks(fdf);
	mlx_loop_hook(fdf->mlx_ptr, update_render_main, (t_fdf *)fdf);
	return (1);
}

/*
** this function will build an array in which we sill store for each 3d point
** from the object, its corresponding projection 2d points before render.
**
** note: we keep the t_3dpoint structure, because we will need the z coordinate
** to encode the color of the pixel.
** return	1 = OK,
** 			0 = KO
*/

int create_object_array_for_projected_points(t_object *object)
{
	int i;
	t_2dpoint **projected;

	i = 0;
	if (!(projected = (t_2dpoint**)malloc(sizeof(t_2dpoint*) * object->nrows)))
		return (0);
	while (i < object->nrows)
	{
		if (!(projected[i] = (t_2dpoint*)malloc(sizeof(t_2dpoint) * object->ncols)))
		{
			free_object_projected_array(i, projected);
			return (0);
		}
		i++;
	}
	object->projected = projected;;
	return (1);
}

void set_speed_for_motions(t_object *object, t_fdf *fdf)
{
	float max_side;

	if (object->ncols > object->nrows)
		max_side = object->ncols;
	else
		max_side = object->nrows;
	if (max_side < object->delta_z_original)
		max_side = object->delta_z_original;

	fdf->world.motion_ctrl.step_shift = max_side * 0.02;
	fdf->world.motion_ctrl.step_zoom = max_side * 0.02;
}

/*
** set parameters, then start the  main loop.
*/
void fdf_set_parameters_and_start_loop(t_fdf *fdf)
{
	if (!(create_object_array_for_projected_points(&fdf->world.object)))
		exit_properly(fdf, EXIT_FAILURE);
	if (!(create_pixel_shadow_array(&fdf->window)))
		exit_properly(fdf, EXIT_FAILURE);
	init_objects_metadata(&fdf->world.object);
	init_world_before_render(&fdf->world);
	set_speed_for_motions(&fdf->world.object, fdf);

	mlx_loop(fdf->mlx_ptr);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	t_fdf fdf;

	init_struct_fdf(&fdf);
	//ARBITRARY SIZE FOR WINDOW CREATION
	fdf.window.height = 500;
	fdf.window.width = 800;

	if (argc >2)
		return (print_err("no more than 2 args"));
	else if (argc <2)
		return (print_err("need one arg: the file containing the map data. ex: 42.fdf"));

	if(!(open_file_and_parse_data(argv[1], &fdf.world.object)))
		exit_properly(&fdf, EXIT_FAILURE);
	//DEBUG
//	debug_object(&fdf.object);
	if (!init_mlx_parameters(&fdf))
		exit_properly(&fdf, EXIT_FAILURE);
	fdf_set_parameters_and_start_loop(&fdf);
}
