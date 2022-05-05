/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:34:57 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/05 15:13:28 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int g_sig;

int ft_wait_sig(void)
{
    while (g_sig == 0)
        usleep(10);
    if (g_sig == 1)
        g_sig = 0;
    return (1);
}

int     ft_check_pid(char *str, pid_t *pid)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
        {
            write(2, "Invalid PID\n", 12);
            return (1);
        }
    }
    *pid = ft_atoi(str);
    if (*pid < 1 || *pid > 4194304)
    {
        write(2, "Invalid PID\n", 12);
        return (1);
    }
    return (0);
}

void    ft_send_bit(char c, pid_t pid) // pid_t pid est le pid que je rentre manuellement apres le ./client
{
    int i;

    i = 0;
    while (128 >> i) // un char est code sur 8 bits donc on veut envoyer 8 signaux
    {
        usleep(100);
        if ((128 >> i) & c) // c est compris par l'ordi en binaire | pour comparer le bit le plus a gauche avec 1 | if (1) alors ...
        {
            if (kill(pid, SIGUSR2) == -1) // si kill == -1, n'envoie pas de signal, si kill != -1, envoie SIGUSR2
            {
                write(2, "Error, signal failed !\n", 24);
                exit(1);
            }
            ft_wait_sig();
        }
        else
        {
            if (kill(pid, SIGUSR1) == -1) // si kill == -1, n'envoie pas de signal, si kill != -1, envoie SIGUSR1
            {
               write(2, "Error, signal failed !\n", 24);
               exit(1);
            }
            ft_wait_sig();
        }
        i++;
    }
}

void    ft_handler(int sig)
{
    (void)sig;
    g_sig = 1;
}

void    ft_end(int sig)
{
    (void)sig;
    ft_putstr_fd("The message has been received by server\n", 1);
}

int     main(int ac, char **av)
{
    pid_t   pid;
    int     i;

    i = 0;
    if (ac != 3)
    {
        write(2, "Need 1 arg after PID\n", 21); // 2 = sortie d'erreur
        return (1);
    }
    if (ft_check_pid(av[1], &pid) == 1) // je passe pid (string) et l'adresse de pid puis je recupere pid en int
        return (1);
    signal(SIGUSR1, ft_handler);
    signal(SIGUSR2, ft_end);
    while (av[2][i] != '\0') // tant que la chaine passee en parametre existe
    {
        ft_send_bit(av[2][i], pid); // la fonction travaille sur un caractere de la chaine passee en parametre
        i++;
    }
    ft_send_bit('\0', pid); // \0 en bin = 0000 0000
    return (0);
}