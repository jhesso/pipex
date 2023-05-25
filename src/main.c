/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:40:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/05/25 15:40:01 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	parent()
*	waits for the children process to finish and fetches the status of the last
*	child
*	return the exit status code of the last child process.
*/
static int	parent(t_data *d)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_fds(d);
	d->child--;
	exit_code = 1;
	while (d->child >= 0)
	{
		wpid = waitpid(d->pids[d->child], &status, 0);
		if (wpid == d->pids[d->nbr_cmd - 1])
		{
			if ((d->child == (d->nbr_cmd - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		d->child--;
	}
	free(d->pipe);
	free(d->pids);
	return(exit_code);
}

/*	creates a pipe and forks all child processes before calling the parent
*	to wait for them to finish their tasks.
*	returns the last child's exit code
*/
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
		d->pids[d->child] = fork();
		if (d->pids[d->child] == -1)
			exit_err(error_msg("fork: ", strerror(errno), 1), d);
		else if (d->pids[d->child] == 0)
			child(d);
		free_strs(d->cmd_path, d->cmd_options);
		d->child++;
	}
	exit_code = parent(d);
	if (d->heredoc == 1)
		unlink(".heredoc.tmp");
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
