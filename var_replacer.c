#include "../incl/minishell.h"

/* erase_var:
 * Elimina una variable de entorno dentro de una cadena, ajustando el contenido restante.
 * - Encuentra la variable usando `$` como referencia y la elimina de la cadena.
 * - Si la variable está al final de la cadena, simplemente la corta.
 * 
 * Retorna 0 si se eliminó correctamente, 1 en caso de error.
 */
static int	erase_var(t_token **token_node, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_length(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + var_length(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_str;
	return (0);
}

/* erase_and_replace:
 * Reemplaza una variable de entorno por su valor dentro de una cadena.
 * - Elimina la variable e inserta su valor en la misma posición.
 * - Si la variable pertenece a un token, actualiza su contenido.
 * 
 * Retorna la nueva cadena con la variable reemplazada.
 */

static char	*erase_and_replace(t_token **token_node, char *str,
			char *var_value, int index)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - var_length(str + index)
			+ ft_strlen(var_value));
	newstr = get_new_token_string(str, var_value, newstr_size, index);
	if (token_node && *token_node)
	{
		free_ptr((*token_node)->str);
		(*token_node)->str = newstr;
	}
	return (newstr);
}

/* replace_var:
 * Busca y reemplaza una variable de entorno en un token con su valor.
 * - Si la variable no tiene valor, simplemente la elimina de la cadena.
 * - Si la variable tiene un valor, la reemplaza en su posición.
 * 
 * Retorna 0 si la operación fue exitosa, 1 en caso de error.
 */
int	replace_var(t_token **token_node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (erase_var(token_node, (*token_node)->str, index) == 1)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	else
	{
		if (erase_and_replace(token_node, (*token_node)->str, \
		var_value, index) == NULL)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	free_ptr(var_value);
	return (0);
}

/* replace_str_heredoc:
 * Variante de `replace_variable` para heredoc. Reemplaza una variable de entorno
 * dentro de una cadena heredoc.
 * - Si la variable no tiene valor, vacía la cadena.
 * - Si la variable tiene un valor, la reemplaza en su posición.
 * 
 * Retorna la nueva cadena con la variable reemplazada.
 */
char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_and_replace(NULL, str, var_value, index);
		free_ptr(tmp);
	}
	free_ptr(var_value);
	return (str);
}
