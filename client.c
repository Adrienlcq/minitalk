/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:34:57 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/03 13:50:07 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int     ft_atoi(const char *str);

int     ft_check_pid(pid_t pid)
{
    int     i;

    i = 0;
    if (pid < 1 || pid > 4194304)
    {
        write(2, "Invalid PID\n", 12);
        return (1);
    }
    while (pid)
    {
        if (pid[i] >= 0 && pid[i] <= 9)
            i++;
        else
            return (1);
    }
    return (0);
}

void    ft_send_bit(char c, pid_t pid) // pid_t pid est le pid que je rentre manuellement apres le ./client
{
    int i;

    i = 0;
    while (i < 8) // un char est code sur 8 bits donc on veut envoyer 8 signaux
    {
        if ((c << i) & 1) // char est compris par l'ordi en binaire | pour comparer le bit le plus a gauche avec 1 | if (1) alors ...
        {
            if (kill(pid, SIGUSR2) == -1) // si kill == -1, n'envoie pas de signal, si kill != -1, envoie SIGUSR2
            {
                write(2, "Error, signal failed !\n", 24);
                exit(1);
            }
        }
        else
        {
            if (kill(pid, SIGUSR1) == -1) // si kill == -1, n'envoie pas de signal, si kill != -1, envoie SIGUSR1
            {
               write(2, "Error, signal failed !\n", 24);
               exit(1);
            }
        }
        usleep(200); // suspend l'execution du programme en microsecondes 
        i++;
    }
}

int     main(int ac, char **av)
{
    pid_t   pid;
    int     i;

    i = 0;
    if (ac != 3)
    {
        write(2, "2 arg max\n", 10); // 2 = sortie d'erreur
        return (1);
    }
    pid = ft_atoi(av[1]);
    if (ft_check_pid(pid) == 1)
        return (1);
    while (av[1][i]) // tant que la chaine passee en parametre existe
    {
        ft_send_bit(av[1][i], pid); // la fonction travaille sur un caractere de la chaine passee en parametre
        i++;
    }
    ft_send_bit('\0', pid); // \0 en bin = 0000 0000
    return (0);
}