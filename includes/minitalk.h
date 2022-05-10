/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:46:02 by adlecler          #+#    #+#             */
/*   Updated: 2022/05/06 17:15:13 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_buffer
{
	char	buffer[200];
	int		i_buff;
	int		nb_bit;
	int		max_bit;
	pid_t	pid_client;
}			t_buffer;

void	t_send_bit(char c, pid_t pid);
void	t_handler(int sig);
void	ft_end(int sig);
void	ft_init_struct(void);
void	t_print(void);
void	t_add_bit(int bit);
void	ft_display_pid(void);
void	ft_receive_bit(int sig, siginfo_t *si, void *arg);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_wait_sig(void);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_check_pid(char *str, pid_t *pid);

#endif