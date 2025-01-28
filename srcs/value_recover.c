#include "../incl/minishell.h"

/* var_exists:
 * Verifica si una variable existe en el entorno del shell.
 * - Recorre la lista de variables de entorno y compara el nombre con la variable dada.
 * 
 * Retorna 0 si la variable existe, o 1 si no se encuentra en el entorno.
 */
static int	var_exists(t_data *data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

/* search_env_var:
 * Busca una variable en el entorno y devuelve su valor.
 * - Si la variable está en el entorno, devuelve una copia de su valor.
 * - Si la variable no se encuentra, retorna NULL.
 */
static char	*search_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(data->env[i] + len);
	return (str);
}

/* recover_val:
 * Recupera el valor de una variable de entorno a partir de su nombre.
 * - Si la variable existe, obtiene su valor y lo marca en el token correspondiente.
 * - Si la variable es `$?`, retorna el código de salida del último comando ejecutado.
 * - Si la variable no existe, retorna NULL.
 */
char	*recover_val(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && var_exists(data, var) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		value = search_env_var(data, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_last_exit_code);
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
