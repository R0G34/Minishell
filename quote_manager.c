#include "../incl/minishell.h"

/* count_len:
 * Calcula la longitud de una cadena ignorando las comillas si están presentes.
 * - Si encuentra una comilla simple (') o doble ("), cambia el estado de las comillas.
 * - Si la comilla cierra un bloque de texto, vuelve al estado DEFAULT.
 * - Solo cuenta los caracteres que no sean comillas, manteniendo la estructura de la cadena.
 * 
 * Retorna la longitud ajustada de la cadena con las comillas ignoradas.
 */
int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			if (str[i] == '\"')
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQUOTE)
			|| (str[i] == '\"' && status == DQUOTE))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

/* quotes_in_string:
 * Verifica si una cadena contiene comillas simples (') o dobles (").
 * 
 * Retorna true si hay al menos una comilla en la cadena, false en caso contrario.
 */
bool	quotes_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

/* handle_quotes:
 * Recorre la lista de tokens y elimina las comillas de cada token si es necesario.
 * - Si el token contiene comillas y no está precedido por un HEREDOC, se eliminan.
 * - Modifica directamente la lista de tokens para dejar solo el contenido sin comillas.
 * 
 * Retorna 0 tras completar el procesamiento.
 */
int	handle_quotes(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (quotes_in_string(temp->str) == true
			&& (!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))
			remove_quotes(&temp);
		temp = temp->next;
	}
	return (0);
}
