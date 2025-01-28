#include "../incl/minishell.h"

/* signal_reset_prompt:
 * Restablece el prompt de entrada del usuario cuando se recibe una señal en modo interactivo.
 * - Se ejecuta al recibir SIGINT (Ctrl + C), limpiando la línea actual y mostrando un nuevo prompt.
 */
void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* set_signals_interactive:
 * Configura el comportamiento del shell ante SIGINT (Ctrl + C) y SIGQUIT (Ctrl + \).
 * - SIGINT restablece el prompt de usuario con una nueva línea en blanco.
 * - SIGQUIT se ignora.
 * - Se usa cuando el shell está en modo interactivo, esperando entrada del usuario.
 */
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/* signal_print_newline:
 * Imprime una nueva línea cuando se recibe una señal en modo no interactivo.
 */
void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

/* set_signals_noninteractive:
 * Configura el comportamiento del shell ante SIGINT (Ctrl + C) y SIGQUIT (Ctrl + \) en modo no interactivo.
 * - Se usa cuando el shell no está esperando entrada del usuario, sino ejecutando un comando (ej. `cat`).
 * - En este caso, el shell no debe reaccionar a SIGINT y SIGQUIT; solo el proceso en ejecución debe hacerlo.
 */
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/* ignore_sigquit:
 * Ignora la señal SIGQUIT (Ctrl + \), evitando que el shell la procese.
 */
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
