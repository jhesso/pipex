/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:47:38 by jhesso            #+#    #+#             */
/*   Updated: 2023/03/24 19:15:09 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_env_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			break ;
		}
		i++;
	}
	return (path);
}

static char	**parse_path(char **env_path)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env_path[i])
	{
		tmp = env_path[i];
		env_path[i] = ft_strjoin(env_path[i], "/");
		free (tmp);
		i++;
	}
	return (env_path);
}

/*	get_path()
*	get the path variable from envp and parse it into a usable form
*	returns the env_path char** or NULL if there was an error
*/
char	**get_path(char **envp)
{
	char	**env_path;
	char	*path_str;

	path_str = get_env_path(envp);
	if (!path_str)
		return (NULL);
	env_path = ft_split(path_str, ':');
	free(path_str);
	if (!env_path)
		return (NULL);
	env_path = parse_path(env_path);
	if (!env_path)
		return (NULL);
	return (env_path);
}
