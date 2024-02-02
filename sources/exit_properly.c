/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:26:53 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 23:06:26 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_opengl/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

/*
** function called when need to exit the program
** free anything that need to be in the fdf structure.
*/

int	exit_properly(t_fdf *fdf, int success)
{
	//free functions here

	if (fdf->window.win_ptr)
		free(fdf->window.win_ptr);
	free_mlx_ptr(fdf->mlx_ptr);
	if (success)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
