/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:01:51 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 23:28:51 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include "../minilibx_opengl/mlx.h"
#include "../includes/structures_drawings.h"

/*
** note:	this is the function that will loop indefinitly. creation of a
**			buffer image, then we print it and store it (in case we will need
**			it later).
**			if a buffer was previously stored we will destroy it.
*/

int		update_render_main(t_fdf *fdf)
{
	t_img	n_img;

	if (!create_image(&n_img, fdf, fdf->window.width, fdf->window.height))
		exit_properly(fdf, EXIT_FAILURE);
	//probably no need to recreate the image each time...
	if (fdf->buffer.img)
		mlx_destroy_image(fdf->mlx_ptr, fdf->buffer.img);
	fdf->buffer = n_img;
	make_image_transparent(&n_img);
	//here do the drawings into the image.
	//if (!some_funtion(*fdf, &n_img))
	//	exit_properly(fdf, C3D_FAIL);
	draw_square(n_img, build_square(init_point_xy(0, 0), 100,\
				100, 0x00ff00));
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->window.win_ptr, n_img.img, 0, 0);
	if (fdf->stop_program)
		exit_properly(fdf, EXIT_SUCCESS);
	return (1);
}
