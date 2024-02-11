/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_fdf.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:20:59 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 04:12:25 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_FDF_H
# define STRUCTURES_FDF_H

# include "../includes/structures_drawings.h"

typedef struct		s_img
{
	void			*img;
	char			*data_str;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct		s_screen
{
	int				height;
	int				width;
}					t_screen;

/*
** used to create an array of t_pixel representing the screen
** this will be checked before rendering a pixel:
** if displayed is NULL: go! if not, we need to check the projected point's z
** value first
*/
typedef struct		s_pixel_shadow
{
	t_2dpoint		*displayed;
}					t_pixel_shadow;

typedef struct		s_motion_control
{
	float		step_shift;
	float		step_zoom;
}					t_motion_control;

typedef struct		s_window
{
	int				height;
	int				width;
	void			*win_ptr;
	t_pixel_shadow **pixel_shadow;
}					t_window;

typedef struct	s_camera
{
	t_matrix44	view_direction;
	float		half_width_FOV;
	float		half_height_FOV;
}				t_camera;

typedef struct		s_motion
{	
	unsigned int	pitch_up:1;
	unsigned int	pitch_down:1;

	unsigned int	yaw_right:1;
	unsigned int	yaw_left:1;

	unsigned int	roll_left:1;
	unsigned int	roll_right:1;

	unsigned int	zoom_in:1;
	unsigned int	zoom_out:1;

	unsigned int	shift_right:1;
	unsigned int	shift_left:1;
	unsigned int	shift_up:1;
	unsigned int	shift_down:1;
	unsigned int	shift_forward:1;
	unsigned int	shift_backward:1;

	unsigned int	apply_to_camera:1;

	unsigned int	reset_world:1;
}					t_motion;

//everything will be situated regarding the world's coordinate.
typedef struct	s_world
{
	t_camera	camera;
	t_motion	motion;
	t_object	object;
	t_motion_control motion_ctrl;
	//could have some lights here.
	//could have a list of t_object placed here as well.
}				t_world;

typedef struct		s_fdf
{
	void			*mlx_ptr;
	t_window		window;
	t_screen		screen;
	unsigned int	stop_program:1 ;
	t_img			buffer;
	t_world			world;
}					t_fdf;

#endif
