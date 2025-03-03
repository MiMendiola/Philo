/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:01:44 by mmendiol          #+#    #+#             */
/*   Updated: 2025/03/03 11:50:28 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_list(t_philo **stack)
{
	t_philo	*aux;

	while (*stack)
	{
		aux = (*stack)->next;
		pthread_mutex_destroy(&aux->lock);
		free(*stack);
		*stack = aux;
	}
	free(stack);
}

t_philo	*last_node(t_philo *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_philo	*new_node(int id, char *av[])
{
	t_philo	*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
//	pthread_mutex_init(&philo->lock, NULL);
	philo->prev = NULL;
	philo->next = NULL;
	philo->timeToDieMs = ft_atoi(av[2]);
	philo->timeToEatMs = ft_atoi(av[3]);
	philo->timeToSleepMs = ft_atoi(av[4]);
	if (av[5])
		philo->maxTimesEaten = ft_atoi(av[5]);
	else
		philo->maxTimesEaten = INT_MAX;
	if ((philo->timeToDieMs == INT_MAX + 1) || (philo->timeToEatMs == INT_MAX + 1) || (philo->timeToSleepMs == INT_MAX + 1) || (philo->maxTimesEaten == INT_MAX + 1))
		return(free(philo), NULL);
	return (philo);
}

void	add_node_back(t_philo **stack, t_philo *new)
{
	t_philo	*aux;

	aux = last_node(*stack);
	if (*stack != NULL)
	{
		new->prev = aux;
		new->next = NULL;
		aux->next = new;
	}
	else
		*stack = new;
}

long	atol_philo(char *str)
{
    long n = 0;
    int i = 0;

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+' || str[i] == '-')
        if (str[i++] == '-') 
            return (printf("Only positive numbers allowed\n"), -1);
    if (str[i] < '0' ||  str[i] > '9')
        return (printf("Only numbers allowed\n"), -1);
    while (str[i] >= '0' && str[i] <= '9')
    {
        n = n * 10 + (str[i++] - '0');
        if (n > INT_MAX)
            return (printf("Number is too big\n"), -1);
    }
    return (n);
}
