/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:51:30 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 23:23:46 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/structures_drawings.h"

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

int		draw_line(t_img img, t_point p1, t_point p2, int color)
{
	t_line	line;
	int		i;

	i = -1;
	if (p1.x < 0 || p1.x >= img.width || p2.x < 0 || p2.x >= img.width \
		|| p1.y < 0 || p1.y >= img.height || p2.y < 0 || p2.y >= img.height)
		return (0);
	line.x1 = p1.x;
	line.x2 = p2.x;
	line.y1 = p1.y;
	line.y2 = p2.y;
	line.color = color;
	line.direction_slop_x = ft_sign(p2.x - p1.x);
	line.direction_slop_y = ft_sign(p2.y - p1.y);
	if (line.direction_slop_x && line.direction_slop_y)
		draw_line_bresenham(img, line);
	else if (!line.direction_slop_x)
		while (++i < ft_abs(p2.y - p1.y))
			color_pix(img, line.y1 + i * line.direction_slop_y, line.x1, \
					line.color);
	else
		while (++i < ft_abs(p2.x - p1.x))
			color_pix(img, line.y1, line.x1 + i * line.direction_slop_x, \
					line.color);
	return (1);
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

void	draw_line_bresenham(t_img img, t_line line)
{
	int	i;

	i = -1;
	init_line_struct_for_bresenham(&line);
	while (++i < line.dx)
	{
		color_pix(img, line.y1, line.x1, line.color);
		if (line.p_error > 0)
		{
			line.p_error += line.delta_perror_pos;
			if (!line.invert_step_axis)
				line.y1 += line.direction_slop_y;
			else
				line.x1 += line.direction_slop_x;
		}
		else
			line.p_error += line.delta_perror_neg;
		if (!line.invert_step_axis)
			line.x1 += line.direction_slop_x;
		else
			line.y1 += line.direction_slop_y;
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

void	init_line_struct_for_bresenham(t_line *line)
{
	line->dx = ft_abs(line->x2 - line->x1);
	line->dy = ft_abs(line->y2 - line->y1);
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
