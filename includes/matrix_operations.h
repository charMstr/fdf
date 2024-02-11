/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:32:00 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/09 22:34:12 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_OPERATIONS_H
# define MATRIX_OPERATIONS_H

# include "../includes/structures_drawings.h"

t_matrix44	matrix_product(const t_matrix44 *const target, \
		t_matrix44 *const apply);
t_matrix44	uniform_scale_transformation(float x);
t_matrix44	scale_transformation(float x,float y, float z);
void		bzero_matrix44(t_matrix44 const *matrix);
void		set_matrix_to_identity(t_matrix44 *matrix44);
t_matrix44	translation_transformation(float x,float y, float z);
t_matrix44	rotation_z_tranformation(float theta);
t_matrix44	rotation_x_tranformation(float theta);
t_matrix44	rotation_y_tranformation(float theta);

t_3dpoint	vector_product_by_scalar(t_3dpoint const * const left, \
		float scalar);
t_3dpoint	vector_soustraction(t_3dpoint const * const left, \
		t_3dpoint const * const right);
t_3dpoint	vector_addition(t_3dpoint const * const left, \
		t_3dpoint const * const right);
void 		vector_normalize(t_3dpoint  * const vector);
float		vector_length(t_3dpoint const * const vector);
float		dot_product(t_3dpoint const * const left, \
		t_3dpoint const * const right);
t_3dpoint 	cross_product(t_3dpoint const * const left, \
		t_3dpoint const * const right);
t_3dpoint	vector_by_matrix_product(t_3dpoint const * const vector, \
		t_matrix44 const * const matrix);

#endif
