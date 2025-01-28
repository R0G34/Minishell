#include "../incl/minishell.h"

/*
	TRUNC -> Redirección de salida en modo truncado.
	El archivo cuyo nombre resulta de la expansión de la palabra será abierto 
	en modo escritura en el descriptor de archivo `n` o en la salida estándar (`fd 1`) 
	si `n` no está especificado.
	Si el archivo no existe, se crea; si ya existe, se trunca a tamaño 0.

	El formato general para redirigir la salida es: `[n]>[|]word`
*/

/* get_relative_path:
 * Obtiene la ruta absoluta o relativa de un archivo.
 * - Si el archivo comienza con '/', se considera una ruta absoluta y se devuelve tal cual.
 * - Si el archivo es relativo, se antepone `./` para formar la ruta completa.
 * 
 * Retorna la ruta final del archivo.
 */

char	*get_relative_path(char *file_to_open)
{
	char	*path;
	char	*ret;

	if (file_to_open[0] == '/')
		return (ft_strdup(file_to_open));
	path = ft_strdup("./");
	ret = ft_strjoin(path, file_to_open);
	printf("PARSING - Get_rel_path function return : %s\n", ret);
	return (ret);
}

/* open_outfile_trunc:
 * Abre un archivo de salida en modo truncado.
 * - Si ya había un archivo de salida definido, lo libera y lo sobrescribe.
 * - Si hubo un error previo al abrir un archivo de entrada o salida,
 *   no intenta abrir otro archivo de salida.
 * 
 * Ejemplo de casos donde el archivo "test" no debe abrirse:
 *   `echo hello > forbidden_file > test`
 *   `echo hello >> forbidden_file > test`
 *   `< forbidden_file cat > test`
 */
static void	open_outfile_trunc(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

/* parse_trunc:
 * Maneja la redirección de salida en modo truncado (`>`).
 * - Obtiene el último comando de la lista y le asigna un archivo de salida truncado.
 * - Si hay más tokens después de la redirección, avanza en la lista de tokens.
 */
void	parse_trunc(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outfile_trunc(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
