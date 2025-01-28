#include "../incl/minishell.h"

/* update_wds:
 * Actualiza las variables de entorno PWD y OLDPWD después de cambiar el directorio.
 * También guarda copias internas de las rutas para usarlas si las variables
 * de entorno se eliminan.
 */
static void	update_wds(t_data *data, char *wd)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data->env, "PWD"));
	set_env_var(data, "PWD", wd);
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free_ptr(data->working_dir);
		data->working_dir = ft_strdup(wd);
	}
	free_ptr(wd);
}

/* chdir_errno_mod:
 * Maneja un error específico de `chdir` relacionado con la eliminación de directorios
 * padre en algunos sistemas. Si ocurre un error "Stale file handle" (ESTALE), 
 * lo convierte en un error "No such file or directory" (ENOENT).
 */
static	bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd("cd", path, strerror(errno), errno);
	return (false);
}

/* change_dir:
 * Cambia el directorio de trabajo actual al especificado en `path` y actualiza
 * la variable OLDPWD en el entorno. Si hay un error, se maneja apropiadamente.
 * Devuelve true en caso de éxito y false en caso de fallo.
 */
static bool	change_dir(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		ret = ft_strjoin(data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(data, ret);
	return (true);
}

/* cd_builtin:
 * Implementa el comando `cd` del shell, que cambia el directorio de trabajo actual.
 * - Si no se especifica ningún argumento, cambia al directorio de inicio (HOME).
 * - Si se pasa el argumento "-", cambia al directorio anterior (OLDPWD).
 * - Si se pasan múltiples argumentos, muestra un error.
 * Devuelve 0 en caso de éxito y 1 en caso de fallo.
 */
int	cd_builtin(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_value(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}
