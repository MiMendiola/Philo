#include "../includes/philo.h"

void    mutex_error_handler(int status, t_opscode code)
{
    if (status == 0)
        return ;
    if (status == EINVAL && (code == LOCK || code == UNLOCK || code == DESTROY))
        printf("Valor especificado en el mutex es invalido");
    else if (status == EINVAL && code == INIT)
        printf("Valor especificado en el attr es invalido");
    else if (status == EBUSY)
        printf("Mutex esta locked");
    else if (status == EPERM)
        printf("Intentar desbloquear un mutex no bloqueado");
    else if (status == EDEADLK)
        printf("Lockear un mutex que ya bloqueaste tu mismo");
    else if (status == ENOMEM)
        printf("No hay memoria para inicializar el mutex");
}

void    mutex_handler(pthread_mutex_t *mutex, t_opscode code)
{
    if (code == LOCK)
        mutex_error_handler(pthread_mutex_lock(mutex), code);
    else if (code == UNLOCK)
        mutex_error_handler(pthread_mutex_unlock(mutex), code);
    else if (code == INIT)
        mutex_error_handler(pthread_mutex_init(mutex, NULL), code);
    else if (code == DESTROY)
        mutex_error_handler(pthread_mutex_destroy(mutex), code);
    else
        printf("error code mutex (nose si esta linea es necesaria, creo que no por eso este mensaje)");
}

void    thread_error_handler(int status, t_opscode code)
{
    if (status == 0)
        return ;
    if (status == EINVAL && (code == JOIN || code == DETACH))
        printf("Valor especificado en el hilo es invalido");
    else if (status == EINVAL && code == CREATE)
        printf("Valor especificado en el attr es invalido");
    else if (status == EAGAIN)
        printf("Recursos insuficientes para crear otro hilo");
    else if (status == EPERM)
        printf("Permiso denegado");
    else if (status == EDEADLK)
        printf("Deadlock detectado o el hilo especificado es el mismo que el hilo que realiza la llamada");
    else if (status == ESRCH)
        printf("El hilo especificado no existe");
}

void    thread_handler(pthread_t *thread, void *(*foo)(void *), void *data, t_opscode code)
{
    if (code == CREATE)
        thread_error_handler(pthread_create(thread, NULL, foo, data), code);
    else if (code == JOIN) 
        thread_error_handler(pthread_join(thread, NULL), code);
    else if (code == DETACH)
        thread_error_handler(pthread_detach(thread), code);
    else
        printf("error code hilos (nose si esta linea es necesaria, creo que no por eso este mensaje)");
}