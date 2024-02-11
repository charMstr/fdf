/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:30:08 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 03:32:35 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/debug.h"
# include "../libft/libft.h"

void debug_3dpoint(t_3dpoint point)
{
	printf("[x:%.2f, y:%.2f, z:%.2f]\n", point.x, point.y, point.z);
}

void debug_array_of_3dpoint(t_3dpoint *array_of_points, int length_array)
{
	int i;

	i = 0;
	while (i < length_array)
	{
		debug_3dpoint(array_of_points[i]);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void debug_object(t_object *object)
{
	int i;
	int j;

	j = 0;
	while (j < object->nrows)
	{
		i = 0;
		while (i < object->ncols)
		{
			printf("%*.f ", 3, (object->original)[j][i].z);
			i++;
		}
		printf("\n");
		j++;
	}
}

/*
** used to debug the matrix structur
*/
void debug_matrix44(const t_matrix44 * const matrix)
{
	int i = 0;
	int j;

	while (i < 4)
	{
		j = 0;
		printf("[");
		while (j < 4)
		{
			printf("%*.0f",4,  matrix->m[i][j]);
			j++;
		}
		printf("]\n");
		i++;
	}
	printf("\n");
}

void debug_2dpoint(const t_2dpoint * const point)
{
	printf("x:%.f\n", point->x);
	printf("y:%.f\n", point->y);
	printf("is_outside_canevas: %d\n", point->is_outside_canevas);
}

void 	debug_shadow_pixel_array(t_window* window)
{
	int i = 0;
	int j =0;
	t_2dpoint p;

	while (i < window->height)
	{
		j = 0;
		while (j < window->width)
		{
			if (window->pixel_shadow[i][j].displayed)
			{
				p = *window->pixel_shadow[i][j].displayed;
				printf("for point x:%f\n, y: %f", p.x, p.y);
			}
			j++;
		}
		i++;
	}
}
