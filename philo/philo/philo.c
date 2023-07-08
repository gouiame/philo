/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:15:27 by cgouiame          #+#    #+#             */
/*   Updated: 2023/07/07 18:02:36 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].info = data;
		philo[i].deadline = philo[i].info->s_time + philo[i].info->time_to_die;
		if (i == data->num_philo - 1)
			philo[i].s_fork = &philo[0].fork;
		else
			philo[i].s_fork = &philo[i + 1].fork;
		i++;
	}
}

void	ft_init_philo_forks(t_philo *philo, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		i++;
	}
}

void	ft_create_and_detach_threads(t_philo *philo, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_philo_routine, &philo[i]))
		{
			free (philo);
			return ;
		}
		pthread_detach(philo[i].thread);
		i++;
	}
}

t_philo	*ft_create_philo(t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->num_philo);
	if (philo == NULL)
		return (NULL);
	ft_init_philo_forks(philo, data->num_philo);
	data->s_time = ft_epoch_time();
	ft_set_philo(data, philo);
	ft_create_and_detach_threads(philo, data->num_philo);
	return (philo);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (check_args(ac, av, data) == 0)
		return (printf("Error\n"), free(data), 1);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->lock_1, NULL);
	philo = ft_create_philo(data);
	if (philo == NULL)
		return (1);
	ft_check_status(data, philo);
	pthread_mutex_destroy(&data->mutex);
	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_destroy(&philo[i].fork);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->lock_1);
	free(philo);
	return (0);
}
