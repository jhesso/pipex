/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:43:32 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/24 19:14:34 by jhesso           ###   ########.fr       */
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

# include "../libft/includes/libft.h"

/* path.c */
char	**get_path(char **envp);

/* error.c */
int		error_msg(char *msg, int err_num);
void	exit_err(int error_code);

/* debug.c */
void	debug_print_arr(char **arr);

#endif
