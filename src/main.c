/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:40:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/24 19:16:31 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	pipex(int ac, char **av, char **envp)
{
	int		exit_code;
	char	**path;

	if (ac != 1)
		debug_print_arr(av);
	exit_code = 0; //? leaving this here for now, I think the goal is to remove this in the end but I dont have anything that would change the exit_code yet.
	path = get_path(envp);
	debug_print_arr(path);
	return (exit_code);
}

/* main()
*	checks that the program is ran correctly and that we have all the
*	information needed.
*/
int	main(int ac, char **av, char** envp)
{
	int	exit_code;
	if (ac < 5)
	{
		if (ac >= 2 && !ft_strcmp("here_doc", av[1]))
			return (error_msg("Usage: ./pipex here_doc LIMITER cmd1 cmd2\
			... cmdn file2.\n", 1));
		return (error_msg("Usage: ./pipex file1 cmd1 cmd2 file2.\n", 1));
	}
	else if (ac < 6 && !ft_strcmp ("here_doc", av[1]))
		return (error_msg("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn\
		file2.\n", 1));
	if (!envp || envp[0][0] == '\0')
		exit_err(error_msg("Unexpected error.\n", 2));
	exit_code = pipex(ac, av, envp);
	return (exit_code);
}
