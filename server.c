/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:00:00 by irobinso          #+#    #+#             */
/*   Updated: 2025/02/05 11:47:59 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"

static void	ft_handler(int signum, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	c = 0;

	(void)context;
	if (signum == SIGUSR2)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			ft_printf("\n");
			if (kill(info->si_pid, SIGUSR1) == -1)
				ft_printf("Error: Failed to send confirmation signal\n");
		}
		else if (write(1, &c, 1) == -1)
			ft_printf("Error: Failed to write character\n");
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("\033[94mPID: \033[0m %d\n", pid);
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error: Failed to set up signal handlers\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
