/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:01:51 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/12 17:21:43 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include "../minilibx_opengl/mlx.h"
#include "../includes/render.h"
#include "../includes/structures_drawings.h"
#include "../includes/matrix_operations.h"
#include "../libft/libft.h"


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
	fdf->buffer = n_img;
	//make_image_transparent(&n_img);
	update_transformation_matrix(&fdf->world.motion, &fdf->world);

	//here do the drawings into the image.
	//if (!some_funtion(*fdf, &n_img))
	//	exit_properly(fdf, C3D_FAIL);
	reset_pixel_shadow_array(&fdf->window);
	//render_point_cloud_style(&n_img, fdf, &fdf->world.object);
	render_fdf_style(fdf, &n_img);
	//debug_shadow_pixel_array(&fdf->window);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->window.win_ptr, n_img.img, 0, 0);
	//debug_matrix44(&fdf->world.object.transformation);

	mlx_destroy_image(fdf->mlx_ptr, fdf->buffer.img);
	fdf->buffer.img = NULL;
	if (fdf->stop_program)
		exit_properly(fdf, EXIT_SUCCESS);
	return (1);
}
