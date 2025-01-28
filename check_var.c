#include "../incl/minishell.h"

/* Comprueba si una cadena contiene variables ($) y marca 
el token correspondiente. */
static void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->str[i])
	{
		if ((*token_node)->str[i] == '$')
		{	
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

/* Valida una lista de tokens, detecta variables y 
comprueba errores de sintaxis consecutivos. */
int	check_if_var(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE)
	{
		errmsg("syntax error near unexpected token", temp->str, true);
		return (FAILURE);
	}
	while (temp)
	{
		variable_check(&temp);
		if (check_consecutives(&temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}
