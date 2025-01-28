#include "../incl/minishell.h"

/* unset_builtin:
 * Implementa el comando `unset` del shell, que elimina variables de entorno.
 * - Si una clave no es válida o contiene '=', se muestra un error y se continúa con las demás.
 * - Si la variable existe en el entorno, se elimina.
 * - Si no existe, no hace nada.
 * Devuelve 0 si todas las variables fueron eliminadas correctamente, o 1 si hubo errores.
 */
int	unset_builtin(t_data *data, char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = get_env_var_index(data->env, args[i]);
			if (idx != -1)
				remove_env_var(data, idx);
		}
		i++;
	}
	return (ret);
}