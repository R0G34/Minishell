#include "../incl/minishell.h"

/* env_var_count:
 * Cuenta cuántas variables de entorno existen actualmente en la lista de entorno.
 * Retorna el número total de variables de entorno.
 */
int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/* get_env_var_index:
 * Busca una variable específica en la lista de variables de entorno.
 * 
 * Retorna el índice de la variable dentro del entorno si se encuentra.
 * La búsqueda requiere el nombre exacto de la variable, sin admitir coincidencias parciales.
 * Retorna -1 si la variable no se encuentra en el entorno.
 */
int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (i);
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

/* get_env_var_value:
 * Busca una variable en la lista de entorno y devuelve su valor.
 * 
 * Retorna un puntero al valor de la variable si se encuentra.
 * La búsqueda requiere el nombre exacto de la variable.
 * Retorna NULL si la variable no existe en el entorno.
 */
char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}

/* is_valid_env_var_key:
 * Comprueba si una clave es válida para ser usada como nombre de variable de entorno.
 * Una clave válida debe comenzar con una letra o un guion bajo (_) y solo puede contener
 * caracteres alfanuméricos o guion bajo.
 * 
 * Retorna true si la clave es válida, false si contiene caracteres no permitidos.
 */
bool	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
