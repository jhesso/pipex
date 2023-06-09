/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:44:14 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/01 13:36:46 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	error_msg()
*	prints an error message on the STDERR.
*	returns the error code
*/
int	error_msg(char *msg, char *msg2, char *errno_str, int erno)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	ft_putstr_fd(errno_str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (erno);
}

/*	exit_err()
*	In case of an error, cleanly exit the program, freeing all allocated memory
*	and closing all opened file descriptors
*/
void	exit_err(int error_code, t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->pipe != NULL)
			free(data->pipe);
		if (data->pids != NULL)
			free(data->pids);
		if (data->cmd_options != NULL || data->cmd_path != NULL)
			free_strings(data->cmd_path, data->cmd_options);
	}
	if (data->heredoc == 1)
		unlink(".heredoc.tmp");
	exit(error_code);
}
