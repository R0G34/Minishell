#include "../incl/minishell.h"

/* contains_space:
 * Verifica si una cadena contiene espacios en blanco.
 * - Recorre la cadena y comprueba si hay algún carácter de espacio.
 * 
 * Retorna true si hay al menos un espacio, false en caso contrario.
 */
static bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

/* split_var_cmd_token:
 * Divide un token de tipo VAR que contiene espacios en múltiples tokens de tipo WORD.
 * - Separa la cadena en palabras individuales y las agrega como nuevos tokens.
 * - El primer elemento se asigna como comando del último nodo de la lista de comandos.
 * - Los siguientes elementos se agregan como argumentos al comando.
 */
static void	split_var_cmd_token(t_command *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*tmp;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = lst_new_token(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		lst_add_back_token(&new_tokens,
			lst_new_token(ft_strdup(strs[i]), NULL, WORD, DEFAULT));
	lst_add_back_token(&new_tokens,
		lst_new_token(NULL, NULL, END, DEFAULT));
	fill_args(&new_tokens, last_cmd);
	lstclear_token(&tmp, &free_ptr);
	free_str_tab(strs);
}

/* parse_word:
 * Procesa tokens de tipo WORD o VAR y los asigna a la estructura de comandos.
 * - Si el token es el primero o sigue a un PIPE, se asigna como comando.
 * - Si el token es de tipo VAR y contiene espacios, se divide en varios tokens.
 * - Si el token no es un comando, se agrega como argumento del último comando.
 */
void	parse_word(t_command **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*last_cmd;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last_cmd->command == NULL)
		{
			if (temp->type == VAR && contains_space(temp->str))
				split_var_cmd_token(last_cmd, temp->str);
			else
				last_cmd->command = ft_strdup(temp->str);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
	}
	*token_lst = temp;
}
