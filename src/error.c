/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:13:13 by jhesso            #+#    #+#             */
/*   Updated: 2023/05/25 12:39:33 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	error_msg()
*	prints an error message on the STDERR.
*	returns the error code
*/
int	error_msg(char *msg, char *errno_str, int erno)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (erno);
}

/*	exit_err()
*	In case of an error, cleanly exit the program, freeing all allocated memory
*	and closing all opened file descriptors
*/
void	exit_err(int error_code, t_data *data)
{
	//TODO add freeing and fd closing whenever they are added to the program
	exit(error_code);
}
