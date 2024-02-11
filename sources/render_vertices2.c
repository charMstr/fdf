/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_vertices2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:18:30 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/10 20:17:15 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"


/*
** The input point sees its coordinate being projected onto the x and the y
** axis, using the z divide technique.
** This works because we always assume the canvas is one unit away from the
** viewing frustum on the z axis.
*/

void	apply_z_divide_to_3dpoint(t_2dpoint *const point2d, t_3dpoint const *const point3d)
{
	float x_proj;
	float y_proj;

	if (point3d->z == 0) // avoid divide by zero
	{
		x_proj = point3d->x;
		y_proj = point3d->y;
	}
	else if (point3d->z > 0)
	{
		x_proj = point3d->x/point3d->z;
		y_proj = point3d->y/point3d->z;
	}
	else //invert sign in the opposite case.
	{
		x_proj = - point3d->x/point3d->z;
		y_proj = - point3d->y/point3d->z;
	}
	point2d->x = x_proj;
	point2d->y = y_proj;
}

/*
** this function will remap the coordinates of the projected point into the
** NDC space (normalized device coordinate). which means a coordinate between
** [0 and 1] instead of between [-1 and 1] for example (according to the current
** field of view).
** This is done on each axis x and y.
**
** note: the FOV cannot be zero, otherwise 0 divide bug!!!
*/

void remap_coordinates_to_ndc(t_2dpoint *const point, t_camera *const camera)
{
	point->x += camera->half_width_FOV;
	point->y += camera->half_height_FOV;

	point->x /= (camera->half_width_FOV*2);
	point->y /= (camera->half_height_FOV*2);
}

/*
** This function will make the coordinates relative to the window size.
** it starts with coordinates remaped to ndc, and ends with coordinates relative
** to the screen resolution.
**
** x and y values end up between zero and window's resolution (width and height)
*/

void remap_coordinates_to_window(t_2dpoint *const point, t_window const *const window)
{
	point->x *= window->width;
	point->y *= window->height;
}

/*
** This function verifies if the point will be within the field of view, once
** projected onto the canevas.
** (it checks it is within the canevas limits, and it also checks if the
** point will be behind the camera).
**
** If not it sets the var is_outside_canevas to 1.
**
** input:
** 		- 2dpoint to check if the x' or y' projected points are outside canevas
** 		- camera: contains the FOV values.
** 		- z dimension of the 3d point transformed. needs to be behind the cam
**
** notes: Canevas full size == FOV.
*/

void set_is_outside_canevas_variable(t_2dpoint *point, t_camera const *const camera, float z)
{
	//means we are outside the boundary of the fov
	if ((point->x < -camera->half_width_FOV) \
			|| (point->x > camera->half_width_FOV) \
			|| (point->y < -camera->half_height_FOV) \
			|| (point->y > camera->half_height_FOV))
		point->is_outside_canevas = 1;
	//means the point lays in the back of the viewing frustum (camera)
	if (z > 0)
		point->is_outside_canevas = 1;
}
