#include "../incl/minishell.h"

/* init_env:
 * Inicializa la estructura de datos con las variables de entorno heredadas del shell original.
 * - Reserva memoria para almacenar las variables de entorno.
 * - Copia cada variable de `env` en la estructura `data->env`.
 * 
 * Retorna false en caso de error, true si la inicialización es exitosa.
 */
static bool	init_env(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(env_var_count(env) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
		i++;
	}
	return (true);
}

/* init_wds:
 * Inicializa las variables de directorio de trabajo.
 * - Si `PWD` y `OLDPWD` no están definidos en el entorno, los configura con `getcwd`.
 * - Es necesario para el correcto funcionamiento del comando `cd`.
 * 
 * Retorna true si la inicialización es exitosa, false en caso de error.
 */
static bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->working_dir = ft_strdup(wd);
	if (!data->working_dir)
		return (false);
	if (get_env_var_index(data->env, "OLDPWD") != -1)
	{
		data->old_working_dir = ft_strdup(get_env_var_value(data->env,
					"OLDPWD"));
		if (!data->old_working_dir)
			return (false);
	}
	else
	{
		data->old_working_dir = ft_strdup(wd);
		if (!data->old_working_dir)
			return (false);
	}
	return (true);
}

/* init_data:
 * Inicializa la estructura de datos utilizada para analizar y ejecutar comandos del usuario.
 * - Configura las variables de entorno y los directorios de trabajo.
 * - Inicializa los punteros de tokens y comandos.
 * - Establece valores predeterminados para PID y código de salida global.
 * 
 * Retorna true si la inicialización es exitosa, false en caso de error.
 */
bool	init_data(t_data *data, char **env)
{
	if (!init_env(data, env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_wds(data))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	g_last_exit_code = 0;
	return (true);
}

/* init_io:
 * Inicializa la estructura de entrada/salida de un comando con valores predeterminados.
 * - Establece los archivos de entrada y salida en NULL.
 * - Configura valores por defecto para heredoc y backups de `stdin` y `stdout`.
 */
void	init_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}
