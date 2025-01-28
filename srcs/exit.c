#include "../incl/minishell.h"

/* exit_shell:
 * Cierra correctamente el programa minishell.
 * - Cierra todos los descriptores de archivo abiertos.
 * - Libera toda la memoria asignada antes de salir.
 * - Finaliza el proceso con el código de salida especificado.
 */
void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exno);
}
