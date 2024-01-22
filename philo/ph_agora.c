/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_agora.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:37:50 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 16:31:15 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ph_monitor(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (!philo->info->died)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->info->done >= philo->info->ph_num)
			philo->info->died = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

static void	*ph_supervisor(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (!philo->info->died)
	{
		pthread_mutex_lock(&philo->lock);
		if (ph_gtime() >= philo->tm_to_die && !philo->eating)
			ph_mss(MSS_DIED, philo);
		if (philo->eats == philo->info->eat_goal)
		{
			pthread_mutex_lock(&philo->info->lock);
			philo->info->done++;
			philo->eats++;
			pthread_mutex_unlock(&philo->info->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

static void	*ph_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->tm_to_die = philo->info->tm_die + ph_gtime();
	if (pthread_create(&philo->t1, NULL, &ph_supervisor, (void *)philo))
		return ((void *)1);
	while (philo->info->died == 0)
	{
		ph_act_eat(philo);
		ph_mss(MSS_THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return (NULL);
}

int	ph_agora(t_info *info)
{
	int			i;
	pthread_t	t0;

	info->start_tm = ph_gtime();
	if (info->eat_goal > 0)
		if (pthread_create(&t0, NULL, &ph_monitor, &info->philos[0]))
			return (ph_error(info, ERR_TH));
	i = -1;
	while (++i < info->ph_num)
	{
		if (pthread_create(&info->tid[i], NULL, &ph_routine, &info->philos[i]))
			return (ph_error(info, ERR_TH));
		ph_usleep(1);
	}
	i = -1;
	while (++i < info->ph_num)
		if (pthread_join(info->tid[i], NULL))
			return (ph_error(info, ERR_JOIN));
	if (info->eat_goal > 0)
		if (pthread_join(t0, NULL))
			return (ph_error(info, ERR_JOIN));
	return (0);
}
