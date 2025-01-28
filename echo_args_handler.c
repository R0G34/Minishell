#include "../incl/minishell.h"

/* create_args_echo_mode:
 * Maneja el caso específico cuando el comando es "echo".
 * - Asigna memoria para la lista de argumentos utilizando `count_args`.
 * - Recorre la lista de tokens mientras los nodos sean de tipo WORD o VAR:
 *   - Si `join` en la estructura del token es `true`, se unen los tokens VAR que tengan `join = true`.
 *   - Si `join = false`, simplemente se copia el token actual en `last_cmd->args[i]`.
 * 
 * Retorna SUCCESS si los argumentos se crean correctamente, o FAILURE en caso de error.
 */
int	create_args_echo_mode(t_token **token_node, t_command *last_cmd)
{
	int		nb_args;
	t_token	*temp;
	int		i;

	remove_empty_var_args(token_node);
	temp = *token_node;
	nb_args = count_args(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->join == true)
			last_cmd->args[i] = join_vars(&temp);
		else
			last_cmd->args[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

/* add_args_echo_mode:
 * Agrega argumentos adicionales al comando "echo".
 * - Crea una nueva lista de argumentos combinando los existentes con los nuevos.
 * - Copia los argumentos anteriores y añade los nuevos de la lista de tokens.
 * - Libera la lista anterior y actualiza `last_cmd->args` con la nueva.
 * 
 * Retorna SUCCESS si los argumentos se agregan correctamente, o FAILURE si hay un error.
 */
int	add_args_echo_mode(t_token **token_node, t_command *last_cmd)
{
	int		len;
	int		nb_args;
	char	**new_tab;
	t_token	*temp;

	remove_empty_var_args(token_node);
	temp = *token_node;
	nb_args = count_args(temp);
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_in_new_tab(len, new_tab, last_cmd, temp);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	while (temp->type == WORD || temp->type == VAR)
		temp = temp->next;
	*token_node = temp;
	return (SUCCESS);
}
