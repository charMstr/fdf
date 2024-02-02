/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_set_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:34:58 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/31 23:05:15 by charmstr         ###   ########.fr       */
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

	/*
	if (key == K_W)
		fdf->player.move_forward = 0;
	if (key == K_S)
		fdf->player.move_backward = 0;
	if (key == K_A)
		fdf->player.shift_left = 0;
	if (key == K_D)
		fdf->player.shift_right = 0;
	if (key == K_CTRL_LEFT)
		fdf->player.bend_knees = 0;
		*/

	if (key == K_RIGHT)
		;//fdf->perspective.turn_right = 0;
	if (key == K_LEFT)
		;//fdf->perspective.turn_left = 0;
	if (key == K_UP)
		;//fdf->perspective.tilt_upward = 0;
	if (key == K_DOWN)
		;//fdf->perspective.tilt_downward = 0;
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
	if (key == K_ESC)
		fdf->stop_program = 1;
	/*
	if (key == K_RIGHT)
		fdf->player.turn_right = 1;
	if (key == K_LEFT)
		fdf->player.turn_left = 1;
	if (key == K_W)
		fdf->player.move_forward = 1;
	if (key == K_S)
		fdf->player.move_backward = 1;
	if (key == K_A)
		fdf->player.shift_left = 1;
	if (key == K_D)
		fdf->player.shift_right = 1;
	if (key == K_UP)
		fdf->player.tilt_upward = 1;
	if (key == K_DOWN)
		fdf->player.tilt_downward = 1;
	if (key == K_CTRL_LEFT)
		fdf->player.bend_knees = fdf->real_middle >> 2;
	if (key == K_SPACE)
		fdf->player.jump = 1;
		*/
	return (0);
}
