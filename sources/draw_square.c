/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:30:34 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 23:21:03 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_opengl/mlx.h"
#include "../libft/libft.h"
#include "../includes/structures_drawings.h"
#include "../includes/structures_fdf.h"

/*
** this file will be used to draw a pixel, or a square
*/

/*
** note:	this function will cast the long string pointer into an pointer
**			to int arrays. we change the four bytes at once. a pixel at a time.
*/

void		color_pix(t_img img, int y, int x, int color)
{
	int (*tab)[img.width];

	tab = (void*)img.data_str;
	tab[y][x] = color;
}

/*
** note:	this function will build a square structure that will be then put
**			inside the image address.
*/

t_square	build_square(t_point p1, int width, int height, int color)
{
	t_square square;

	if (width < 0)
	{
		square.x = p1.x - width;
		square.width = -width;
	}
	else
	{
		square.x = p1.x;
		square.width = width;
	}
	if (height < 0)
	{
		square.y = p1.y - height;
		square.height = -height;
	}
	else
	{
		square.y = p1.y;
		square.height = height;
	}
	square.color = color;
	return (square);
}

/*
** note:	this function will draw the square previously prepared by the
**			build_square() func, into the image addres space.
**
** RETURN:	1 -> ok
** 			0 -> tried to draw outside the img's bitmap.
*/

int			draw_square(t_img img, t_square square)
{
	int i;
	int j;

	i = 0;
	if (square.x < 0 || square.x + square.width > img.width)
		return (0);
	if (square.y < 0 || square.y + square.height > img.height)
		return (0);
	while (i < square.height)
	{
		j = 0;
		while (j < square.width)
		{
			color_pix(img, square.y + i, square.x + j, square.color);
			j++;
		}
		i++;
	}
	return (1);
}
