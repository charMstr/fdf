/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:08:30 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/10 04:33:19 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures_drawings.h"
#include "../libft/libft.h"
#include <math.h>

//set matrix to zero.
void bzero_matrix44(t_matrix44 const *matrix)
{
	ft_bzero((void*)matrix, sizeof(float) * 16);
}

void set_matrix_to_identity(t_matrix44 *matrix44)
{
	bzero_matrix44(matrix44);
	matrix44->m[0][0] = 1;
	matrix44->m[1][1] = 1;
	matrix44->m[2][2] = 1;
	matrix44->m[3][3] = 1;
}

//multiplcation by other matrix, it has to be a 4 by 4 matrix so no check.
t_matrix44  matrix_product(const t_matrix44 *const target, t_matrix44 *const apply)
{
	t_matrix44 output;
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			output.m[row][column] = \
				target->m[row][0] * apply->m[0][column] + \
				target->m[row][1] * apply->m[1][column] + \
				target->m[row][2] * apply->m[2][column] + \
				target->m[row][3] * apply->m[3][column];
		}
	}
	return (output);
}


/*
** scaling matrix
*/
t_matrix44 scale_transformation(float x, float y, float z)
{
	t_matrix44 new;

	set_matrix_to_identity(&new);
	new.m[0][0] = x;
	new.m[1][1] = y;
	new.m[2][2] = z;
	return (new);
}

//same as scale_transformation, but it applies the same scalar in all axis.
t_matrix44 uniform_scale_transformation(const float x)
{
	return (scale_transformation(x, x, x));
}

//translatation matrix
t_matrix44 translation_transformation(float x, float y, float z)
{
	t_matrix44 new;

	set_matrix_to_identity(&new);
	new.m[0][3] = x;
	new.m[1][3] = y;
	new.m[2][3] = z;
	return (new);
}

//rotation around z axis
t_matrix44 rotation_z_tranformation(float theta)
{
	t_matrix44 matrix;
	set_matrix_to_identity(&matrix);

	matrix.m[0][0] = cos(theta);
	matrix.m[0][1] = - sin(theta);
	matrix.m[1][0] = sin(theta);
	matrix.m[1][1] = cos(theta);
	return (matrix);
}

//rotation around x axis
t_matrix44 rotation_x_tranformation(float theta)
{
	t_matrix44 matrix;
	set_matrix_to_identity(&matrix);

	matrix.m[1][1] = cos(theta);
	matrix.m[1][2] = - sin(theta);
	matrix.m[2][1] = sin(theta);
	matrix.m[2][2] = cos(theta);
	return (matrix);
}

//rotation around x axis
t_matrix44 rotation_y_tranformation(float theta)
{
	t_matrix44 matrix;
	set_matrix_to_identity(&matrix);

	matrix.m[0][0] = cos(theta);
	matrix.m[0][2] = sin(theta);
	matrix.m[2][0] = - sin(theta);
	matrix.m[2][2] = cos(theta);
	return (matrix);
}
