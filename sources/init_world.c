/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:18:46 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 12:06:25 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "../includes/matrix_operations.h"
#include "../includes/structures_drawings.h"
#include <math.h>
#include "../includes/debug.h"

#include "../includes/render.h"

/*
** find object's center of gravity
*/

void	find_object_center_of_gravity(t_object *object)
{
	float number_of_points;
	t_3dpoint center_of_gravity = {.x = 0.0, .y = 0.0, .z = 0.0};

	for (int row = 0; row < object->nrows; row++)
	{
		for (int column = 0; column < object->ncols; column++)
		{
			center_of_gravity.x += object->original[row][column].x;
			center_of_gravity.y += object->original[row][column].y;
			center_of_gravity.z += object->original[row][column].z;
		}
	}
	number_of_points = (float)(object->ncols * object->nrows);
	center_of_gravity.x /= number_of_points;
	center_of_gravity.y /= number_of_points;
	center_of_gravity.z /= number_of_points;

	object->center_of_gravity = center_of_gravity;
}

/*
** this function is bad since it alters the original data_points
** it will recenter the object on its "center of gravity".
*/
//this could be done with a matrix on the object while rendering on each loop.


void shift_center_of_data_to_center_of_gravity(t_object *object)
{
	for (int row = 0; row < object->nrows; row++)
	{
		for (int column = 0; column < object->ncols; column++)
		{
			object->original[row][column].x -= object->center_of_gravity.x;
			object->original[row][column].y -= object->center_of_gravity.y;
			object->original[row][column].z -= object->center_of_gravity.z;
		}
	}
}

void recenter_objects_data_around_self(t_object *object)
{
	int row;
	int column;
	float shift_x;
	float shift_y;
	float shift_z;

	row = 0;
	shift_x = object->ncols / 2.0;
	shift_y = object->nrows / 2.0;
	shift_z = object->delta_z_original / 2.0;
	while (row < object->nrows)
	{
		column = 0;
		while (column < object->ncols)
		{
			object->original[row][column].x -= shift_x;
			object->original[row][column].y -= shift_y;
			object->original[row][column].z -= shift_z;
			column ++;
		}
		row++;
	}
}

/*
** this function will get the information relatives to the maximum and minimum
** height of the vertices for a given object. it will be usefull for
** calculating the "center of gavity", the color gradient.
*/

float find_objects_delta_z(t_object const *object)
{
	int row;
	int column;
	float min_z;
	float max_z;

	row = 0;
	while (row < object->nrows)
	{
		column = 0;
		if (!row && !column)//very first loop
		{
			max_z = object->original[row][column].z;
			min_z = object->original[row][column].z;
		}
		while (column < object->ncols)
		{
			if (object->original[row][column].z < min_z)
				min_z = object->original[row][column].z;
			if (object->original[row][column].z > max_z)
				max_z = object->original[row][column].z;
			column ++;
		}
		row++;
	}
	return (max_z - min_z);
}

/*
** this function is entered when point->color corresponds to the initial z
** value of the given point.
** point->color is reencoded to a certain value.
*/

void	encode_color_of_point(t_2dpoint *point, float delta_z_for_object, float z_original_point)
{
	point->color = COLOR_MIN_HEIGHT + (z_original_point/delta_z_for_object) * (COLOR_MAX_HEIGHT - COLOR_MIN_HEIGHT);
}

/*
** this function will loop over the array and set the color for each point
** (relative to the original z value.)
*/
void fill_array_with_points_initialised_with_color_encoded(t_object *object)
{
	int row;
	int column;

	row = 0;
	while (row < object->nrows)
	{
		column = 0;
		while (column < object->ncols)
		{
			encode_color_of_point(&object->projected[row][column], object->delta_z_original, object->original[row][column].z);
			column ++;
		}
		row++;
	}
}

/*
** This function will prepare the object for render.
** It will get the delta of the z axis.
** It will recenter the cloud point on its "center of gravity".
** It will set the encoded color for each point once and for all.
*/

void init_objects_metadata(t_object *object)
{
	object->delta_z_original = find_objects_delta_z(object);
	fill_array_with_points_initialised_with_color_encoded(object);
	find_object_center_of_gravity(object);
	//recenter_objects_data_around_self(object);
	shift_center_of_data_to_center_of_gravity(object);
}

void 	init_camera(t_camera *camera)
{
	ft_bzero(camera, sizeof(t_camera));
	set_matrix_to_identity(&camera->view_direction);
	//arbitrary at first.
	camera->half_width_FOV = 1;
	camera->half_height_FOV = 1;
}

/*
** this function resets ths object at start
*/
void place_object_in_front_camera(t_object * const object)
{
	t_matrix44 transformation_at_start;

	set_matrix_to_identity(&object->transformation);
	transformation_at_start = translation_transformation(0, 0, \
			- (object->delta_z_original + 10));
			//arbitrary number to set the object in the back of the canevas
	object->transformation = matrix_product(&transformation_at_start, \
			&object->transformation);
}

/*
** initialises the world, its camera and its canevas before we start to render.
*/
int	init_world_before_render(t_world *world)
{
	init_camera(&world->camera);
	ft_bzero(&world->motion, sizeof(t_motion));
	place_object_in_front_camera(&world->object);
	return (0);
}
