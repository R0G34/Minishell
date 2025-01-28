#include "../incl/minishell.h"

/* join_vars:
 * Une todos los tokens de una frase con variables dentro de comillas.
 * - Para que los tokens se unan, deben ser de tipo VAR y tener `join = true`.
 * - Esta función solo se usa cuando el comando es "echo".
 * 
 * Ejemplo:
 *   Entrada: ["Hello", "  ", "world"]
 *   Salida:  ["Hello  world"]
 */
char	*join_vars(t_token **token_node)
{
	t_token	*temp;
	char	*str;

	temp = *token_node;
	str = ft_strdup(temp->str);
	while (temp->type == VAR && temp->next->type == VAR
		&& temp->next->join == true)
	{
		str = ft_strjoin(str, temp->next->str);
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

/* count_args:
 * Cuenta el número de argumentos en la lista de tokens.
 * - Un argumento puede ser un WORD o un VAR.
 * - Si un VAR tiene `join = true`, se considera parte del mismo argumento.
 * 
 * Retorna la cantidad de argumentos válidos en la lista de tokens.
 */

int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		if (temp->type == VAR && temp->join == true)
		{
			while (temp->type == VAR && temp->join == true)
				temp = temp->next;
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

/* copy_in_new_tab:
 * Copia los argumentos existentes en una nueva lista de argumentos.
 * - La nueva lista amplía los argumentos previos con los nuevos tokens WORD o VAR.
 * - Si un VAR tiene `join = true`, se une con el argumento anterior.
 * 
 * Retorna la nueva lista de argumentos con los valores actualizados.
 */
char	**copy_in_new_tab(int len, char **new_tab,
			t_command *last_cmd, t_token *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == VAR)
	{
		if (tmp->join == true)
			new_tab[i] = join_vars(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

/* remove_empty_var_args:
 * Elimina variables vacías del entorno antes de agregarlas a "echo".
 * - Si una variable no existe en el entorno, su token se elimina.
 * - Si la variable existe pero su valor es vacío, se mantiene.
 * 
 * Ejemplo:
 *   Si $X no existe en el entorno, 'echo $X $X $USER' imprimirá:
 *   'username' (no '  username').
 */
void	remove_empty_var_args(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->type == VAR && temp->str[0] == '\0'
			&& temp->var_exists == false)
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			lstdelone_token(temp->prev, free_ptr);
		}
		else
			temp = temp->next;
	}
}
