/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:24:42 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/03 13:39:20 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void    ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
int     ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);

typedef struct s_buffer
{
    char    buffer[200];
    int     i_buff;
    int     nb_bit;
    int     max_bit;
    pid_t   pid_client;
}               t_buffer;

t_buffer    g_buffer;

void    ft_init_struct(void)
{
    memset(g_buffer.buffer, 0, 200);
    g_buffer.i_buff = 0;
    g_buffer.nb_bit = 0;
    g_buffer.max_bit = 128;

}

void    ft_print_and_reset_buffer(void)
{
    write(1, g_buffer.buffer, ft_strlen(g_buffer.buffer) + 1);
    ft_init_struct();
}

/*void    ft_add_bit(int bit)
{
    g_buffer.max_bit = 128 >> g_buffer.nb_bit;
    int c;
    if (bit == 1)
    {
        printf("1\n");
        printf("Valeur de i_buff : %d\n", g_buffer.i_buff);
        g_buffer.buffer[g_buffer.i_buff] = g_buffer.buffer[g_buffer.i_buff] | g_buffer.max_bit;
    }
    else 
    {    
        printf("0\n");
        printf("Valeur de i_buff : %d\n", g_buffer.i_buff);
    }
    c = g_buffer.buffer[g_buffer.i_buff] - '0';
    printf("Valeur de CCC: %d\n", c);
    if (g_buffer.nb_bit == 7)
    {
        if (g_buffer.buffer[g_buffer.i_buff] == '\0')
        {
            ft_print_and_reset_buffer();
            printf("Je rentre pas ici\n");
        }
        g_buffer.i_buff++;
        //write(1, &g_buffer.buffer[g_buffer.i_buff - 1], 1);
        printf("Valeur de g_buffer.buffer : %s\n", g_buffer.buffer);
        //ft_init_struct();
        g_buffer.nb_bit = -1;
    }
    g_buffer.nb_bit++;
}*/

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

void    display_pid()
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
    {
        //printf("0\n");
        ft_add_bit(0);
    }
    else if (sig == SIGUSR2)
    {
        //printf("1\n");
        ft_add_bit(1);
    }
    else
        write(2, "Bad signal\n", 11);
}

int main()
{
    struct  sigaction   sa;

    ft_init_struct();
    display_pid();
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &ft_receive_bit;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (42)
        usleep(1);
    return (0);
}