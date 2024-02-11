/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf_style.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:49:13 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 00:47:39 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/render.h"
#include <math.h>

/*
** this function will fill the array of points at init. most importantly, it
** will encode the color of each point.
*/
void fill_array_with_projected_points(t_fdf *fdf, t_object *object)
{
	int row;
	int column;

	row = 0;
	while (row < object->nrows)
	{
		column = 0;
		while (column < object->ncols)
		{
			update_projected_2dpoint(fdf, object,row, column);
			column ++;
		}
		row++;
	}
}

///join the dots with lines. the fdf project!
void	render_fdf_style(t_fdf *fdf, t_img *canevas)
{
	int row;
	int column;

	row = 0;
	fill_array_with_projected_points(fdf, &fdf->world.object);
	while (row < fdf->world.object.nrows)
	{
		column = 0;
		while (column < fdf->world.object.ncols)
		{
			//means we are onto the second point in column at least.
			if (column)
			{
				draw_lines_between_2_vertices(fdf, canevas, \
					&fdf->world.object.projected[row][column - 1], \
					&fdf->world.object.projected[row][column], 0x00ff00, \
					&fdf->world.object.original[row][column - 1], \
					&fdf->world.object.original[row][column]);

			}
			// means we are onto the second point in row at least.
			if (row)
				draw_lines_between_2_vertices(fdf, canevas, \
					&fdf->world.object.projected[row - 1][column], \
					&fdf->world.object.projected[row][column], 0x00ff00, \
					&fdf->world.object.original[row - 1][column], \
					&fdf->world.object.original[row][column]);
			column ++;
		}
		row++;
	}
}

/*
** This function is called when either one of the points lays on the wrong
** side of the canevas plan. Remember: we keep the viewing frustum clear.
** It means we cannot draw a full line, we will have to
** find a new point that is the intersection of the line with the canevas.
** (this new point will be swapped instead of the point that is off limits).
*/
void 	find_canevas_plan_intersection_and_swap_point(t_fdf *fdf, t_2dpoint *p1, t_2dpoint *p2, int p1_behind_canevas_plan, t_3dpoint const *const p1o, t_3dpoint const *const p2o)
{
	float depth_ratio_t1_dz;
	float t1_to_canevas;
	float dz;
	t_2dpoint intersect_canevas_plan;
	t_3dpoint t1;
	t_3dpoint t2;
	t1 = vector_by_matrix_product(p1o, &fdf->world.object.transformation);
	t1 = vector_by_matrix_product(&t1, &fdf->world.camera.view_direction);
	t2 = vector_by_matrix_product(p2o, &fdf->world.object.transformation);
	t2 = vector_by_matrix_product(&t2, &fdf->world.camera.view_direction);

	dz = fabs(t2.z - t1.z);
	t1_to_canevas = fabs((-1) - t1.z);
	depth_ratio_t1_dz =  t1_to_canevas / dz;
	intersect_canevas_plan.x = t1.x + depth_ratio_t1_dz * (t2.x - t1.x);
	intersect_canevas_plan.y = t1.y + depth_ratio_t1_dz * (t2.y - t1.y);
	//here we have the coordinate of the point lying in the canevas plan.
	//need now to normalize it

	remap_coordinates_to_ndc(&intersect_canevas_plan, &fdf->world.camera);
	remap_coordinates_to_window(&intersect_canevas_plan, &fdf->window);

	if (p1_behind_canevas_plan)
	{ // we draw between p1 and new point
		p2->color = 1;
		p2->hidden_z = 1;
		p2->x = intersect_canevas_plan.x;
		p2->y = intersect_canevas_plan.y;
	}
	else
	{ // we draw between p2 and new point
		p1->color = 1;
		p1->hidden_z = 1;
		p1->x = intersect_canevas_plan.x;
		p1->y = intersect_canevas_plan.y;
	}
}

/*
** this function is meant to pass a few conditions before caling the algorithm
** to actually draw lines.
**
** we can modify a point's coordinate to make sure only the correct port
** will be attempted to be drawn on screen (optimisation++).
*/

void	draw_lines_between_2_vertices(t_fdf *fdf, t_img* canevas, t_2dpoint *p1, t_2dpoint *p2, int color, t_3dpoint *p1o, t_3dpoint *p2o)
{
	if (p1->hidden_z >= -1 && p2->hidden_z >= -1)
		return; // nothing to draw, both points lay in the plan between the
	//camera and the canevas. keep this space clear..

	//at least one point lays before the canevas plan.
	if (p1->hidden_z >= -1 || p2->hidden_z >= -1)
	{
		if (p1->hidden_z >= -1)
		find_canevas_plan_intersection_and_swap_point(fdf, p1, p2, 0, p1o, p2o);
		else
			find_canevas_plan_intersection_and_swap_point(fdf, p1, p2, 1, p1o, p2o);
	}

	//here is both points are outisde the FOV but on the good side of the canevas, we can optimize by finding the coordinate that starts at the border of the screen.
	draw_line(canevas, p1, p2, color);
}
