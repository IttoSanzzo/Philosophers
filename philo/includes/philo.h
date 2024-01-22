/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:01:56 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 16:31:53 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

// includes
# include "ph_includes.h"
# include "ph_macros.h"
# include "ph_structs.h"

// ph_inits.c
int			ph_inits(t_info *info, int ac, char **av);

// ph_agora.c
int			ph_agora(t_info *info);

// ph_loner.c
int			ph_loner(t_info *info);

// ph_acts.c
void		ph_act_eat(t_philo *philo);

// ph_exit.c
int			ph_error(t_info *info, char *mss);
void		ph_free_all(t_info *info);

// ph_extra.c
int			ph_check_info(char **argv);
uint64_t	ph_gtime(void);
int			ph_usleep(useconds_t time);
void		ph_mss(char *s, t_philo *philo);

// ft_utils.c
int			ft_atoi(const char *nptr);
void		ft_putendl_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);

#endif