/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_transformation_matrix.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:24:16 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/11 04:09:44 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this file takes care of updating the transformation matrix according to
** the keys pressed/released
*/

#include "../includes/fdf.h"
#include "../includes/matrix_operations.h"

#define STEP_ROTATION 0.06
#define STEP_ROTATION_CAMERA 0.04

void	update_camera_transformation(t_motion * const motion, t_camera * const camera, t_motion_control *motion_ctrl)
{
	t_matrix44 applied_to;

	//SHIFT SECTION
	if (motion->shift_right)
	{
		applied_to = translation_transformation(-motion_ctrl->step_shift, 0, 0);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	else if (motion->shift_left)
	{
		applied_to = translation_transformation(motion_ctrl->step_shift, 0, 0);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	if (motion->shift_up)
	{
		applied_to = translation_transformation(0, motion_ctrl->step_shift, 0);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	else if (motion->shift_down)
	{
		applied_to = translation_transformation(0, -motion_ctrl->step_shift, 0);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	if (motion->shift_forward)
	{
		applied_to = translation_transformation(0, 0, motion_ctrl->step_shift);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	else if (motion->shift_backward)
	{
		applied_to = translation_transformation(0, 0, -motion_ctrl->step_shift);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}


	//YAW SECTION
	if (motion->yaw_right)
	{
		applied_to = rotation_y_tranformation(STEP_ROTATION_CAMERA);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	else if (motion->yaw_left)
	{
		applied_to = rotation_y_tranformation(- STEP_ROTATION_CAMERA);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}


	//PITCH SECTION
	if (motion->pitch_up)
	{
		applied_to = rotation_x_tranformation(STEP_ROTATION_CAMERA);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	else if (motion->pitch_down)
	{
		applied_to = rotation_x_tranformation(- STEP_ROTATION_CAMERA);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}

	//ROLL SECTION
	if (motion->roll_right)
	{
		applied_to = rotation_z_tranformation(STEP_ROTATION_CAMERA);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
	else if (motion->roll_left)
	{
		applied_to = rotation_z_tranformation(- STEP_ROTATION_CAMERA);
		camera->view_direction = matrix_product(&applied_to, &camera->view_direction);
	}
}

void	update_object_transformation(t_motion * const motion, t_object * const object, t_motion_control *motion_ctrl)
{
	t_matrix44 apply;

	//YAW SECTION
	if (motion->yaw_right)
	{
		apply = rotation_y_tranformation(STEP_ROTATION);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	else if (motion->yaw_left)
	{
		apply = rotation_y_tranformation(- STEP_ROTATION);
		object->transformation = matrix_product(&object->transformation, &apply);
	}

	//PITCH SECTION
	if (motion->pitch_up)
	{
		apply = rotation_x_tranformation(STEP_ROTATION);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	else if (motion->pitch_down)
	{
		apply = rotation_x_tranformation(- STEP_ROTATION);
		object->transformation = matrix_product(&object->transformation, &apply);
	}


	//ROLL SECTION
	if (motion->roll_right)
	{
		apply = rotation_z_tranformation(STEP_ROTATION);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	else if (motion->roll_left)
	{
		apply = rotation_z_tranformation(- STEP_ROTATION);
		object->transformation = matrix_product(&object->transformation, &apply);
	}

	//ZOOM SECTION
	if (motion->zoom_in)
	{
		apply = uniform_scale_transformation(1 + motion_ctrl->step_zoom);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	else if (motion->zoom_out)
	{
		apply = uniform_scale_transformation(1 - motion_ctrl->step_zoom);
		object->transformation = matrix_product(&object->transformation, &apply);
	}


	//SHIFT SECTION
	if (motion->shift_right)
	{
		apply = translation_transformation(motion_ctrl->step_shift, 0, 0);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	else if (motion->shift_left)
	{
		apply = translation_transformation(-motion_ctrl->step_shift, 0, 0);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	if (motion->shift_up)
	{
		apply = translation_transformation(0, -motion_ctrl->step_shift, 0);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	else if (motion->shift_down)
	{
		apply = translation_transformation(0, motion_ctrl->step_shift, 0);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	if (motion->shift_forward)
	{
		apply = translation_transformation(0, 0, motion_ctrl->step_shift);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
	else if (motion->shift_backward)
	{
		apply = translation_transformation(0, 0, -motion_ctrl->step_shift);
		object->transformation = matrix_product(&object->transformation, &apply);
	}
}

void update_transformation_matrix(t_motion *const motion, t_world *const world)
{
	if (motion->reset_world)
	{
		init_world_before_render(world);
		return;
	}
	if (motion->apply_to_camera)
		update_camera_transformation(motion, &world->camera, &world->motion_ctrl);
	else
		update_object_transformation(motion, &world->object, &world->motion_ctrl);
}
