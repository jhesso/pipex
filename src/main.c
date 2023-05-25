/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:40:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/05/25 14:29:31 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	pipex(t_data *d)
{
	int		exit_code;

	if (pipe(d->pipe) == -1)
		exit_err(error_msg("pipe: ", strerror(errno), 1), d);
	d->child = 0;
	while (d->child < d->nbr_cmd)
	{
		d->cmd_options = ft_split(d->av[d->child + 2 + d->heredoc], ' ');
		if (!d->cmd_options)
			exit_err(error_msg("unexpected error", "", 1), d);
		d->cmd_path = get_cmd(d->cmd_options[0], d);
	}
	return (exit_code);
}

/* main()
*	checks that the program is ran correctly and that we have all the
*	information needed.
*/
int	main(int ac, char **av, char** envp)
{
	int		exit_code;
	t_data	data;

	if (ac < 5)
	{
		if (ac >= 2 && !ft_strcmp("here_doc", av[1]))
			return (error_msg("Usage: ./pipex here_doc LIMITER cmd1 cmd2\
			... cmdn file2.\n", "", 1));
		return (error_msg("Usage: ./pipex file1 cmd1 cmd2 file2.\n", "", 1));
	}
	else if (ac < 6 && !ft_strcmp ("here_doc", av[1]))
		return (error_msg("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn\
		file2.\n", "", 1));
	if (!envp || envp[0][0] == '\0')
		exit_err(error_msg("Unexpected error.\n", "", 2), NULL);
	data = init(ac, av, envp);
	exit_code = pipex(&data);
	return (exit_code);
}
