/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:34:57 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/05 15:13:28 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	if (n != 0)
	{
		while (i < n)
		{
			str[i] = '\0';
			i++;
		}
	}
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

