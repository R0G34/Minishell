#include "../incl/minishell.h"

int	g_last_exit_code;

/* get_children:
 * Espera a que los procesos hijos finalicen, limpiando los descriptores
 * de archivos y la lista de comandos.
 * 
 * Retorna el código de salida de un proceso hijo según Bash:
 *  - Si el proceso finaliza normalmente, devuelve su código de salida.
 *  - Si el proceso es terminado por una señal, devuelve 128 + número de la señal.
 *  - Si hay múltiples comandos en una tubería, el estado de salida será 
 *    el del último comando ejecutado en la tubería.
 */
static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

/* create_children:
 * Crea un proceso hijo para cada comando a ejecutar. Si el comando es 
 * un built-in sin tuberías, se ejecuta en el proceso principal en lugar de un hijo.
 * 
 * Retorna true si se creó correctamente un proceso para cada comando o si
 * un built-in se ejecutó directamente en el proceso principal.
 * Retorna false si hubo un error en `fork`.
 */
static int	create_children(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

/* prep_for_exec:
 * Prepara la lista de comandos antes de la ejecución.
 * - Crea las tuberías necesarias para la comunicación entre procesos.
 * - Verifica los archivos de entrada y salida asociados a cada comando.
 * 
 * Retorna false si hubo un error en la preparación.
 * Retorna true si todo está listo para la ejecución.
 */
static int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds
			&& !check_infile_outfile(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

/* execute:
 * Ejecuta los comandos dados creando procesos hijos y esperando su finalización.
 * - Si el comando es un built-in sin tuberías, se ejecuta directamente en el proceso principal.
 * - Si el comando no es un built-in, se crean procesos hijos para su ejecución.
 * 
 * Retorna el código de salida del último proceso hijo en terminar,
 * o 1 en caso de fallo al crear un proceso hijo.
 */
int	execute(t_data *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_infile_outfile(data->cmd->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		ret = execute_builtin(data, data->cmd);
		restore_io(data->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(data));
}
