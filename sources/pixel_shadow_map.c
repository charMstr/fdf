/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shadow_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 01:46:07 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 03:02:54 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** This file is here to create a map of t_pixel_shadow.
** Each pixel has an entry in this map. It is used to know if a pixel is
** already rendered. if so, we can decide to render again depending of the
** z value.
*/

#include "../includes/structures_fdf.h"
#include <stdlib.h>
#include "../libft/libft.h"

/*
** build the map containing each pixel's shadow.
** return:
** 	- 0 failure
** 	- 1 ok
*/

int	create_pixel_shadow_array(t_window *window)
{
	int i;
	t_pixel_shadow** array;

	i = 0;
	if (!(array = (t_pixel_shadow**)malloc(sizeof(t_pixel_shadow*) * window->height)))
		return (0);
	while (i < window->height)
	{
		if (!(array[i] = (t_pixel_shadow*)malloc(sizeof(t_pixel_shadow) * window->width)))
		{
			// [Sun 11/02/2024 at 02:35:40 //]
			//TODO (charmstr):  the exit properly function
			while (--i > -1)
				free(array[i]);
			free(array);
			return (0);
		}
		i++;
	}
	window->pixel_shadow = array;
	return (1);
}

/*
** each pointer can to a t_2dpoint. it is used to know if a pixel is already
** rendered, and if the new pixel we want to place can go on top, or be skipped
*/

void reset_pixel_shadow_array(t_window *window)
{
	int i;
	int j;

	i = 0;
	while (i < window->height)
	{
		j = 0;
		while (j < window->width)
		{
			window->pixel_shadow[i][j].displayed = NULL;
			j++;
		}
		i++;
	}
}

