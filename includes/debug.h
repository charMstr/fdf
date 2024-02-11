/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:30:52 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 03:29:11 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "../includes/structures_fdf.h"
# include "../includes/structures_drawings.h"
# include <stdio.h>

void debug_3dpoint(t_3dpoint point);
void debug_array_of_3dpoint(t_3dpoint *array_of_points, int length_array);
void debug_object(t_object *object);
void debug_2dpoint(const t_2dpoint * const point);

void debug_matrix44(const t_matrix44 * const matrix);

void 	debug_shadow_pixel_array(t_window* window);

#endif
