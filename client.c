/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:24:00 by pnolte            #+#    #+#             */
/*   Updated: 2022/06/24 13:22:58 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_msg(char *message, int pid)
{
	int	i;
	int	shift;

	i = 0;
	while (message[i] != '\0')
	{
		shift = 7;
		while (shift >= 0)
		{
			if (message[i] >> shift & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			shift--;
			usleep(50);
		}
		i++;
	}
	i = 8;
	while (i > 0)
	{
		i--;
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

void	received(int signo, siginfo_t *info, void *context)
{
	static int	count = 0;

	context = NULL;
	info = NULL;
	if (SIGUSR2 == signo)
		count++;
	else
	{
		ft_putstr_fd("Received: ", 1);
		ft_putnbr_fd(count, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_act;
	int					i;

	i = 0;
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent: ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	s_act.sa_sigaction = received;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	send_msg(argv[2], ft_atoi(argv[1]));
	while (1)
		pause();
	return (0);
}
