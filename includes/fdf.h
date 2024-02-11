/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:04:32 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 04:10:58 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/structures_fdf.h"
# include "../includes/structures_drawings.h"
# include "../includes/defines_fdf.h"
# include "../includes/debug.h"
# include <stdlib.h>
# include <stdio.h>

int		exit_properly(t_fdf *fdf, int success);
void	free_object_projected_array(int nrow, t_2dpoint **projected_points);
void	free_object(t_object *object);

void	set_my_hooks(t_fdf *fdf);
int		deal_key_released(int key, t_fdf *fdf);
int		deal_key_pressed(int key, t_fdf *fdf);
void	set_my_hooks(t_fdf *fdf);
int		close_window_hook(t_fdf *fdf);

int		update_render_main(t_fdf *fdf);
void	fdf_set_parameters_and_start_loop(t_fdf *fdf);
int		init_mlx_parameters(t_fdf *fdf);

void	make_image_transparent(t_img *img);
int		create_image(t_img *img, t_fdf *fdf, int width, int height);

void		draw_line(t_img * const img, t_2dpoint *p1, t_2dpoint *p2, int color);
void		draw_line_bresenham(t_img * const img, t_line * const line);
int			ft_sign(int a);
int			ft_abs(int a);
void		init_line_struct_for_bresenham(t_line *line, t_2dpoint *p1, \
		t_2dpoint * p2);
void		draw_line_vert(t_img * const img, t_2dpoint p1, int height, int color);
void		draw_line_horiz(t_img * const img, t_2dpoint p1, int width, int color);

int			draw_square(t_img * const img, t_square square);
t_square	build_square(t_2dpoint p1, int width, int height, int color);
void		color_pix(t_img * const img, int y, int x, int color);


void		init_struct_fdf(t_fdf *fdf);

int			open_file_and_parse_data(char* file_name, t_object *object);
t_3dpoint	create_3dpoint(int x, int y, int z);

t_3dpoint	create_3dpoint(int x, int y, int z);

//DEBUG
void debug_array_of_3dpoint(t_3dpoint *array_of_points, int length_array);
void debug_3dpoint(t_3dpoint point);

int			check_valid_input_data_file_and_fetch_size(char *file_name, t_object *object);
int			check_cell_is_valid(char *str, t_object *object);
int			check_line_is_valid(char *line, t_object *object);
int			check_line_is_valid_assist(t_object *object, int points_per_row);


int			init_world_before_render(t_world *world);
void 		init_camera(t_camera *camera);
int			create_object_array_for_projected_points(t_object *object);
void		init_objects_metadata(t_object *object);
void		recenter_objects_data_around_self(t_object *object);


void		render_fdf_style(t_fdf *fdf, t_img *canevas);
void		draw_lines_between_2_vertices(t_fdf *fdf, t_img* canevas, \
		t_2dpoint *p1, t_2dpoint *p2, int color, t_3dpoint *p1o, \
		t_3dpoint *p2o);
void 		find_canevas_plan_intersection_and_swap_point(t_fdf *fdf, \
		t_2dpoint *p1, t_2dpoint *p2, int p1_behind_canevas_plan, \
		t_3dpoint const *const p1o, t_3dpoint const *const p2o);


void		update_transformation_matrix(t_motion *const motion, \
		t_world *const world);

int		create_pixel_shadow_array(t_window *window);
void	reset_pixel_shadow_array(t_window *window);
void	free_pixel_shadow_array(int nrow, t_pixel_shadow **array);

#endif
