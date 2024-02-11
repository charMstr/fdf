/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:51:30 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/10 12:06:48 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/structures_drawings.h"
#include <math.h>

/*
** this file will handle the line drawing.
*/

/*
** note:	this is the root function for line drawing. If the line is neither
**			vertical nor horizontal, we will call the bresenham algorithm.
**
** note:	for optimisation purpose we just use a while loop for vertical or
**			horizontal lines.
**
** note:	the point has to be img.width/height - 1 at maximum
**
** RETURN:	1 -> alright
**			0 -> to draw outside the img boundaries.
*/

void	draw_line(t_img * const img, t_2dpoint *p1, t_2dpoint *p2, int color)
{
	t_line	line;
	int		i;

	i = -1;
	line.x = p1->x;
	line.y = p1->y;
	line.color = color;
	line.direction_slop_x = ft_sign(p2->x - p1->x);
	line.direction_slop_y = ft_sign(p2->y - p1->y);
	init_line_struct_for_bresenham(&line, p1, p2);
	if (line.direction_slop_x && line.direction_slop_y)
		draw_line_bresenham(img, &line);
	else if (!line.direction_slop_x)
		while (++i < ft_abs(p2->y - p1->y))
			color_pix(img, p1->y + i * line.direction_slop_y, p1->x, \
					line.color);
	else
		while (++i < ft_abs(p2->x - p1->x))
			color_pix(img, p1->y, p1->x + i * line.direction_slop_x, \
					line.color);
}

/*
** note:	this function implements the Bresenham algorithm:
**			according to the signe of p_error:
**			- negative: -> y stays the same.
**						-> p_error = p_error + 2dy
**			- positive:	-> y += 1;
**						-> p_error = p_error + 2dy - 2dx
**
**			the very first p_error is 2dy - dx
**
** note: this is valid for the slop inferior to 1.
*/

void	draw_line_bresenham(t_img * const img, t_line * const line)
{
	int	i;

	i = -1;
	while (++i < line->dx)
	{
		color_pix(img, line->y, line->x, line->color);
		if (line->p_error > 0)
		{
			line->p_error += line->delta_perror_pos;
			if (!line->invert_step_axis)
				line->y += line->direction_slop_y;
			else
				line->x += line->direction_slop_x;
		}
		else
			line->p_error += line->delta_perror_neg;
		if (!line->invert_step_axis)
			line->x += line->direction_slop_x;
		else
			line->y += line->direction_slop_y;
	}
}

/*
** note:	this function will Return the sign of an int.
**
** RETURN:	-1, 0 or 1
*/

int		ft_sign(int a)
{
	if (!a)
		return (0);
	else if (a > 0)
		return (1);
	return (-1);
}

/*
** RETURN:	the absolute value of an integer;
*/

int		ft_abs(int a)
{
	if (a >= 0)
		return (a);
	else
		return (-a);
}

/*
** note:	the structure line was already partially filled before deciding
**			if yes or nowe would use the bresenham algorithm.
**
** note:	this function pre-calculates all the necessary values for the
**			line drawing when using the bresenham algorithm. especially the
**			values that are redundant.
**
** note:	if the delta_x is inferior to the delta_y, we swap them for all
**			the rest of the algotithm so that we can take sample steps on the y
**			axis one at a time(instead of the x abscisse).
*/

void	init_line_struct_for_bresenham(t_line *line, t_2dpoint *p1, t_2dpoint * p2)
{
	line->dx = ft_abs(p2->x - p1->x);
	line->dy = ft_abs(p2->y - p1->y);
	if (line->dx >= line->dy)
		line->invert_step_axis = 0;
	else
	{
		line->dx ^= line->dy;
		line->dy ^= line->dx;
		line->dx ^= line->dy;
		line->invert_step_axis = 1;
	}
	line->delta_perror_neg = 2 * line->dy;
	line->delta_perror_pos = line->delta_perror_neg - 2 * line->dx;
	line->p_error = line->delta_perror_neg - line->dx;
}
