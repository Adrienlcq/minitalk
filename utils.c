/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:34:14 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/03 13:37:41 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		negative;

	i = 0;
	negative = 1;
	result = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = negative * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	if (result < 0 && negative == 1)
		return (-1);
	else if (result < 0 && negative == -1)
		return (0);
	return (result * negative);
}
