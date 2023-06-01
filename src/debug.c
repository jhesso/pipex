/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:40:27 by jhesso            #+#    #+#             */
/*   Updated: 2023/06/01 15:46:26 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	debug_print_data(t_data data)
{
	ft_printf("envp:\n");
	print_string_arr(data.envp);
	ft_printf("av:\n");
	print_string_arr(data.av);
	ft_printf("ac: %d\n", data.ac);
	ft_printf("heredoc: %d, fd_in: %d, fd_out: %d\n", data.heredoc, data.fd_in,
		data.fd_out);
	ft_printf("nbr_cmd: %d, child: %d\n", data.nbr_cmd, data.child);
	ft_printf("cmd_options:\n");
	print_string_arr(data.cmd_options);
	ft_printf("cmd_path: %s", data.cmd_path);
}
