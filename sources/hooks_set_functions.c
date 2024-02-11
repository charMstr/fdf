/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_set_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:34:58 by charmstr          #+#    #+#             */
/*   Updated: 2024/02/10 22:49:16 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_opengl/mlx.h"
#include "../includes/fdf.h"

/*
** this file will be setting up all the hook function to the milibix window
** pointer through the use of this function:
**
** void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, \
**			int (*funct_ptr)(), void *param)
*/

/*
** note:	this function is the root to set function pointers to the mlx.
*/

void	set_my_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->window.win_ptr, KEY_PRESSED, 1L << 0, deal_key_pressed, fdf);
	mlx_hook(fdf->window.win_ptr, KEY_RELEASED, 1L << 1, deal_key_released, fdf);
	mlx_hook(fdf->window.win_ptr, CLOSE_WINDOW, 1L << 17, close_window_hook, fdf);
}

/*
** note:	this function is in charge of closing the program properly in the
**			case the user clicks on the red cross of the window.
**
** note:	we simply set a boolean to zero, which we will evaluate into the
**			Main loop of the fdf, so that we can exit at a time when the
**			memory is under control (freed properly).
*/

int		close_window_hook(t_fdf *fdf)
{
	fdf->stop_program = 1;
	return (0);
}

/*
** note:	this function will deal with the key being released.
*/

int		deal_key_released(int key, t_fdf *fdf)
{
	fdf = (t_fdf *)fdf;

	//TO TAKE CONTROL OF THE CAMERA
	if (key == K_SPACE)
		fdf->world.motion.apply_to_camera = 0;

	//YAW
	if (key == K_L)
		fdf->world.motion.yaw_right = 0;
	if (key == K_J)
		fdf->world.motion.yaw_left = 0;

	//PITCH
	if (key == K_I)
		fdf->world.motion.pitch_up = 0;
	if (key == K_K)
		fdf->world.motion.pitch_down = 0;

	//ROLL
	if (key == K_U)
		fdf->world.motion.roll_left = 0;
	if (key == K_O)
		fdf->world.motion.roll_right = 0;


	//SHIFT MOTION = TRANSLATION
	if (key == K_W)
		fdf->world.motion.shift_up = 0;
	if (key == K_S)
		fdf->world.motion.shift_down = 0;
	if (key == K_A)
		fdf->world.motion.shift_left = 0;
	if (key == K_D)
		fdf->world.motion.shift_right = 0;
	if (key == K_E)
		fdf->world.motion.shift_forward = 0;
	if (key == K_Q)
		fdf->world.motion.shift_backward = 0;

	//reset WORLD
	if (key == K_ENTER)
		fdf->world.motion.reset_world = 0;

	//zoom
	/*
		fdf->world.motion.zoom_in = 0;
		fdf->world.motion.zoom_out = 0;
		*/

	return (0);
}

/*
** note:	this function will deal with the key being pressed.
**
** note:	when hitting the ESC key, the behavior is the exact same as it is
**			for the close_window_hook().
*/

int		deal_key_pressed(int key, t_fdf *fdf)
{
	//STOP PROGRAM
	if (key == K_ESC)
		fdf->stop_program = 1;

	//YAW
	if (key == K_L)
		fdf->world.motion.yaw_right = 1;
	if (key == K_J)
		fdf->world.motion.yaw_left = 1;

	//PITCH
	if (key == K_I)
		fdf->world.motion.pitch_up = 1;
	if (key == K_K)
		fdf->world.motion.pitch_down = 1;

	//ROLL
	if (key == K_U)
		fdf->world.motion.roll_left = 1;
	if (key == K_O)
		fdf->world.motion.roll_right = 1;

	//SHIFT MOTION = TRANSLATION
	if (key == K_A)
		fdf->world.motion.shift_left = 1;
	if (key == K_D)
		fdf->world.motion.shift_right = 1;
	if (key == K_W)
		fdf->world.motion.shift_up = 1;
	if (key == K_S)
		fdf->world.motion.shift_down = 1;
	if (key == K_E)
		fdf->world.motion.shift_forward = 1;
	if (key == K_Q)
		fdf->world.motion.shift_backward = 1;

	//TAKE CONTROL OF THE CAMERA
	if (key == K_SPACE)
		fdf->world.motion.apply_to_camera = 1;

	//RESET world
	if (key == K_ENTER)
		fdf->world.motion.reset_world = 1;

	//zoom

	return (0);
}
