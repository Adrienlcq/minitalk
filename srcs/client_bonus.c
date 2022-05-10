/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:34:57 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/06 15:14:24 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_sig;

int	ft_wait_sig(void)
{
	while (g_sig == 0)
		usleep(10);
	if (g_sig == 1)
		g_sig = 0;
	return (1);
}

void	ft_send_bit(char c, pid_t pid)
{
	int	i;

	i = -1;
	while (128 >> ++i)
	{
		usleep(100);
		if ((128 >> i) & c)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				write(2, "Error, signal failed !\n", 24);
				exit(1);
			}
			ft_wait_sig();
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				write(2, "Error, signal failed !\n", 24);
				exit(1);
			}
			ft_wait_sig();
		}
	}
}

void	ft_handler(int sig)
{
	(void)sig;
	g_sig = 1;
}

void	ft_end(int sig)
{
	(void)sig;
	ft_putstr_fd("The message has been received by server\n", 1);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (ac != 3)
	{
		write(2, "Need 1 arg after PID\n", 21);
		return (1);
	}
	if (ft_check_pid(av[1], &pid) == 1)
		return (1);
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_end);
	while (av[2][i] != '\0')
	{
		ft_send_bit(av[2][i], pid);
		i++;
	}
	ft_send_bit('\0', pid);
	return (0);
}
