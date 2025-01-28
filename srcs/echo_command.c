#include "../incl/minishell.h"

/* is_n_flag:
 * Verifica si un argumento es una opción válida del tipo -n.
 * Devuelve true si el argumento es una variación válida de -n (como -n, -nn, -nnnn, etc.).
 * Devuelve false si contiene algo diferente a '-' y 'n' (como --n o -n1234).
 */
static bool	is_n_flag(char *arg)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = true;
	return (n_flag);
}

/* echo_print_args:
 * Imprime los argumentos proporcionados al comando echo en la salida estándar.
 * Si la opción -n está presente, no se imprime una nueva línea al final.
 */
static void	echo_print_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/* echo_builtin:
 * Implementa el comando `echo` del shell, que imprime cadenas en la salida estándar.
 * - Si la opción -n está presente, no añade una nueva línea al final.
 * Devuelve 0 al completar correctamente.
 */
int	echo_builtin(t_data *data, char **args)
{
	int		i;
	bool	n_flag;

	(void)data;
	n_flag = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo_print_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}
