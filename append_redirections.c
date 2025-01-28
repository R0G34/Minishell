#include "../incl/minishell.h"

/*
	APPEND
	La redirección de salida en modo "append" hace que el archivo especificado
	sea abierto para agregar contenido en el descriptor de archivo `n` (o en
	la salida estándar `fd 1` si `n` no está especificado).  
	Si el archivo no existe, se crea.  

	El formato general para la redirección con `append` es: `[n]>>word`.
*/

/* open_outfile_append:
 * Abre un archivo de salida en modo "append".  
 * - Si ya había un archivo de salida definido, lo libera y lo sobrescribe.  
 * - Si un intento previo de abrir un archivo de entrada o salida falló
 *   (archivo inexistente o permisos denegados), no intenta abrir un nuevo archivo.  
 * 
 * Ejemplo de casos donde no se debe abrir el archivo "test":
 *   `echo hello > forbidden_file >> test`
 *   `echo hello >> forbidden_file >> test`
 *   `< forbidden_file cat >> test`
 */
static void	open_outfile_append(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0' && var_filename)
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

/* parse_append:
 * Maneja la redirección de salida en modo "append".
 * - Obtiene el último comando de la lista y le asigna un archivo de salida en modo "append".
 * - Si hay más tokens después de la redirección, avanza en la lista de tokens.
 */
void	parse_append(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outfile_append(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
