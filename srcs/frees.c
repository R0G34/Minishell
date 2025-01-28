#include "../incl/minishell.h"

/* free_data:
 * Libera toda la memoria utilizada por el shell para ejecutar un comando.
 * - Si `clear_history` es true, también libera el entorno, el historial de comandos
 *   y los directorios de trabajo almacenados.
 */
void	free_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		lstclear_token(&data->token, &free_ptr);
	if (data && data->cmd)
		lst_clear_cmd(&data->cmd, &free_ptr);
	if (clear_history == true)
	{
		if (data && data->working_dir)
			free_ptr(data->working_dir);
		if (data && data->old_working_dir)
			free_ptr(data->old_working_dir);
		if (data && data->env)
			free_str_tab(data->env);
		rl_clear_history();
	}
}

/* close_fds:
 * Cierra los descriptores de archivo abiertos, incluidos los pipes y fds de entrada/salida.
 * - Si `close_backups` es true, también restaura y cierra los backups de STDIN y STDOUT.
 */
void	close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

/* free_io:
 * Libera la estructura de descriptores de entrada/salida.
 * - Restaura la entrada/salida estándar antes de liberar la memoria.
 * - Si había un heredoc, elimina su archivo temporal.
 */
void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

/* free_str_tab:
 * Libera un array de strings y establece sus punteros en NULL para evitar errores de doble liberación.
 */
void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

/* free_ptr:
 * Libera un puntero de cualquier tipo si no es NULL y lo establece en NULL.
 * - Esto evita liberaciones dobles accidentales.
 */
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
