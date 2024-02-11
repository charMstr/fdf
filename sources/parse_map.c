/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:36:32 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/09 11:34:46 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this file aims to parse the map, which is raster data. where the position in
** the file corresponds to the x and y coordinate. and the value corresponds to
** the z coordinate.
*/

#include "../includes/fdf.h"
#include <fcntl.h>
#include "../includes/error_handling.h"
#include "../includes/get_next_line.h"
#include "../libft/libft.h"
#include "../includes/debug.h"

/*
** this func will parse a line of data from the file_name containing the map.
** input:
** 	row_number: the current row of data/current line (ex: first row means y=0)
** 	line: the raw string containing the data points from a given row.
**
** return:
** 	0 if failed
** 	1 OK (one row of 3d points added in object->map)
*/

int from_line_insert_row_of_3d_points(t_object *object, char *line, int row_number)
{
	t_3dpoint *row;
	char **array_of_3dpoints;
	int i;

	if (!(array_of_3dpoints = ft_split(line, ' ')))
		return (0);
	if (!(row = malloc (sizeof(*row) * object->ncols)))
	{
		ft_free_2d(array_of_3dpoints);
		return (0);
	}

	i = 0;
	while (i < object->ncols)
	{
		row[i] = create_3dpoint(i, row_number, atoi(array_of_3dpoints[i]));
		i++;
	}
	object->original[row_number] = row;
	ft_free_2d(array_of_3dpoints);
	return 1;
}



/*
** this is the root function for parsing the file containing the data of the
** map. it opens the file, gets line after line and builds gradually a 2
** dimensions array containing in each cell a 3dpoint (x, y, and z values).
*/

int open_file_and_parse_data(char* file_name, t_object *object)
{
	int fd1;
	char *next_line;
	int current_row;
	int result_gnl;

	if (!(check_valid_input_data_file_and_fetch_size(file_name, object)))
		return 0;
	if ((fd1 = open(file_name, O_RDONLY, 0644)) == -1)
		return (print_err("could not open data file given as parameter"));
	current_row = 0;
	next_line = NULL;
	while ((result_gnl = get_next_line(fd1, &next_line)) > 0)
	{
		if (!from_line_insert_row_of_3d_points(object, next_line, current_row))
		{
			result_gnl = -1;
			break;
		}
		current_row++;
		free(next_line);
	}
	close(fd1);
	if (result_gnl == -1)
	{
		free(next_line);
		return (0);
	}
	return (1);
}
