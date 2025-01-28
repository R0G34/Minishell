#include "../incl/minishell.h"

/* is_var_compliant:
 * Verifica si un carácter es válido para formar parte de un nombre de variable.
 * Un nombre de variable válido solo puede contener caracteres alfanuméricos y guion bajo (_).
 * 
 * Retorna true si el carácter es válido, false en caso contrario.
 */
bool	is_var_compliant(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

/* var_length:
 * Calcula la longitud de un nombre de variable dentro de una cadena,
 * comenzando desde el primer `$`. 
 * - Si la variable es un número o `?`, su longitud será de 1.
 * - Si la variable tiene un nombre alfanumérico, se cuenta hasta encontrar 
 *   un carácter inválido.
 * 
 * Retorna la longitud del nombre de la variable.
 */
int	var_length(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (is_var_compliant(str[i]) == false)
			break ;
		count++;
		i++;
	}
	return (count);
}

/* identify_var:
 * Extrae el nombre de la variable de una cadena que contiene `$`.
 * - Encuentra la posición de `$` y obtiene el nombre de la variable.
 * - Retorna el nombre de la variable con un '=' al final, 
 *   para facilitar su búsqueda en el entorno.
 * 
 * Retorna la variable en formato `VAR=` o NULL si hay un error.
 */
char	*identify_var(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = var_length(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free_ptr(var);
	var = tmp;
	return (var);
}
