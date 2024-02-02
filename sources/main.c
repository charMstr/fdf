/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:00:32 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 23:50:32 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error_handling.h"
#include "../minilibx_opengl/mlx.h"
#include "../libft/libft.h"
#include <stdlib.h>

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
** set parameters, then start the  main loop.
*/
void fdf_set_parameters_and_start_loop(t_fdf *fdf)
{
	mlx_loop(fdf->mlx_ptr);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	t_fdf fdf;

	init_struct_fdf(&fdf);
	//usefull if i want to have the size of the window parsed in my config file.
	//should be parsed from file later on
	// [Mon 29/01/2024 at 20:46:10]
	//TODO (charmstr): do a function here for parsing this matter.
	fdf.window.height = 500;
	fdf.window.width = 800;

	if (!init_mlx_parameters(&fdf))
	{
		return (EXIT_FAILURE);
	}
	fdf_set_parameters_and_start_loop(&fdf);
}
