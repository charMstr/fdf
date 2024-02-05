/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:26:53 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/03 00:10:17 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_opengl/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/structures_drawings.h"

/*
** frees the map build and containing all my data points.
*/

void free_map(t_raster_data *raster_data)
{
	int i;

	i = 0;
	while (i < raster_data->nrows)
	{
		if (raster_data->map[i])
			free(raster_data->map[i]);
		i++;
	}
	free(raster_data->map);
}

/*
** function called when need to exit the program
** free anything that need to be in the fdf structure.
*/

int	exit_properly(t_fdf *fdf, int success)
{
	//free functions here

	if (fdf->window.win_ptr)
		free(fdf->window.win_ptr);
	if (fdf->mlx_ptr)
		free_mlx_ptr(fdf->mlx_ptr);
	if (fdf->raster_data.map)
	{
		free_map(&fdf->raster_data);
	}
	if (success)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
