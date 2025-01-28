#include "../incl/minishell.h"

/* change_status_to_quote:
 * Cambia el estado del token a comillas simples (SQUOTE) o dobles (DQUOTE),
 * dependiendo del carácter encontrado.
 */
static void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->str[*i] == '\'')
		(*token_node)->status = SQUOTE;
	if ((*token_node)->str[*i] == '\"')
		(*token_node)->status = DQUOTE;
	(*i)++;
}

/* if_quotes_and_default:
 * Verifica si un carácter es una comilla simple o doble y si el estado actual es DEFAULT.
 * Esto indica que se está abriendo una nueva comilla en la cadena.
 * 
 * Retorna true si se encuentra una comilla no cerrada, false en caso contrario.
 */
static bool	if_quotes_and_default(t_token **token_node, int i)
{
	if (((*token_node)->str[i] == '\'' || (*token_node)->str[i] == '\"')
		&& (*token_node)->status == DEFAULT)
		return (true);
	else
		return (false);
}

/* change_back_to_default:
 * Si se encuentra una comilla de cierre, se restablece el estado a DEFAULT.
 * 
 * Retorna true si se restableció el estado, false en caso contrario.
 */
static bool	change_back_to_default(t_token **token_node, int *i)
{
	if (((*token_node)->str[*i] == '\'' && (*token_node)->status == SQUOTE)
		|| ((*token_node)->str[*i] == '\"' && (*token_node)->status == DQUOTE))
	{
		(*token_node)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

/* remove_quotes:
 * Recorre la cadena del token y elimina las comillas, manteniendo solo el contenido.
 * - Si se encuentra una comilla inicial sin estado previo, se establece el estado de comillas.
 * - Si se encuentra una comilla de cierre, se restablece el estado a DEFAULT.
 * - Todos los demás caracteres se copian en una nueva cadena sin comillas.
 * 
 * Retorna 0 si se eliminaron las comillas correctamente, 1 si ocurrió un error.
 */
int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->str, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->str[i])
	{
		if (if_quotes_and_default(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_default(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->str[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_line;
	(*token_node)->join = true;
	return (0);
}
