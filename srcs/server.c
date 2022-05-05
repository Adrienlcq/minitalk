/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:24:42 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/05 17:23:15 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_buffer    g_buffer;

void    ft_init_struct(void)
{
    ft_bzero(g_buffer.buffer, 200);
    g_buffer.i_buff = 0;
    g_buffer.nb_bit = 0;
    g_buffer.max_bit = 128;
}

void	ft_print(void)
{
	if (g_buffer.buffer[g_buffer.i_buff - 1] == '\0')
	{
		write(1, g_buffer.buffer, ft_strlen(g_buffer.buffer));
		write(1, "\n", 1);
		ft_init_struct();
        if (kill(g_buffer.pid_client, SIGUSR2) == -1)
        {
            ft_putstr_fd("Signal failed\n", 2);
            exit(1);
        }
	}
}

void	ft_add_bit(int bit)
{
	g_buffer.max_bit = 128 >> g_buffer.nb_bit;
	if (bit == 1)
		g_buffer.buffer[g_buffer.i_buff] = g_buffer.buffer[g_buffer.i_buff]
			| g_buffer.max_bit;
	g_buffer.nb_bit++;
	if (g_buffer.nb_bit == 8)
	{
		g_buffer.nb_bit = 0;
		g_buffer.i_buff++;
		if (g_buffer.i_buff == 199)
		{
			write(1, g_buffer.buffer, ft_strlen(g_buffer.buffer));
			ft_init_struct();
		}
		else
			ft_print();
	}
	if (kill(g_buffer.pid_client, SIGUSR1) != 0)
	{
		ft_putstr_fd("Error\nUnable to send signal to client\n", 2);
		exit(0);
	}
}

void    ft_display_pid(void)
{
    int pid;

    pid = getpid();
    write(1, "Process ID is : ", 8);
    ft_putnbr_fd(pid, 1);
    write(1, "\n", 1);
}

void    ft_receive_bit(int sig, siginfo_t *si, void *arg)
{
    (void)arg;
    (void)si;
    g_buffer.pid_client = si->si_pid;
    if (sig == SIGUSR1)
        ft_add_bit(0);
    else if (sig == SIGUSR2)
        ft_add_bit(1);
    else
        write(2, "Bad signal\n", 11);
}

int main()
{
    struct  sigaction   sa;

    ft_init_struct();
    ft_display_pid();
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &ft_receive_bit;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (42)
        usleep(1);
    return (0);
}