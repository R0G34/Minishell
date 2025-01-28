#include "../incl/minishell.h"

/* restore_io:
 * Restaura la entrada estándar (stdin) y la salida estándar (stdout)
 * a sus descriptores originales (0 y 1).
 * - Se usa para restablecer la entrada/salida después de la ejecución de un comando,
 *   preparando el shell para la siguiente entrada del usuario.
 * 
 * Retorna true si la restauración fue exitosa, false en caso de error.
 */
bool	restore_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

/* redirect_io:
 * Redirige la entrada y salida estándar a los descriptores de archivo adecuados.
 * - Guarda los descriptores originales antes de reemplazarlos, permitiendo su restauración.
 * - Si `fd_in` está configurado, duplica su descriptor en stdin.
 * - Si `fd_out` está configurado, duplica su descriptor en stdout.
 * 
 * Retorna true si la redirección fue exitosa, false en caso de error.
 */
bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	return (ret);
}

/* check_infile_outfile:
 * Verifica si los archivos de entrada y salida están correctamente configurados.
 * - Retorna true si los archivos están disponibles y accesibles.
 * - Retorna false si alguno de los archivos no se pudo abrir.
 */
bool	check_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}
