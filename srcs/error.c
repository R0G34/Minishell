#include "../incl/minishell.h"

/* join_strs:
 * Une dos cadenas en una sola, liberando la memoria de la primera.
 * - Si `str` es NULL, devuelve una copia de `add`.
 * - Si `add` es NULL, devuelve `str` sin modificaciones.
 * 
 * Retorna la nueva cadena concatenada o NULL en caso de error.
 */
char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_ptr(tmp);
	return (str);
}

/* add_detail_quotes:
 * Determina si se deben añadir comillas alrededor de un detalle en un mensaje de error.
 * - Se añaden comillas si el comando es "export" o "unset".
 * 
 * Retorna true si se deben agregar comillas, false en caso contrario.
 */
static bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

/* errmsg_cmd:
 * Imprime un mensaje de error en la salida de error estándar, con el prefijo "minishell: ".
 * - Si el comando tiene un detalle, lo muestra con comillas si es necesario.
 * 
 * Retorna el código de error especificado.
 */
int	errmsg_cmd(char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = join_strs(msg, command);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(msg, "`");
		msg = join_strs(msg, detail);
		if (detail_quotes)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (error_nb);
}

/* errmsg:
 * Imprime un mensaje de error sin estar asociado a un comando específico.
 * - Se usa durante el análisis sintáctico para errores de sintaxis.
 */
void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = join_strs(msg, errmsg);
	if (quotes)
		msg = join_strs(msg, " `");
	else
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, detail);
	if (quotes)
		msg = join_strs(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}

/* usage_message:
 * Muestra un mensaje de uso cuando se pasan argumentos inválidos al shell.
 * - Explica cómo iniciar el shell correctamente.
 * 
 * Retorna el valor booleano proporcionado.
 */
bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}
