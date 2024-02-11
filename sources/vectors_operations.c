/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:34:47 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/08 14:15:16 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures_drawings.h"
#include <math.h>

t_3dpoint vector_addition(t_3dpoint const * const left, t_3dpoint const * const right)
{
	t_3dpoint new;

	new.x = left->x + right->x;
	new.y =  left->y + right->y;
	new.z =  left->z + right->z;
	return (new);
}

t_3dpoint vector_soustraction(t_3dpoint const * const left, t_3dpoint const * const right)
{
	t_3dpoint new;

	new.x = left->x - right->x;
	new.y =  left->y - right->y;
	new.z =  left->z - right->z;
	return (new);

}

t_3dpoint vector_product_by_scalar(t_3dpoint const * const left, float scalar)
{
	t_3dpoint new;

	new.x = left->x * scalar;
	new.y = left->y * scalar;
	new.z = left->z * scalar;
	return (new);
}

float vector_length(t_3dpoint const * const vector)
{
	return sqrt(vector->x * vector->x + \
			vector->y * vector->y + vector->z * vector->z);
}

float dot_product(t_3dpoint const * const left, t_3dpoint const * const right)
{
	return(left->x * right->x + left->y * right->y + left->z * right->z);
}

/*
** orders matter+++
** returns the coordinate of a vector that is normal to the other two. and its
** magnitude is equal to the area between the two vectors.
**
** output is maximum when two vectors are orthogonal.
*/

t_3dpoint  cross_product(t_3dpoint const * const left, t_3dpoint const * const right)
{
	t_3dpoint new;

	new.x = left->y * right->z - left->z * right->y;
	new.y = left->z * right->x - left->x * right->z;
	new.z = left->x * right->y - left->y * right->x;
	return (new);
}

/*
** used to normalise a vector before we use it (its length becomes 1).
*/
void 	vector_normalize(t_3dpoint  * const vector)
{
	float length;
	float inverse_length;

	length = vector_length(vector);
	if (length != 0 && length !=1)
	{
		inverse_length = 1/length;
		vector->x *= inverse_length;
		vector->y *= inverse_length;
		vector->z *= inverse_length;
	}
}

/*
** We use in this code the column-major order convention... which means
** the vector is vertical and is on the right side of the matrix.
**
** /!\ waring non commutative.
*/

t_3dpoint vector_by_matrix_product(t_3dpoint const * const vector, t_matrix44 const * const matrix)
{
	t_3dpoint new;

	new.x = matrix->m[0][0] * vector->x + matrix->m[0][1] * vector->y \
			+ matrix->m[0][2] * vector->z + matrix->m[0][3];
	new.y = matrix->m[1][0] * vector->x + matrix->m[1][1] * vector->y \
			+ matrix->m[1][2] * vector->z + matrix->m[1][3];
	new.z = matrix->m[2][0] * vector->x + matrix->m[2][1] * vector->y \
			+ matrix->m[2][2] * vector->z + matrix->m[2][3];
	return (new);
}
