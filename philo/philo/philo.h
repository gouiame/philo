/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:20:47 by cgouiame          #+#    #+#             */
/*   Updated: 2023/07/07 18:02:40 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include   <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eating;
	long			s_time;
	int				nb_meals;
	int				state;
	pthread_mutex_t	lock;
	pthread_mutex_t	lock_1;
	pthread_mutex_t	mutex;
}t_data;

typedef struct s_philo
{
	int				id;
	t_data			*info;
	int				quit;
	long			deadline;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*s_fork;
}t_philo;

void	mysleep(int mytime);
int		ft_atoi(char *str);
int		ft_check_arg(int ac, char **av);
int		ft_check_arg1(char **av);
int		ft_check_arg2(char **av);
int		ft_check_arg3(t_data *data);
void	ft_store_data(t_data *data, int ac, char **av);
long	ft_epoch_time(void);
void	ft_print(char *msg, int id, t_data *data);
void	ft_check_death(t_philo *philo);
void	ft_routine(t_philo *philos);
void	*ft_philo_routine(void *p);
int		ft_atoi(char *arg);
t_data	*ft_parsing(int ac, char **av);
int		ft_strlen(char *str);
int		check_digit(int ac, char **av);
int		check_args(int ac, char **av, t_data *data);
void	ft_check_status(t_data *data, t_philo *philo);

#endif
