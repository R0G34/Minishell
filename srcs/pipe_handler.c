#include "../incl/minishell.h"

/* parse_pipe:
 * Maneja la redirección de comandos a través de un pipe (`|`).
 * - Marca el último comando de la lista para que su salida se dirija a un pipe.
 * - Crea un nuevo comando en la lista para manejar la entrada del siguiente comando.
 * - Avanza en la lista de tokens para procesar el siguiente comando.
 */
void	parse_pipe(t_command **cmd, t_token **token_lst)
{
	t_command	*last_cmd;

	last_cmd = lst_last_cmd(*cmd);
	last_cmd->pipe_output = true;
	lst_add_back_cmd(&last_cmd, lst_new_cmd(false));
	*token_lst = (*token_lst)->next;
}
