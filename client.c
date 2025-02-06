/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:00:00 by irobinso          #+#    #+#             */
/*   Updated: 2025/02/05 11:45:37 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"

void	confirmation_handler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("Message received by server\n");
	exit(0);
}

void	send_bit(int pid, int bit)
{
	int	signal_to_send;

	if (bit == 1)
		signal_to_send = SIGUSR2;
	else
		signal_to_send = SIGUSR1;
	if (kill(pid, signal_to_send) == -1)
	{
		ft_printf("Error: Failed to send signal\n");
		exit(1);
	}
	usleep(100);
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		send_bit(pid, (c >> i) & 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./client <pid> <message>\033[0m\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	if (signal(SIGUSR1, confirmation_handler) == SIG_ERR)
	{
		ft_printf("Error: Failed to set up signal handler\n");
		return (1);
	}
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid, '\0');
	pause();
	return (0);
}
