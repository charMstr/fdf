/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:30:52 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/03 01:01:59 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "../includes/structures_fdf.h"
# include "../includes/structures_drawings.h"
# include <stdio.h>

void debug_3dpoint(t_3dpoint point);
void debug_array_of_3dpoint(t_3dpoint *array_of_points, int length_array);
void debug_raster_data(t_raster_data *raster_data);

#endif
