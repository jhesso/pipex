/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:22:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/01 13:22:42 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	close_pipe_fds()
*	close all pipes' read and write fds
*/
static void	close_pipe_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->nbr_cmd - 1) * 2)
	{
		close(data->pipe[i]);
		i++;
	}
}

/*	close_fds()
*	close any open file descriptors in case of error
*/
void	close_fds(t_data *data)
{
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	close_pipe_fds(data);
}

/*	free_strings()
*	frees a string and/or array of strings if they are not already NULL
*/
void	free_strings(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}
