/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:43:32 by jhesso            #+#    #+#             */
/*   Updated: 2023/05/31 15:55:31 by jhesso           ###   ########.fr       */
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

/* path.c */
char	**get_path(char **envp);
char	*get_cmd(char *cmd, t_data *d);

/* init.c */
t_data	init(int ac, char **av, char **envp);

/* file.c */
void	get_input_file(t_data *d);
void	get_output_file(t_data *d);
void	get_heredoc(t_data *d);

/* error.c */
int		error_msg(char *msg, char *errno_str, int erno);
void	exit_err(int error_code, t_data *data);

/* debug.c */
void	debug_print_arr(char **arr);

/* utils.c */
void	close_fds(t_data *data);
void	free_strings(char *str, char **strs);

#endif
