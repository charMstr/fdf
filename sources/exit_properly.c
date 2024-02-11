/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:26:53 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 04:58:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_opengl/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/structures_drawings.h"

void free_pixel_shadow_array(int nrow, t_pixel_shadow **array)
{
	while (--nrow > -1)
	{
		free(array[nrow]);
	}
	free (array);
	*array = NULL;
}

/*
** this function will free the array of t_2d_points if failure/stop program, or
** malloc failed when building the array at init.
*/
void free_object_projected_array(int nrow, t_2dpoint **projected_points)
{
	while (--nrow > -1)
	{
		free(projected_points[nrow]);
	}
	free (projected_points);
	*projected_points = NULL;
}

/*
** frees the map build and containing all my data points.
*/

void free_object(t_object *object)
{
	int i;

	i = 0;
	while (i < object->nrows)
	{
		if (object->original[i])
			free(object->original[i]);
		i++;
	}

	free(object->original);
	object->original = NULL;
}

/*
** function called when need to exit the program
** free anything that need to be in the fdf structure.
*/

int	exit_properly(t_fdf *fdf, int success)
{
	//free functions here

	if (fdf->window.pixel_shadow)
		free_pixel_shadow_array(fdf->window.height, fdf->window.pixel_shadow);
	if (fdf->mlx_ptr && fdf->buffer.img != NULL)
		mlx_destroy_image(fdf->mlx_ptr, fdf->buffer.img);
	if (fdf->window.win_ptr)
		free(fdf->window.win_ptr);
	if (fdf->mlx_ptr)
		free_mlx_ptr(fdf->mlx_ptr);
	if (fdf->world.object.projected)
		free_object_projected_array(fdf->world.object.nrows, fdf->world.object.projected);
	if (fdf->world.object.original)
		free_object(&fdf->world.object);
	if (success)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
