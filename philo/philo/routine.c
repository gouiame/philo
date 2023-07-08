/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:58:06 by cgouiame          #+#    #+#             */
/*   Updated: 2023/07/07 18:03:00 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *msg, int id, t_data *data)
{
	pthread_mutex_lock(&(data->mutex));
	printf("%ld %d %s\n", ft_epoch_time() - data->s_time, id, msg);
	pthread_mutex_unlock(&(data->mutex));
}

void	ft_check_status(t_data *data, t_philo *philo)
{
	data->state = 0;
	data->nb_meals = 0;
	while (data->state == 0)
	{
		pthread_mutex_lock(&data->lock_1);
		if (philo->quit == 1)
			philo->info->nb_meals++;
		pthread_mutex_unlock(&data->lock_1);
		ft_check_death(philo);
	}
}

void	ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock_1);
	if (philo->info->nb_meals == philo->info->num_philo)
	{
		usleep(2000);
		pthread_mutex_lock(&philo->info->mutex);
		philo->info->state = 1;
	}
	pthread_mutex_unlock(&philo->info->lock_1);
	pthread_mutex_lock(&philo->info->lock);
	if (ft_epoch_time() >= philo->deadline + 5)
	{
		ft_print("died", philo->id, philo->info);
		pthread_mutex_lock(&philo->info->mutex);
		philo->info->state = 1;
	}
	pthread_mutex_unlock(&philo->info->lock);
}

void	ft_routine(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->num_of_eating || !(philos->info->num_of_eating))
	{
		pthread_mutex_lock(&philos->fork);
		ft_print("has taken a fork", philos->id, philos->info);
		pthread_mutex_lock(philos->s_fork);
		ft_print("has taken a fork", philos->id, philos->info);
		pthread_mutex_lock(&philos->info->lock);
		philos->deadline = ft_epoch_time() + philos->info->time_to_die;
		pthread_mutex_unlock(&philos->info->lock);
		ft_print("is eating", philos->id, philos->info);
		mysleep(philos->info->time_to_eat);
		pthread_mutex_unlock(&philos->fork);
		pthread_mutex_unlock(philos->s_fork);
		ft_print("is sleeping", philos->id, philos->info);
		mysleep(philos->info->time_to_sleep);
		i++;
		ft_print("is thinking", philos->id, philos->info);
	}
}

void	*ft_philo_routine(void *p)
{
	t_philo	*philos;

	philos = p;
	if (!(philos->id % 2))
		usleep(100);
	pthread_mutex_lock(&philos->info->lock_1);
	philos->quit = 0;
	pthread_mutex_unlock(&philos->info->lock_1);
	pthread_mutex_lock(&philos->info->lock);
	philos->deadline = philos->info->s_time + philos->info->time_to_die;
	pthread_mutex_unlock(&philos->info->lock);
	ft_routine(philos);
	pthread_mutex_lock(&philos->info->lock_1);
	philos->quit = 1;
	pthread_mutex_unlock(&philos->info->lock_1);
	return (NULL);
}
