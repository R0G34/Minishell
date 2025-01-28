#include "../incl/minishell.h"

/* realloc_env_vars:
 * Realoca la memoria para la lista de variables de entorno, aumentando su tamaño.
 * Copia las variables actuales a la nueva lista y libera la memoria de la anterior.
 * 
 * Retorna un puntero a la nueva lista de variables de entorno, o NULL en caso de error.
 */
static char	**realloc_env_vars(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

/* set_env_var:
 * Agrega o actualiza una variable de entorno con la clave y valor proporcionados.
 * - Si la clave ya existe, su valor será sobrescrito.
 * - Si la clave no existe, se crea una nueva entrada en la lista de entorno.
 * 
 * Retorna true si la operación fue exitosa, false en caso de error.
 */
bool	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(data->env);
		data->env = realloc_env_vars(data, idx + 1);
		if (!data->env)
			return (false);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

/* remove_env_var:
 * Elimina una variable de entorno dada su posición en la lista.
 * - Si el índice es inválido, la función no hace nada.
 * - La variable eliminada es removida de la lista y la memoria se reorganiza.
 * 
 * Retorna true si la variable fue eliminada correctamente, false en caso de error.
 */
bool	remove_env_var(t_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env))
		return (false);
	free_ptr(data->env[idx]);
	i = idx;
	count = idx;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = realloc_env_vars(data, count);
	if (!data->env)
		return (false);
	return (true);
}
