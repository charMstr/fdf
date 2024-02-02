/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 04:41:52 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 22:38:47 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_opengl/mlx.h"
#include "../includes/fdf.h"
#include "../includes/error_handling.h"

/*
** this file takes care of building the images.
*/

/*
** note:	this function will create a structure corresponding to an image, and
**			do all the mlx calls to set up the image to the asked size.
**
** note:	if the last two params are left to zero, then the window's size is
**			taken.
**
** RETURN:	1 -> ok
**			0 -> some mallocs failed inside the mlx_calls.
*/

int		create_image(t_img *img, t_fdf *fdf, int width, int height)
{
	if (width <= 0 || width >= fdf->window.width)
		width = fdf->window.width;
	if (height <= 0 || height >= fdf->window.height)
		height = fdf->window.height;
	if (!(img->img = mlx_new_image(fdf->mlx_ptr, width, height)))
		return (print_err("failure while creating new image in create_image"));
	if (!(img->data_str = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
			&(img->line_length), &(img->endian))))
		return (print_err("failed while getting data_address in create_image"));
	img->width = width;
	img->height = height;
	return (1);
}

/*
** note:	this function will simply make the image transparent so that we can
**			lay it on top of the background.
*/

void	make_image_transparent(t_img *img)
{
	int len;
	int (*tab)[img->width * img->height];
	int i;

	len = img->width * img->height;
	i = 0;
	tab = (void*)img->data_str;
	while (i < len)
	{
		tab[0][i] = TRANSPARENT;
		i++;
	}
}
