/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:20:37 by cgouiame          #+#    #+#             */
/*   Updated: 2023/07/07 15:52:37 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (j < ft_strlen(av[i]))
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && av[i][j] != '+')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_store_data(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_of_eating = ft_atoi(av[5]);
	if (ac == 5)
		data->num_of_eating = 0;
}

int	check_args(int ac, char **av, t_data *data)
{
	if (ac != 6 && ac != 5)
		return (0);
	if (check_arg(ac, av))
		return (0);
	ft_store_data(data, ac, av);
	if (data->num_philo < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1
		|| (ac == 6 && data->num_of_eating == 0))
		return (0);
	return (1);
}
