/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:16:26 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 04:24:41 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../includes/structures_fdf.h"
# include "../includes/matrix_operations.h"
# include "../includes/structures_drawings.h"

void		render_point_cloud_style(t_img *canevas, t_fdf *fdf, \
		t_object *object);
void		apply_z_divide_to_3dpoint(t_2dpoint *const point2d, \
		t_3dpoint const *const point3d);
void		remap_coordinates_to_ndc(t_2dpoint *const point, \
		t_camera *const camera);
void		remap_coordinates_to_window(t_2dpoint *const point, \
		t_window const *const window);
void		set_is_outside_canevas_variable(t_2dpoint *point, \
		t_camera const *const camera, float z);

t_3dpoint	give_transformed_3dpoint(t_matrix44 const *object_transformation, \
		t_matrix44 const * camera_transformation, \
		t_3dpoint const * original_point);
void		update_projected_2dpoint(t_fdf *fdf, t_object *object, int row, \
		int column);
void		render_point_cloud_style(t_img *canevas, t_fdf *fdf, \
		t_object *object);
void		try_to_render_pixel_and_update_pixel_shadow(t_img *canevas,
		t_window *window, t_2dpoint *point);

#endif
