/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:30:08 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/03 01:05:35 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/debug.h"
# include "../libft/libft.h"

void debug_3dpoint(t_3dpoint point)
{
	printf("[x:%d, y:%d, z:%d]", point.x, point.y, point.z);
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

int predict_max_size_str(t_raster_data *raster_data)
{
	int i;
	int j;
	int max_size_str;
	int current_size_str;

	j = 0;
	while (j < raster_data->nrows)
	{
		i = 0;
		while (i < raster_data->ncols)
		{

			if ((current_size_str = ft_size_num_base_signed((int*)(&(raster_data->map)[j][i]), 10, 1, 0)) > max_size_str)
				max_size_str = current_size_str;
			i++;
		}
		j++;
	}
	return (max_size_str);
}

void debug_raster_data(t_raster_data *raster_data)
{
	int i;
	int j;
	int max_size_str;

	max_size_str = predict_max_size_str(raster_data);
	j = 0;
	while (j < raster_data->nrows)
	{
		i = 0;
		while (i < raster_data->ncols)
		{
			printf("%*d ",max_size_str, (raster_data->map)[j][i].z);
			i++;
		}
		printf("\n");
		j++;
	}
}
