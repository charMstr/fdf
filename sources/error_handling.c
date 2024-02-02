/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 08:59:11 by charmstr          #+#    #+#             */
/*   Updated: 2024/01/29 20:57:49 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/fdf.h"
#include "../includes/error_handling.h"

/*
** this file will contain functions that will handle the error and display
** messages in the correct format.  "Error\n" + "specific message"
*/

/*
** note:	this function will display error message on the standard err output
*/

int	print_err(char *str)
{
	ft_putstr_fd(RED_ERROR, 2);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("--> ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(END_RED_ERROR, 2);
	return (0);
}
