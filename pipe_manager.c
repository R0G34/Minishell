#include "../incl/minishell.h"

/* close_pipe_fds:
 * Cierra los descriptores de archivo (fds) de todos los pipes en la lista de comandos.
 * - Si se proporciona un comando específico en `skip_cmd`, sus fds no se cerrarán.
 *   - El proceso padre pasa `NULL` para cerrar todos los pipes.
 *   - Un proceso hijo pasa su propio comando como `skip_cmd` para evitar cerrar sus propios fds.
 */
void	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

/* create_pipes:
 * Crea un conjunto de pipes para cada comando encadenado en la lista de comandos.
 * - Asigna memoria para los descriptores de archivo de cada pipe.
 * - Si la creación del pipe falla, libera la memoria y devuelve false.
 * 
 * Retorna true si la operación fue exitosa, false en caso de error.
 */
bool	create_pipes(t_data *data)
{
	int			*fd;
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

/* set_pipe_fds:
 * Configura los descriptores de archivo de un comando según su posición en la tubería.
 * - Si el comando tiene una entrada proveniente de otro comando (`prev->pipe_output`),
 *   se redirige la entrada estándar (`stdin`) al extremo de lectura del pipe anterior.
 * - Si el comando tiene una salida hacia otro comando, se redirige la salida estándar (`stdout`)
 *   al extremo de escritura de su pipe.
 * - Luego, se cierran todos los pipes innecesarios.
 * 
 * Retorna true si la configuración fue exitosa, false en caso contrario.
 */
bool	set_pipe_fds(t_command *cmds, t_command *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (true);
}
