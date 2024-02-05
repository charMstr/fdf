/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:04:32 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/02 23:52:39 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/structures_fdf.h"
# include "../includes/structures_drawings.h"
# include "../includes/defines_fdf.h"
# include <stdlib.h>
# include <stdio.h>

void	set_my_hooks(t_fdf *fdf);
int		deal_key_released(int key, t_fdf *fdf);
int		deal_key_pressed(int key, t_fdf *fdf);
void	set_my_hooks(t_fdf *fdf);
int		close_window_hook(t_fdf *fdf);
int		exit_properly(t_fdf *fdf, int success);
int		update_render_main(t_fdf *fdf);
void	fdf_set_parameters_and_start_loop(t_fdf *fdf);
int		init_mlx_parameters(t_fdf *fdf);

void	make_image_transparent(t_img *img);
int		create_image(t_img *img, t_fdf *fdf, int width, int height);

int			draw_line(t_img img, t_point p1, t_point p2, int color);
void		draw_line_bresenham(t_img img, t_line line);
int			ft_sign(int a);
int			ft_abs(int a);
void		init_line_struct_for_bresenham(t_line *line);
t_point		init_point_xy(float x, float y);
void		draw_line_vert(t_img img, t_point p1, int height, int color);
void		draw_line_horiz(t_img img, t_point p1, int width, int color);

int			draw_square(t_img img, t_square square);
t_square	build_square(t_point p1, int width, int height, int color);
void		color_pix(t_img img, int y, int x, int color);


void		init_struct_fdf(t_fdf *fdf);
t_point		init_point_xy(float x, float y);

int			open_file_and_parse_data(char* file_name, t_raster_data *raster_data);
t_3dpoint	create_3dpoint(int x, int y, int z);

t_3dpoint	create_3dpoint(int x, int y, int z);

//DEBUG
void debug_array_of_3dpoint(t_3dpoint *array_of_points, int length_array);
void debug_3dpoint(t_3dpoint point);

int			check_valid_input_data_file_and_fetch_size(char *file_name, t_raster_data *raster_data);
int			check_cell_is_valid(char *str, t_raster_data *raster_data);
int			check_line_is_valid(char *line, t_raster_data *raster_data);
int			check_line_is_valid_assist(t_raster_data *raster_data, int points_per_row);

#endif
