/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:23:47 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/07 17:49:09 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	get_input_file()
*	set the input fd for pipex
*	if heredoc is specified, temp file will be created
*	otherwise the specified input file will be opened
*/
void	get_input_file(t_data *d)
{
	if (d->heredoc == 1)
	{
		get_heredoc(d);
		d->fd_in = open(".heredoc.tmp", O_RDONLY, 0644);
		if (d->fd_in == -1)
			exit_err(error_msg("here_doc: ", "", strerror(errno), 1), d);
	}
	else
	{
		d->fd_in = open(d->av[1], O_RDONLY, 0644);
		if (d->fd_in == -1)
			exit_err(error_msg(d->av[1], ": ", strerror(errno), 1), d);
	}
}

/*	get_output_file()
*	Open/create the output file. If here_doc is specified
*	the output file will be appended, otherwise, it will be overwritten
*/
void	get_output_file(t_data *d)
{
	if (d->heredoc == 1)
		d->fd_out = open(d->av[d->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		d->fd_out = open(d->av[d->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fd_out == -1)
		exit_err(error_msg(d->av[d->ac -1], ": ", strerror(errno), 1), d);
}

/*	get_heredoc()
*	read from stdin and store read lines in a temp file
*	until specified limiter is found.
*	then, set pipex's input file as that temp file
*/
void	get_heredoc(t_data *d)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	tmp_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	stdin_fd = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		exit_err(error_msg("here_doc: ", "", strerror(errno), 1), d);
	line = "";
	while (1)
	{
		ft_putstr_fd("here_doc > ", 1);
		line = get_next_line(stdin_fd);
		if (line == NULL)
			break ;
		if (ft_strlen(d->av[2]) + 1 == ft_strlen(line) && \
			!ft_strncmp(line, d->av[2], ft_strlen(d->av[2] + 1)))
			close(stdin_fd);
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
}
