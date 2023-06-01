/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:09:31 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/01 14:58:40 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	clean_init()
*	set default values to our data structure
*/
static t_data	clean_init(void)
{
	t_data	d;

	d.envp = NULL;
	d.av = NULL;
	d.ac = -1;
	d.heredoc = 0;
	d.fd_in = -1;
	d.fd_out = -1;
	d.pipe = NULL;
	d.nbr_cmd = -1;
	d.child = -1;
	d.pids = NULL;
	d.cmd_options = NULL;
	d.cmd_path = NULL;
	return (d);
}

/*	generate_pipes
*generate a pipe for each command
*/
static void	generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_cmd - 1)
	{
		if (pipe(data->pipe + 2 * i) == -1)
			exit_err(error_msg("Couldn't create pipe", "", "", 1), data);
		i++;
	}
}

/*	init()
*	initialize a new data struct to hold pipex info
*/
t_data	init(int ac, char **av, char **envp)
{
	t_data	data;

	data = clean_init();
	data.ac = ac;
	data.av = av;
	data.envp = envp;
	if (!ft_strncmp("here_doc", av[1], 9))
		data.heredoc = 1;
	get_input_file(&data);
	get_output_file(&data);
	data.nbr_cmd = ac - 3 - data.heredoc;
	data.pids = malloc(sizeof * data.pids * data.nbr_cmd);
	if (!data.pids)
		exit_err(error_msg("PID error", "", strerror(errno), 1), &data);
	data.pipe = malloc(sizeof * data.pipe * 2 * (data.nbr_cmd - 1));
	if (!data.pipe)
		exit_err(error_msg("pipe error", "", strerror(errno), 1), &data);
	generate_pipes(&data);
	return (data);
}
