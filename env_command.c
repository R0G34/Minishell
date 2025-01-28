#include "../incl/minishell.h"

/* env_builtin:
 * Implementa el comando `env` del shell, que imprime las variables de entorno
 * actuales. Si se pasa algún argumento al comando, genera un error porque
 * `env` no acepta argumentos.
 * 
 * Devuelve 0 si se imprime correctamente, o 1 si ocurre un error.
 */
int	env_builtin(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
