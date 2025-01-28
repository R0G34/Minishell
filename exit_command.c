#include "../incl/minishell.h"

/* check_out_of_range:
 * Verifica si un número está fuera del rango permitido (LONG_MAX o LONG_MIN).
 * Si el número excede estos límites, establece un indicador de error.
 */

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

/* ft_atoi_long:
 * Convierte una cadena de caracteres numéricos en un valor de tipo long.
 * Si la conversión no es válida o el número está fuera de rango, se marca un error.
 */
static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

/* get_exit_code:
 * Obtiene el código de salida del argumento proporcionado al comando `exit`.
 * - Si no hay argumentos, devuelve el último código de salida ejecutado.
 * - Si el argumento no es un número válido, devuelve un error.
 * - Si hay más de un argumento, genera un error por exceso de argumentos.
 * Devuelve un código de salida válido (0-255) o 2 en caso de error.
 */
static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_last_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

/* is_quiet_mode:
 * Determina si el comando `exit` debe imprimir "exit" antes de cerrar el shell.
 * Si `exit` no se ejecuta como un comando independiente, su salida se suprime.
 */
static bool	is_quiet_mode(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

/* exit_builtin:
 * Implementa el comando `exit` del shell.
 * - Si no hay argumentos, sale con el último código de estado ejecutado.
 * - Si hay un argumento, lo convierte en un número y sale con ese valor.
 * - Si hay más de un argumento, genera un error y no finaliza el shell.
 * 
 * Si `exit` se ejecuta en un proceso hijo (por ejemplo, en una tubería),
 * solo termina el proceso hijo y no el shell principal.
 */
int	exit_builtin(t_data *data, char **args)
{
	int		exit_code;
	bool	error;
	bool	quiet;

	quiet = is_quiet_mode(data);
	error = false;
	if (!quiet && data->interactive)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_code = g_last_exit_code;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = errmsg_cmd("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many arguments", 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
