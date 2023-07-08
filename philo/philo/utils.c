/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:25:56 by cgouiame          #+#    #+#             */
/*   Updated: 2023/07/07 13:31:22 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long	num;
	int		i;
	int		sign;

	sign = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = ((num * 10) + (str[i] - '0'));
		i++;
	}
	num *= sign;
	if (num < -2147483648 || num > 2147483647)
		return (0);
	return (num);
}

void	mysleep(int mytime)
{
	long	dur;

	dur = ft_epoch_time();
	while (ft_epoch_time() - dur < mytime)
		usleep(mytime);
}

long	ft_epoch_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}
