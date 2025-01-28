#include "../incl/minishell.h"

/* find_valid_cmd_path:
 * Busca en la lista de rutas disponibles en `PATH` un binario ejecutable para el comando dado.
 * - Verifica si cada ruta tiene acceso de ejecución al binario correspondiente.
 * - Retorna la ruta válida al binario si se encuentra, o NULL si no hay ninguna válida.
 */
static char	*find_valid_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			errmsg_cmd("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_ptr(cmd_path);
		i++;
	}
	return (NULL);
}

/* get_paths_from_env:
 * Obtiene la lista de rutas definidas en la variable de entorno `PATH`.
 * - Si `PATH` no está definida, retorna NULL.
 * - Si `PATH` está definida, la divide en un array de rutas separadas por `:`.
 */
static char	**get_paths_from_env(t_data *data)
{
	char	**env_paths;

	if (get_env_var_index(data->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(get_env_var_value(data->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

/* get_cmd_path:
 * Resuelve la ruta completa de un comando buscando su binario en `PATH`.
 * - Si el comando ya contiene una `/`, se asume que es una ruta absoluta y se retorna tal cual.
 * - Si el comando no tiene `/`, se busca en los directorios especificados en `PATH`.
 * - Retorna la ruta del binario si se encuentra, o NULL si no hay una ruta válida.
 */
char	*get_cmd_path(t_data *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_paths_from_env(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_str_tab(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	if (!cmd_path)
	{
		free_ptr(cmd);
		free_str_tab(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
