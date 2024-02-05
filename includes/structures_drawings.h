/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_drawings.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:07:18 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/02 21:28:22 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_DRAWINGS_H
# define STRUCTURES_DRAWINGS_H

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct s_3dpoint
{
	int x;
	int y;
	int z;	
}				t_3dpoint;

typedef struct	s_line
{
	int			color;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
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

#endif
