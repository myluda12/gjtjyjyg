/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:03:02 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/31 18:13:19 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	my_signal(int sig)
{
	// write(1, "\n$3> ", 5)÷;
	g_shell->g_signal = 1;
	if (g_shell->g_signal_hamza)
		return ;
	printf("\n"); 
    rl_on_new_line(); 
    rl_replace_line("", 0);
    rl_redisplay();
	//rl_clear_signals();
}

void	maange_signals(void)
{
	dup2(g_shell->stdio[0], 0);
	dup2(g_shell->stdio[1], 1);
	signal(SIGINT, my_signal);
	signal(SIGQUIT, SIG_IGN);
}

size_t	ft_strlen_sec(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	g_shell = (t_list *)malloc(sizeof(t_list));
	g_shell->g_fd = 1;
	g_shell->head = malloc(sizeof(t_node));
	copy(env, ft_strlen_sec(env), g_shell);
	copy_env_str(g_shell);
	g_shell->stdio[0] = dup(0);
	g_shell->stdio[1] = dup(1);
	while (1)
	{
		maange_signals();
		g_shell->buffer = readline("$2> ");
		if (g_shell->buffer == NULL)
			exit(0);
		if (g_shell->g_signal == 0)
		{
			add_history(g_shell->buffer);
			split_cmds(g_shell);
			//system("leaks minishell");
		}
		else
			g_shell->g_signal = 0;
	}
}