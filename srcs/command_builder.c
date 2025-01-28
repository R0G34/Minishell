#include "../incl/minishell.h"

/* prep_no_arg_commands:
 * Asegura que todos los comandos tengan al menos un argumento.
 * - Si un comando no tiene argumentos, se asigna su propio nombre como primer argumento.
 * - Esta función recorre la lista de comandos y ajusta los argumentos según sea necesario.
 */
static void	prep_no_arg_commands(t_data *data)
{
	t_command	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
}

/* create_commands:
 * Crea una lista de comandos a partir de una lista de tokens.
 * - Analiza los tokens y asigna los datos adecuados a cada comando.
 * - Maneja diferentes tipos de tokens como palabras, variables, redirecciones y pipes.
 * - Si un comando no tiene argumentos, se prepara adecuadamente.
 */
void	create_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_add_back_cmd(&data->cmd, lst_new_cmd(false));
		if (temp->type == WORD || temp->type == VAR)
			parse_word(&data->cmd, &temp);
		else if (temp->type == INPUT)
			parse_input(&data->cmd, &temp);
		else if (temp->type == TRUNC)
			parse_trunc(&data->cmd, &temp);
		else if (temp->type == HEREDOC)
			parse_heredoc(data, &data->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == END)
			break ;
	}
	prep_no_arg_commands(data);
}
