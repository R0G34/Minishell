#include "../incl/minishell.h"

/* cmd_is_dir:
 * Comprueba si el comando ingresado es un directorio en lugar de un ejecutable.
 * 
 * Retorna true si el comando es un directorio, false en caso contrario.
 */
bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

/* check_command_not_found:
*	Searches for the reason a command was not found in the system binaries.
*	Returns an error message and status if the command is invalid,
*	returns EXIT_SUCCESS if the command is valid and should be executed
*	as a local executable.
*/
int	check_command_not_found(t_data *data, t_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL
		&& get_env_var_index(data->env, "PATH") != -1)
		return (errmsg_cmd(cmd->command, NULL, "command not found",
				CMD_NOT_FOUND));
	if (access(cmd->command, F_OK) != 0)
		return (errmsg_cmd(cmd->command, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))
		return (errmsg_cmd(cmd->command, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (errmsg_cmd(cmd->command, NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
