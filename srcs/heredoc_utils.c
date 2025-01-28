#include "../incl/minishell.h"

/* make_str_from_tab:
 * Crea una única cadena a partir de un array de cadenas, uniendo cada palabra con un espacio.
 * - Si el array contiene varias palabras, las concatena en una sola cadena separada por espacios.
 * - Libera la memoria del array original después de crear la nueva cadena.
 * 
 * Retorna la cadena resultante.
 */
static char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free_ptr(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_ptr(tmp);
		}
	}
	free_str_tab(tab);
	return (str);
}

/* get_expanded_var_line:
 * Prepara una línea que contiene '$' para la expansión de variables de entorno.
 * - Divide la línea en palabras para evitar problemas con variables inexistentes.
 * - Expande las variables de entorno encontradas en la línea.
 * 
 * Retorna una nueva línea con las variables expandidas.
 */
static char	*get_expanded_var_line(t_data *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expander_heredoc(data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

/* evaluate_heredoc_line:
 * Verifica si la línea leída debe escribirse en el archivo de heredoc.
 * - Si la línea es NULL o coincide con el delimitador, se devuelve false para detener la lectura.
 * - Si la línea contiene variables y el heredoc permite expansión, se expanden antes de escribir.
 * 
 * Retorna true si la línea debe escribirse, false si se debe detener la lectura.
 */
static bool	evaluate_heredoc_line(t_data *data, char **line,
									t_io_fds *io, bool *ret)
{
	if (*line == NULL)
	{
		errmsg_cmd("warning", "here-document delimited by end-of-file: wanted",
			io->heredoc_delimiter, true);
		*ret = true;
		return (false);
	}
	if (ft_strcmp(*line, io->heredoc_delimiter) == 0)
	{
		*ret = true;
		return (false);
	}
	if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(data, *line);
		if (!(*line))
		{
			free_ptr(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

/* fill_heredoc:
 * Copia la entrada del usuario en un archivo temporal para heredoc.
 * - Si el usuario ingresa una variable de entorno como `$USER`, la expande antes de escribir.
 * - La escritura se detiene cuando el usuario ingresa el delimitador del heredoc.
 * 
 * Retorna true en caso de éxito, false en caso de fallo.
 */
bool	fill_heredoc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		set_signals_interactive();
		line = readline(">");
		set_signals_noninteractive();
		if (!evaluate_heredoc_line(data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (ret);
}
