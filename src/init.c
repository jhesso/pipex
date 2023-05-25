/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:03:23 by jhesso            #+#    #+#             */
/*   Updated: 2023/05/25 13:48:43 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/*	init_data()
*	initialize the data struct with default values
*/
static t_data	init_data(void)
{
	t_data	data;

	data.envp = NULL;
	data.av = NULL;
	data.ac = -1;
	data.heredoc = -1;
	data.fd_in = -1;
	data.fd_out = -1;
	data.pipe = NULL;
	data.nbr_cmd = -1;
	data.child = -1;
	data.pids = NULL;
	data.cmd_options = NULL;
	data.cmd_path = NULL;
	return (data);
}

/*	gen_pipes()
*	generate a pipe for each command.
*/
static void	gen_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_cmd - 1)
	{
		if (pipe(data->pipe + 2 * i) == -1)
			exit_err(error_msg("Could not create pipe", "", 1), data);
		i++;
	}
}

/*	init()
*	initialize a new data struct to hold pipex info.
*/
t_data	init(int ac, char **av, char **envp)
{
	t_data	data;

	data = init_data();
	data.envp = envp;
	data.ac = ac;
	data.av = av;
	if (!ft_strncmp("here_doc", av[1], 9))
		data.heredoc = 1;
	get_input_file(&data);
	get_output_file(&data);
	data.nbr_cmd = ac - 3 - data.heredoc;
	data.pids = malloc(sizeof * data.pids * data.nbr_cmd);
	if (!data.pids)
		exit_err(error_msg("PID error", strerror(errno), 1), &data);
	gen_pipes(&data);
	return (data);
}
