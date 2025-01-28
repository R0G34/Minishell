#include "../incl/minishell.h"

/*	INPUT -> REDIR_IN (<)
	La redirección de entrada hace que el archivo especificado sea abierto para lectura
	en el descriptor de archivo `n` (o en la entrada estándar `fd 0` si `n` no está especificado).

	El formato general para redirigir la entrada es: `[n]<word`
*/

/* remove_old_file_ref:
 * Elimina una referencia a un archivo de entrada o salida previamente abierto.
 * - Si `infile` es true, elimina el archivo de entrada (`infile`).
 * - Si `infile` es false, elimina el archivo de salida (`outfile`).
 * - Si hubo un error previo al abrir un archivo, no intenta eliminarlo.
 * 
 * Retorna true si se eliminó correctamente, false si hubo un problema.
 */

bool	remove_old_file_ref(t_io_fds *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			free_ptr(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->infile);
		}
		free_ptr(io->infile);
		close(io->fd_in);
	}
	else if (infile == false && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		free_ptr(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

/* open_infile:
 * Abre un archivo de entrada para redirección (`<`).
 * - Si ya había un archivo de entrada definido, lo libera y lo sobrescribe.
 * - Si un intento previo de abrir un archivo falló (archivo inexistente o permisos denegados),
 *   no intenta abrir uno nuevo.
 * 
 * Ejemplo:
 *   `< Makefile < README.md cat > test`  → Se usa `README.md` como entrada (ignora `Makefile`).
 *   `< forbidden < README.md cat > test`  → Da "Permiso denegado" (no se ejecuta `cat`).
 */
static void	open_infile(t_io_fds *io, char *file, char *original_filename)
{
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		errmsg_cmd(original_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		errmsg_cmd(io->infile, NULL, strerror(errno), false);
}

/* parse_input	:
 * Maneja la redirección de entrada (`<`).
 * - Obtiene el último comando de la lista y le asigna un archivo de entrada.
 * - Si hay más tokens después de la redirección, avanza en la lista de tokens.
 */
void	parse_input(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_infile(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}