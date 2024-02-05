/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_fdf.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:20:59 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/02 21:53:18 by charmstr         ###   ########.fr       */
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

typedef struct		s_window
{
	int				height;
	int				width;
	void			*win_ptr;
}					t_window;

typedef struct		s_raster_data
{
	t_3dpoint 		**map;
	int				nrows;
	int				ncols;
}					t_raster_data;

typedef struct		s_fdf
{
	void			*mlx_ptr;
	t_window		window;
	t_screen		screen;
	unsigned int	stop_program:1 ;
	t_img			buffer;
	t_raster_data	raster_data;
}					t_fdf;

#endif
