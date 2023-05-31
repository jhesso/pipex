/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:47:38 by jhesso            #+#    #+#             */
/*   Updated: 2023/05/31 15:56:25 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*	get_env_path()
*	parse the envp variable to find the "PATH=" line
*	and makes a copy of it
*	returns a pointer to the copy, or NULL if there is none or memory
*	allocation failed.
*/
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

/*	parse_path()
*	append a '/' character at the end of each path
*/
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
*	returns the env_path char**
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

/*	get_cmd_path()
*	check each env path to see if the command binary is present.
*	return the valid command path, or NULL if none was found
*/
static char	*get_cmd_path(char *cmd, char **env_paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (env_paths[i])
	{
		cmd_path = ft_strjoin(env_paths[i], cmd);
		if (!cmd_path)
		{
			free_strings(NULL, env_paths);
			exit_err(error_msg("unexpected error", "", 1), NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_strings(cmd_path, NULL);
		i++;
	}
	return (NULL);
}

/*	get_cmd()
*	get the given command path from the environment variables.
*	return the command path, or NULL if no valid command path was found
*/
char	*get_cmd(char *cmd, t_data *d)
{
	char	**env_paths;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	env_paths = get_path(d->envp);
	if (!env_paths)
		return (NULL);
	cmd_path = get_cmd_path(cmd, env_paths);
	if (!cmd_path)
		error_msg("command not found: ", d->av[d->child + 2], 1);
	free_strings(NULL, env_paths);
	return (cmd_path);
}
