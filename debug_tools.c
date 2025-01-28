#include "../incl/minishell.h"

/* print_cmd_args:
 * Imprime los argumentos de un comando en la consola.
 * Si el comando no tiene argumentos, la función no hace nada.
 */
static void	print_cmd_args(t_command *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		i++;
	}
}

/* print_cmd_io:
 * Imprime la información sobre los descriptores de archivo de un comando,
 * incluyendo los archivos de entrada y salida, así como delimitadores de heredoc.
 */
static void	print_cmd_io(t_command *cmd)
{
	if (!cmd->io_fds)
		return ;
	if (cmd->io_fds->infile)
	{
		printf("\tInfile: %s\n", cmd->io_fds->infile);
		printf("\t\tfd_in: %d\n", cmd->io_fds->fd_in);
	}
	if (cmd->io_fds->heredoc_delimiter)
		printf("\tHeredoc delimiter: %s\n", cmd->io_fds->heredoc_delimiter);
	if (cmd->io_fds->outfile)
	{
		printf("\tOutfile: %s\n", cmd->io_fds->outfile);
		printf("\t\tfd_in: %d\n", cmd->io_fds->fd_out);
	}
}

/* print_cmd_list:
 * Recorre la lista de comandos almacenados y muestra sus detalles en la consola,
 * incluyendo sus argumentos, configuraciones de entrada/salida y conexiones entre comandos.
 */
void	print_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	printf("\n---- COMMAND LIST\n");
	while (cmd)
	{
		printf("--- Command = %s\n", cmd->command);
		print_cmd_args(cmd);
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		print_cmd_io(cmd);
		if (cmd->prev == NULL)
			printf("\tprev = NULL\n");
		else
			printf("\tprev = %s\n", cmd->prev->command);
		if (cmd->next == NULL)
			printf("\tnext = NULL\n");
		else
			printf("\tnext = %s\n", cmd->next->command);
		printf("\n");
		cmd = cmd->next;
	}
	printf("\n");
}

/* print_token_type:
 * Muestra el tipo de un token con un prefijo de texto personalizado.
 */
void	print_token_type(t_token *token, char *prefix)
{
	printf("%s", prefix);
	if (token->type == SPACES)
		printf("SPACES\n");
	else if (token->type == WORD)
		printf("WORD\n");
	else if (token->type == VAR)
		printf("VAR\n");
	else if (token->type == PIPE)
		printf("PIPE\n");
	else if (token->type == INPUT)
		printf("INPUT\n");
	else if (token->type == TRUNC)
		printf("TRUNC\n");
	else if (token->type == HEREDOC)
		printf("HEREDOC\n");
	else if (token->type == APPEND)
		printf("APPEND\n");
	else if (token->type == END)
		printf("END\n");
}

/* print_token_list:
 * Muestra una lista de tokens con información detallada sobre cada uno,
 * incluyendo su contenido, tipo y enlaces a tokens anteriores y siguientes.
 */
void	print_token_list(t_token **tokens)
{
	t_token	*lst;
	int		i;

	lst = *tokens;
	printf("\n---- TOKEN LIST\n");
	i = 0;
	while (lst)
	{
		printf("--- Token [%d] [%p]\n", i, lst);
		printf("\tString = [%s]\n", lst->str);
		printf("\tStr backup = [%s]\n", lst->str_backup);
		print_token_type(lst, "\tType = ");
		printf("\tStatus = %d\n", lst->status);
		if (lst->prev)
			printf("\tPrev = [%p]\n", lst->prev);
		else
			printf("\tPrev = NULL\n");
		if (lst->next)
			printf("\tNext = [%p]\n", lst->next);
		else
			printf("\tNext = NULL\n");
		i++;
		lst = lst->next;
	}
}
