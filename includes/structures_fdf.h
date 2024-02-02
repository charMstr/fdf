/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_fdf.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:20:59 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 23:16:34 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_FDF_H
# define STRUCTURES_FDF_H

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

typedef struct		s_fdf
{
	void			*mlx_ptr;
	t_window		window;
	t_screen		screen;
	unsigned int	stop_program:1 ;
	t_img			buffer;
}					t_fdf;


#endif
