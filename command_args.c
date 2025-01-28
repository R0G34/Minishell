#include "../incl/minishell.h"

/* count_arguments:
 * Cuenta cuántos tokens de tipo WORD o VAR existen a partir del token actual.
 * - Se usa para determinar el número de argumentos que tendrá un comando.
 * 
 * Retorna el número de tokens de tipo argumento encontrados.
 */
int	count_arguments(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

/* create_args_default_mode:
 * Crea el array de argumentos de un comando en modo predeterminado.
 * - Asigna memoria para la lista de argumentos usando `count_argument_tokens`.
 * - Copia el comando en `last_cmd->args[0]` y luego copia los argumentos desde la lista de tokens.
 * - Avanza el puntero de tokens hasta el siguiente no relacionado con argumentos.
 * 
 * Retorna SUCCESS si se crean correctamente los argumentos, o FAILURE si hay un error.
 */
int	create_args_default_mode(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb_args = count_arguments(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	temp = *token_node;
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd->args[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

/* copy_default_in_new_tab:
 * Copia los argumentos existentes de `last_cmd` en una nueva lista de argumentos.
 * - La nueva lista se amplía para incluir nuevos argumentos de la lista de tokens.
 * - Se reserva memoria para la nueva lista de argumentos y se copian los valores.
 * 
 * Retorna la nueva lista de argumentos con los valores actualizados.
 */
static char	**copy_default_in_new_tab(
	int len, char **new_tab, t_command *last_cmd, t_token **tk_node)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tk_node;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (temp->type == WORD || temp->type == VAR)
	{
		new_tab[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

/* add_args_default_mode:
 * Agrega argumentos adicionales a un comando en modo predeterminado.
 * - Crea una nueva lista de argumentos combinando los existentes con los nuevos.
 * - Libera la lista anterior y actualiza `last_cmd->args` con la nueva lista.
 * - Avanza el puntero de tokens al siguiente token no relacionado con argumentos.
 * 
 * Retorna SUCCESS si los argumentos se agregan correctamente, o FAILURE si hay un error.
 */
int	add_args_default_mode(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	while (temp->type == WORD || temp->type == VAR)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_default_in_new_tab(len, new_tab, last_cmd, token_node);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	*token_node = temp;
	return (SUCCESS);
}

/* fill_args:
 * Llena la lista de argumentos de un comando.
 * - Si el comando es `echo`, usa un modo especial para manejar los argumentos.
 * - Para otros comandos, usa el modo predeterminado de argumentos.
 * 
 * Retorna SUCCESS después de llenar los argumentos.
 */
int	fill_args(t_token **token_node, t_command *last_cmd)
{
	if (!ft_strcmp(last_cmd->command, "echo"))
	{
		if (!(last_cmd->args))
			return (create_args_echo_mode(token_node, last_cmd));
		else
			return (add_args_echo_mode(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			return (create_args_default_mode(token_node, last_cmd));
		else
			return (add_args_default_mode(token_node, last_cmd));
	}
	return (SUCCESS);
}
