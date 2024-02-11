/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_drawings.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:07:18 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 04:12:14 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_DRAWINGS_H
# define STRUCTURES_DRAWINGS_H

typedef struct	s_2dpoint
{
	float					x;
	float					y;
	float					hidden_z;
	int						color;
	//if 1, it means some rendering can be shortened, except if drawing lines.
	unsigned int			is_outside_canevas:1; 
}				t_2dpoint;

typedef struct s_3dpoint
{
	float  x;
	float  y;
	float  z;	
}				t_3dpoint;

typedef struct	s_line
{
	int			color;
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			invert_step_axis;
	int			delta_perror_neg;
	int			delta_perror_pos;
	int			p_error;
	int			direction_slop_y;
	int			direction_slop_x;
}				t_line;

typedef struct	s_square
{
	int			color;
	int			x;
	int			y;
	int			width;
	int			height;
}				t_square;

//matrix 4 by 4.
typedef struct	s_matrix44
{
	float		m[4][4];
}				t_matrix44;

typedef struct	s_object
{
	t_3dpoint	**original;
	float		delta_z_original; //= the span on z axis: max - min
	t_2dpoint	**projected;
	t_matrix44	transformation;
	int			nrows;
	int			ncols;
}				t_object;


#endif
