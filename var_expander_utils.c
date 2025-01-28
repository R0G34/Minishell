#include "../incl/minishell.h"

/* copy_var_value:
 * Copia el valor de una variable en una nueva cadena, actualizando su posición.
 * - Recorre el valor de la variable y lo copia en la nueva cadena.
 * - Actualiza el índice `j` para reflejar la nueva posición después de la copia.
 */
void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

/* get_new_token_string:
 * Crea una nueva cadena a partir de un token con variables expandidas.
 * - Copia el contenido original, reemplazando la variable por su valor correspondiente.
 * - Si la variable se encuentra en la posición `index`, se reemplaza con su valor.
 * - Retorna una nueva cadena con la variable expandida o NULL si hay un error.
 */
char	*get_new_token_string(char *oldstr, char *var_value,
		int newstr_size, int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * newstr_size);
	if (!new_str)
		return (NULL);
	while (oldstr[i])
	{
		if (oldstr[i] == '$' && i == index)
		{
			copy_var_value(new_str, var_value, &j);
			i = i + var_length(oldstr + index) + 1;
			if (oldstr[i] == '\0')
				break ;
		}
		new_str[j++] = oldstr[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
