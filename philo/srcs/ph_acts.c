/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_acts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:38:17 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 14:38:18 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ph_mss(MSS_FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	ph_mss(MSS_FORK, philo);
}

static void	ph_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ph_mss(MSS_SLEEPING, philo);
	ph_usleep(philo->info->tm_slp);
}

void	ph_act_eat(t_philo *philo)
{
	ph_take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->tm_to_die = ph_gtime() + philo->info->tm_die;
	ph_mss(MSS_EATING, philo);
	philo->eats++;
	ph_usleep(philo->info->tm_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	ph_drop_forks(philo);
}
