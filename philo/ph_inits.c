/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:37:57 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 14:37:59 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_init_info(t_info *info, int ac, char **av)
{
	info->ph_num = (int)ft_atoi(av[1]);
	info->tm_die = (uint64_t)ft_atoi(av[2]);
	info->tm_eat = (uint64_t)ft_atoi(av[3]);
	info->tm_slp = (uint64_t)ft_atoi(av[4]);
	if (ac == 6)
		info->eat_goal = (int)ft_atoi(av[5]);
	else
		info->eat_goal = -1;
	if ((info->ph_num <= 0 || info->ph_num > 200) || (int)info->tm_die < 0
		|| (int)info->tm_eat < 0 || (int)info->tm_slp < 0)
		return (ph_error(NULL, ERR_IN_2));
	info->died = 0;
	info->done = 0;
	pthread_mutex_init(&info->lock, NULL);
	pthread_mutex_init(&info->write, NULL);
	return (0);
}

static int	ph_init_allocs(t_info *info)
{
	info->tid = (pthread_t *)malloc(info->ph_num * sizeof(pthread_t));
	if (!info->tid)
		return (ph_error(info, ERR_ALLOC_1));
	info->forks = (pthread_mutex_t *)malloc(info->ph_num
			* sizeof(pthread_mutex_t));
	if (!info->forks)
		return (ph_error(info, ERR_ALLOC_2));
	info->philos = (t_philo *)malloc(info->ph_num * sizeof(t_philo));
	if (!info->philos)
		return (ph_error(info, ERR_ALLOC_3));
	return (0);
}

static void	ph_init_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->ph_num)
		pthread_mutex_init(&info->forks[i], NULL);
	info->philos[0].l_fork = &info->forks[0];
	info->philos[0].r_fork = &info->forks[info->ph_num - 1];
	i = 0;
	while (++i < info->ph_num)
	{
		info->philos[i].l_fork = &info->forks[i];
		info->philos[i].r_fork = &info->forks[i - 1];
	}
}

static void	ph_init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->ph_num)
	{
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		info->philos[i].eats = 0;
		info->philos[i].eating = 0;
		info->philos[i].tm_to_die = info->tm_die;
		pthread_mutex_init(&info->philos[i].lock, NULL);
	}
}

int	ph_inits(t_info *info, int ac, char **av)
{
	if (ph_init_info(info, ac, av))
		return (1);
	if (ph_init_allocs(info))
		return (1);
	ph_init_forks(info);
	ph_init_philos(info);
	return (0);
}
