/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:36:48 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/01 15:10:36 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

# include "../libft/includes/libft.h"

typedef struct s_data
{
	char	**envp;
	char	**av;
	int		ac;
	int		heredoc;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	int		nbr_cmd;
	int		child;
	int		*pids;
	char	**cmd_options;
	char	*cmd_path;
}			t_data;

int		error_msg(char *msg, char *msg2, char *errno_str, int erno);
t_data	init(int ac, char **av, char **envp);
void	free_strings(char *str, char **strs);
void	close_fds(t_data *data);
void	get_heredoc(t_data *d);
void	exit_err(int error_code, t_data *data);
void	get_input_file(t_data *d);
void	get_output_file(t_data *d);
char	**get_path(char **envp);
char	*get_cmd(char *cmd, t_data *d);

/* debug */
void	debug_print_data(t_data data);

#endif
