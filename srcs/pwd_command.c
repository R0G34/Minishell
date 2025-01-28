#include "../incl/minishell.h"

/* pwd_builtin:
 * Implementa el comando `pwd` del shell, que muestra el directorio de trabajo actual.
 * - Si `data->working_dir` está definido, lo imprime directamente.
 * - Si `getcwd` puede obtener el directorio actual, lo imprime.
 * - Si `getcwd` falla, muestra un mensaje de error.
 * Devuelve 0 en caso de éxito o 1 si ocurre un error.
 */
int	pwd_builtin(t_data *data, char **args)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void)args;
	if (data->working_dir)
	{
		ft_putendl_fd(data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
