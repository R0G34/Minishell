#include "../incl/minishell.h"

/* get_key_value_pair:
 * Separa un argumento en un par clave-valor para definir una variable de entorno.
 * Retorna un array de dos cadenas: la clave y el valor de la variable de entorno.
 * En caso de error, devuelve NULL.
 */
static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

/* export_builtin:
 * Implementa el comando `export` del shell, que agrega o modifica variables de entorno.
 * - Si no se proporcionan argumentos, muestra todas las variables de entorno.
 * - Si se proporcionan claves válidas, las agrega o actualiza en el entorno.
 * - Si una clave es inválida, muestra un mensaje de error y continúa con las siguientes.
 * Devuelve 0 si todas las variables fueron agregadas correctamente, o 1 si hubo errores.
 */
int	export_builtin(t_data *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			free_str_tab(tmp);
		}
		i++;
	}
	return (ret);
}
