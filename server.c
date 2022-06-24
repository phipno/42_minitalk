/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:43:45 by pnolte            #+#    #+#             */
/*   Updated: 2022/06/24 13:01:08 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	msg_rec(int signo, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		i = 0;
	pid_t			client_pid;

	context = NULL;
	client_pid = info->si_pid;
	if (signo == SIGUSR2)
		c |= 1;
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			kill(client_pid, SIGUSR1);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR2);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_act;

	ft_putstr_fd("PID:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_act.sa_flags = SA_SIGINFO;
	s_act.sa_sigaction = msg_rec;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	while (1)
		pause();
}
