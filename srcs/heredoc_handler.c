#include "../incl/minishell.h"

/* get_heredoc:
 * Abre un heredoc esperando la entrada del usuario.
 * - Reemplaza cualquier variable por su valor correspondiente en el entorno.
 * - Escribe la entrada en un archivo temporal.
 * 
 * Retorna false en caso de error, true si se completa con éxito.
 */
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, io, tmp_fd);
	close(tmp_fd);
	return (ret);
}

/* get_heredoc_name:
 * Genera un nombre único para el archivo temporal del heredoc.
 * 
 * Retorna el nuevo nombre generado.
 */
static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

/* get_delim:
 * Obtiene el delimitador del heredoc.
 * - Si el delimitador está entre comillas, las elimina y marca `quotes` como true.
 * - Si no hay comillas, retorna el delimitador tal cual.
 * 
 * Retorna el delimitador procesado.
 */
static char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

/* parse_heredoc:
 * Crea un archivo temporal para el heredoc y lo llena con la entrada del usuario.
 * - Obtiene el último comando de la lista y le asigna el archivo temporal como entrada.
 * - Extrae el delimitador del heredoc y determina si se deben expandir variables.
 * - Si el heredoc se llena correctamente, se abre para su lectura.
 */
void	parse_heredoc(t_data *data, t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;
	t_io_fds	*io;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	io = cmd->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = get_heredoc_name();
	io->heredoc_delimiter = get_delim(temp->next->str, &(io->heredoc_quotes));
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
