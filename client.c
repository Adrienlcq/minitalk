/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:34:57 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/02 19:22:03 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "../libft/libft.h"

void    ft_send_bit(char c, pid_t pid) // str c'est av[1]
{
    int i;

    i = 0;
    while (i < 8) // un char est code sur 8 bits
    {
        if ((c << i) & 1) // char est compris par l'ordi en binaire | pour comparer le bit le plus a gauche avec 1 | if (1) alors ...
        {
            if (kill(pid, SIGUSR2) == -1) // envoie SIGUSR2
               ft_putstr_fd("Error, signal failed !\n", 2); 
        }
        else
        {
            if (kill(pid, SIGUSR1) == -1) // envoie SIGUSR1
               ft_putstr_fd("Error, signal failed !\n", 2);
        }
        usleep(200);
        i++;
    }
}

int     main(int ac, char **av)
{
    pid_t   pid;

    if (ac != 3)
    {
        ft_putstr_fd("2 arg max\n", 2); // 2 = sortie d'erreur
        return (1);
    }
    /* if (ft_atoi(av[1] < 1 || ft_atoi(av[1] > 4194304)))
    {
        ft_putstr_fd("Invalid PID\n", 2);
        return (1);
    } */
    pid = ft_atoi(av[1]);
    int i;

    i = 0;
    while (av[1][i]) // tant que la chaine passee en parametre existe
    {
        ft_send_bit(av[1][i], pid); // la fonction travaille sur un caractere de la chaine passee en parametre
        i++;
    }
    ft_send_bit('\0', pid); // \0 en bin = 0000 0000
}