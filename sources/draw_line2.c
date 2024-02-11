/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:30:47 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/09 11:21:55 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** this file will handle the line drawing (part 2)
*/

/*
** note:	this function will draw a horizontal line
*/

void	draw_line_horiz(t_img * const img, t_2dpoint p1, int width, int color)
{
	int i;

	i = 0;
	while (i <= width && i < img->width)
	{
		color_pix(img, p1.y, p1.x + i, color);
		i++;
	}
}

/*
** note:	this function will draw a vertical line
*/

void	draw_line_vert(t_img * const img, t_2dpoint p1, int height, int color)
{
	int i;

	i = 0;
	while (i <= height & i < img->height)
	{
		color_pix(img, p1.y + i, p1.x, color);
		i++;
	}
}
