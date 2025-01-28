#include "../incl/minishell.h"

/* update_status:
 * Actualiza el estado del token dependiendo del tipo de comilla encontrada.
 * - Si encuentra una comilla simple (') en estado DEFAULT, cambia a estado SQUOTE.
 * - Si encuentra una comilla doble (") en estado DEFAULT, cambia a estado DQUOTE.
 * - Si encuentra una comilla simple (') en estado SQUOTE, vuelve a DEFAULT.
 * - Si encuentra una comilla doble (") en estado DQUOTE, vuelve a DEFAULT.
 */
static void	update_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == DEFAULT)
		(*token_node)->status = SQUOTE;
	else if (c == '\"' && (*token_node)->status == DEFAULT)
		(*token_node)->status = DQUOTE;
	else if (c == '\'' && (*token_node)->status == SQUOTE)
		(*token_node)->status = DEFAULT;
	else if (c == '\"' && (*token_node)->status == DQUOTE)
		(*token_node)->status = DEFAULT;
}

/* is_next_char_a_sep:
 * Verifica si un carácter es un separador válido para una variable de entorno.
 * - Los separadores válidos son: `$`, espacio, `=`, o el final de la cadena.
 * 
 * Retorna true si el carácter es un separador, false en caso contrario.
 */
static bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

/* var_between_quotes:
 * Verifica si una variable de entorno está completamente encerrada entre comillas dobles.
 * - Se considera que una variable está entre comillas si está rodeada por `"` en ambos lados.
 * 
 * Retorna true si la variable está entre comillas, false en caso contrario.
 */
static bool	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

/* var_expander:
 * Expande las variables de entorno en una lista de tokens.
 * - Recorre cada token y busca `$` seguido de un nombre de variable.
 * - Si la variable no está entre comillas simples, intenta reemplazarla por su valor.
 * - Si la variable está entre comillas dobles, se expande normalmente.
 * 
 * Retorna 0 tras completar la expansión de variables.
 */
int	var_expander(t_data *data, t_token **token_lst)
{
	t_token	*temp;
	int		i;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR)
		{
			i = 0;
			while (temp->str[i])
			{
				update_status(&temp, temp->str[i]);
				if (temp->str[i] == '$'
					&& is_next_char_a_sep(temp->str[i + 1]) == false
					&& var_between_quotes(temp->str, i) == false
					&& (temp->status == DEFAULT || temp->status == DQUOTE))
					replace_var(&temp,
						recover_val(temp, temp->str + i, data), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

/* var_expander_heredoc:
 * Variante de `expand_variables` para heredoc. Reemplaza una variable de entorno
 * por su valor dentro de un heredoc.
 * - Si la variable está entre comillas, no se expande.
 * - Si la variable no tiene valor, la reemplaza con una cadena vacía.
 * 
 * Retorna la nueva cadena con las variables reemplazadas.
 */
char	*var_expander_heredoc(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_next_char_a_sep(str[i + 1]) == false
			&& var_between_quotes(str, i) == false)
			str = replace_str_heredoc(str, recover_val(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
