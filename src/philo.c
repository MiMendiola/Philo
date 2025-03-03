/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:21:26 by mmendiol          #+#    #+#             */
/*   Updated: 2025/03/03 11:53:53 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void show_error(char *error)
{
    printf(RED"%s\n"CLEAR , error);
}

int main(int ac, char *av[])
{
    
    if (ac != 5 && ac != 6)
    {
        show_error("Incorrect usage. Please, correct the input.");
        return (1);
    }
    

    /* Guardamos los argumentos ya convertidos */

    /* Creamos tenedores */

    /* Creamos las estructuras de los philosofos */

    /* Crear hilo monitor */

    /* [Creamos os hilos de los filosofos y el monitor => Empiezan a la vez] <= Es necesario que empeicen a la vez (sincronización) */

    /* ROUTINE y MONITOR_ROUTINE */

    /* Liberar memoria - Eliminar todos */

    return (0);
}


// for (int i = 0; i < philo_count; i++)
//     pthead_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
// pthead_create(&monitor_thread, NULL, monitor_routine, &gloabl_data)
