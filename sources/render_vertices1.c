/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_vertices1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:13:23 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/12 17:28:49 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"
#include "../includes/fdf.h"
#include "../includes/defines_fdf.h"

#include "../libft/libft.h"

/*
** this function is called when we want to render a pixel on screen.
** It will check wether there is already a pixel a this location.
** If the new pixel represent a point closer to the screen, the previous pixel
** is overriden.
** The shadow_pixel array is updated if:
** 	- first time we render this pixel,
** 	- new point is closer to canevas
*/

void try_to_render_pixel_and_update_pixel_shadow(t_img *canevas, \
		t_window *window, t_2dpoint *point)
{
	int x;
	int y;

	x = (int)point->x;
	y = (int)point->y;

	//solve the bug due to float conversions.
	if (x < 0 || x >= window->width || y < 0 || y >= window->height)
		return ;
	// if there is no point rendered on this pixel yet.
	if (window->pixel_shadow[y][x].displayed == NULL)
	{
		window->pixel_shadow[y][x].displayed = point;
		color_pix(canevas, point->y, point->x, point->color);
	}
	//only draw if the point is in the foreground of previous point
	else if (window->pixel_shadow[y][x].displayed->hidden_z < point->hidden_z)
	{
		color_pix(canevas, point->y, point->x, point->color);
		window->pixel_shadow[y][x].displayed = point;
	}
}

/*
** this is the main function called to render all the vertices of the object.
*/

void	render_point_cloud_style(t_img *canevas, t_fdf *fdf, t_object *object)
{
	int row;
	int column;
	t_2dpoint *point;

	row = 0;
	while (row < object->nrows)
	{
		column = 0;
		while (column < object->ncols)
		{
			update_projected_2dpoint(fdf, object, row, column);
			point = &(object->projected[row][column]);
			if (!point->is_outside_canevas)
			{
				try_to_render_pixel_and_update_pixel_shadow(canevas, &fdf->window, point);
			}
			column ++;
		}
		row++;
	}
}

/*
** this function will apply the transformation matrices (object itself,
** and camera view) to the original 2dpoint, to get the projected 3dpoint.
*/

t_3dpoint	give_transformed_3dpoint(t_matrix44 const * object_transformation, t_matrix44 const * camera_transformation, t_3dpoint const * original_point)
{
	t_3dpoint transformed_point;

	transformed_point = vector_by_matrix_product(original_point, object_transformation);
	transformed_point = vector_by_matrix_product(&transformed_point, camera_transformation);

	return (transformed_point);
}

/*
** This function receives a point (from its coordinate in the array).
** It will build the projected verion and place it into the corresponding
** location into the array object->projected[][], after applying the
** transformation matrix
*/

void 	update_projected_2dpoint(t_fdf *fdf, t_object *object, int row, int column)
{
	t_2dpoint *projected_point;
	t_3dpoint transformed_point;
	t_3dpoint const * const original_point = &object->original[row][column];

	projected_point = &object->projected[row][column];
	projected_point->is_outside_canevas = 0;
	transformed_point = give_transformed_3dpoint(&object->transformation, &fdf->world.camera.view_direction, original_point);
	apply_z_divide_to_3dpoint(projected_point, &transformed_point);
	set_is_outside_canevas_variable(projected_point, &fdf->world.camera, transformed_point.z);

	//cannot return here if we are drawing lines!!
	//optimisation only for point cloud rendering
	//if (projected_point->is_outside_canevas)
	//	return;
	//we will return here anyway since a point outside canevas will be
	//recalated.

	remap_coordinates_to_ndc(projected_point, &fdf->world.camera);
	remap_coordinates_to_window(projected_point, &fdf->window);
	projected_point->hidden_z = transformed_point.z;
}
