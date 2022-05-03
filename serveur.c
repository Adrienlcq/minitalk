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

void    display_pid()
{
    int pid;

    pid = getpid();
    printf("Process ID is : %d\n", pid);
}

void    ft_receive_bit(int sig)
{
    if (sig == SIGUSR1)
        printf("JE SUIS UN 0\n");
    else if (sig == SIGUSR2)
        printf("JE SUIS UN 1\n");
    else
        printf("JE SUIS DE LA MERDE\n");
    return ;
}

int main()
{

    signal(SIGUSR1, ft_receive_bit);
    signal(SIGUSR2, ft_receive_bit);
    display_pid();
    while (1)
        ;
    return (0);
}