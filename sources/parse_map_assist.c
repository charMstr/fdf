/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_assist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:20:28 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/03 00:11:34 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this file takes care of loading into the structure t_raster_data the number
** of colons ncols, and the number of rows nrows. It will also make sure the
** data is in a correct format (for example no asciii characters...)
*/

#include "../libft/libft.h"
#include "../includes/structures_drawings.h"
#include "../includes/fdf.h"
#include <fcntl.h>
#include "../includes/error_handling.h"
#include "../includes/get_next_line.h"

/*
** this function will make sure a single "cell" in the input file containing
** the raster data is valid (example. containing only a string of positiv
** numbers)
**
** returns:	1 OK
** 			0 error
*/

int check_cell_is_valid(char *str, t_raster_data *raster_data)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
		{
		printf("line: %d\n", raster_data->nrows);
			print_err("invalid line: containing character other than number");
			return(0);
		}
		i++;
	}
	return (1);
}


/*
** This function updates the ncols if not set previously (parsing the very
** first line of the file containing the data points of the map).
** If it's not the first line, we just make sure its contains the right number
** of data points.
**
** return 0 if line contains either 0 data points, or a wrong number
** compared to previous lines.
*/
int check_line_is_valid_assist(t_raster_data *raster_data, int points_per_row)
{
	if (points_per_row == 0)
	{
		printf("line: %d\n", raster_data->nrows);
		print_err("this line containes no data points in data file provided");
		return (0);
	}
	if (raster_data->ncols == 0)
		raster_data->ncols = points_per_row;
	else if (raster_data->ncols != points_per_row)
	{
		printf("line: %d\n", raster_data->nrows);
		print_err("line has not the correct number of data points");
		return (0);
	}
	return 1;

}

/*
** this function makes sure one single line of the file contaning the map is
** valid
*/
int check_line_is_valid(char *line, t_raster_data *raster_data)
{
	int i;
	char **split;

	i = 0;
	if (!(split = ft_split(line, ' ')))
	{
		print_err("failure while using ft_split function");
		return -1;
	}
	while (split[i])
	{
		if (!check_cell_is_valid(split[i], raster_data))
		{
			ft_free_2d(split);
			return (0);
		}
		i++;
	}
	ft_free_2d(split);
	if (!check_line_is_valid_assist(raster_data, i))
		return (0);
	return (1); //OK
}

/*
** This function will make sure the file is valid.
** We fetch the nrows after reading each line.
** We fecth the ncols after reading the first line (each line contains a number
** of data points).
** Each folowing line must contain the same ncols.
** We also make sure the data format is valid (each line contains correct
** characters ...)
*/

int check_valid_input_data_file_and_fetch_size(char *file_name, t_raster_data *raster_data)
{
	int fd1;
	char *next_line;
	int res_gnl;

	if ((fd1 = open(file_name, O_RDONLY, 0644)) == -1)
		return (print_err("could not open data file given as parameter"));
	next_line = NULL;
	while ((res_gnl = get_next_line(fd1, &next_line)) > 0)
	{
		if (!(check_line_is_valid(next_line, raster_data)))
		{
			res_gnl = -1;
			break;
		}
		raster_data->nrows++;
		free(next_line);
	}
	close(fd1);
	if (res_gnl == -1)
	{
		free(next_line);
		return (0);
	}
	if (!(raster_data->map = (t_3dpoint**)malloc(sizeof(*(raster_data->map)) * raster_data->nrows)))
		return (0);
	return (1);
}
