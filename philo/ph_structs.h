/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:01:56 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 14:37:01 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_STRUCTS_H
# define PH_STRUCTS_H 

// Structs	

struct	s_info;

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	int				eats;
	int				eating;
	uint64_t		tm_to_die;
	pthread_t		t1;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_info
{
	int				ph_num;
	uint64_t		tm_die;
	uint64_t		tm_eat;
	uint64_t		tm_slp;
	int				eat_goal;
	int				died;
	int				done;
	uint64_t		start_tm;
	t_philo			*philos;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_info;

#endif