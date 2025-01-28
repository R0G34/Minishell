#include "../incl/minishell.h"

/*
Esta función divide la cadena proporcionada (entrada del usuario) en dos tipos 
de tokens: palabras o separadores (pipes, heredoc, etc.).
Analiza cada carácter de la cadena y determina si es un separador o una palabra, 
y luego guarda el token en una lista enlazada.

También verifica si hay errores de comillas sin cerrar y define qué separadores 
serán evaluados según las reglas de comillas simples o dobles:

Sin comillas: Bash intenta evaluar todos los caracteres especiales.
Comillas simples ('): Evitan cualquier tipo de evaluación.
Comillas dobles ("): Previenen la mayoría de evaluaciones, pero no la evaluación 
de variables.*/
int	tokenization(t_data *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SQUOTE)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
