/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3dpoints.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:50:03 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/03 00:29:59 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures_drawings.h"
#include "../libft/libft.h"
#include <stdio.h>
#include "../includes/debug.h"

t_3dpoint create_3dpoint(int x, int y, int z)
{
	t_3dpoint point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}
