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

void    ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
int     ft_strlen(char *str);

typedef struct s_buffer
{
    char    buffer[200];
    int     i_buff;
    int     nb_bit;
    int     max_bit;
}               t_buffer;

t_buffer    g_buffer;

void    ft_init_struct(void)
{
    ft_bzero(g_buffer.buffer, 200);
    g_buffer.i_buff = 0;
    g_buffer.nb_bit = 0;
    g_buffer.max_bit = 128;
}

void    ft_print_and_reset_buffer(void)
{
    write(1, g_buffer.buffer, ft_strlen(g_buffer.buffer));
    ft_init_struct();
}

void    ft_add_bit(int bit)
{
    if (bit == 1)
    {
        g_buffer.buffer[g_buffer.i_buff] = g_buffer.buffer[g_buffer.i_buff] + (1 << g_buffer.nb_bit);
    }
    if (g_buffer.nb_bit == 7)
    {
        if (g_buffer.buffer[g_buffer.i_buff] == '\0')
        {
            ft_print_and_reset_buffer();
            printf("Je rentre pas ici\n");
        }
        g_buffer.i_buff++;
    }
    g_buffer.nb_bit++;
}

void    display_pid()
{
    int pid;

    pid = getpid();
    write(1, "PID IS: ", 8);
    ft_putnbr_fd(pid, 1);
    write(1, "\n", 1);
}

void    ft_receive_bit(int sig)
{
    if (sig == SIGUSR1)
        ft_add_bit(0);
    else if (sig == SIGUSR2)
        ft_add_bit(1);
    else
        write(2, "Bad signal\n", 11);
}

int main()
{
    ft_init_struct();
    signal(SIGUSR1, ft_receive_bit);
    signal(SIGUSR2, ft_receive_bit);
    display_pid();
    while (1)
        pause();
    return (0);
}