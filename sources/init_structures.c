/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:26:57 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/10 00:38:12 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_opengl/mlx.h"
#include "../includes/fdf.h"
#include "../libft/libft.h"


/*
** note:	we do not do for example: game->target.img.data_str = NULL;
**			because the mlx_function will inititate this pointers. and it will
**			destroy them as well...
*/

void	init_struct_fdf(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(*fdf));
}
