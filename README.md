<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/philosopherse.png" alt="Philosophers Badge"/>
</p>

<h1 align="center">🍝 Philosophers</h1>

<p align="center">
  <strong>I never thought philosophy would be so deadly</strong><br>
  Simulacion del problema clasico de los filosofos comensales usando hilos y mutexes
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Threads-pthreads-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/School-42_Madrid-black?style=for-the-badge&logo=42" />
  <a href="Documentation/en/README.en.md">
    <img src="https://img.shields.io/badge/Read_in-English-purple?style=for-the-badge" alt="Read in English" />
  </a>
</p>

---

## 📋 Tabla de Contenidos

- [Sobre el Proyecto](#-sobre-el-proyecto)
- [Caracteristicas](#-caracteristicas)
- [Requisitos](#-requisitos)
- [Instalacion](#-instalacion)
- [Uso](#-uso)
- [Reglas de la Simulacion](#-reglas-de-la-simulacion)
- [Sincronizacion](#-sincronizacion)
- [Caracteristicas Tecnicas](#-caracteristicas-tecnicas)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Recursos](#-recursos)

---

## 🎯 Sobre el Proyecto

**Philosophers** es un proyecto del cursus de 42 que implementa el problema clasico de los filosofos comensales. Varios filosofos se sientan alrededor de una mesa, alternando entre comer, dormir y pensar. Para comer, cada filosofo necesita tomar dos tenedores compartidos con sus vecinos.

El objetivo es comprender:

- **Threads**: Crear y coordinar hilos con `pthread`.
- **Mutexes**: Proteger recursos compartidos.
- **Data races**: Evitar lecturas y escrituras inseguras.
- **Deadlocks**: Disenar una estrategia para que los filosofos no se bloqueen entre si.
- **Timing**: Controlar tiempos con precision suficiente para una simulacion concurrente.

---

## ✨ Caracteristicas

### Funcionalidades Core

- ✅ Un hilo por filosofo
- ✅ Hilo monitor para detectar muertes
- ✅ Un mutex por tenedor
- ✅ Mutexes para escritura y estado global
- ✅ Sincronizacion de inicio para todos los hilos
- ✅ Caso especial para un solo filosofo
- ✅ Opcion de numero maximo de comidas
- ✅ Finalizacion limpia de hilos y mutexes

### Validacion de Argumentos

- ✅ Solo numeros positivos
- ✅ Rechazo de valores negativos
- ✅ Rechazo de caracteres no numericos
- ✅ Proteccion contra valores mayores que `INT_MAX`
- ✅ Comprobacion del numero correcto de argumentos

### Gestion de Tiempo

- ✅ Timestamps relativos al inicio de la simulacion
- ✅ Conversion entre segundos, milisegundos y microsegundos
- ✅ `precise_usleep` para dormir sin perder de vista el final de la simulacion
- ✅ Monitorizacion continua de `time_to_die`

---

## 🛠️ Requisitos

- **Sistema Operativo**: Linux o macOS
- **Compilador**: `cc`, `gcc` o `clang`
- **Make**
- **Librerias**:
  - `pthread`
  - `sys/time`

### Instalacion de dependencias

**En Ubuntu/Debian:**

```bash
sudo apt-get update
sudo apt-get install build-essential make
```

**En macOS:**

```bash
xcode-select --install
```

---

## 📦 Instalacion

```bash
# Clonar el repositorio
git clone https://github.com/MiMendiola/Philo.git
cd Philo

# Compilar el proyecto
make

# Ejecutar una simulacion
./philo 5 800 200 200
```

### Comandos Make disponibles

```bash
make        # Compila philo
make clean  # Elimina archivos objeto
make fclean # Elimina archivos objeto y ejecutable
make re     # Recompila desde cero
```

---

## 🚀 Uso

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Argumentos

| Argumento | Descripcion |
| --- | --- |
| `number_of_philosophers` | Numero de filosofos y tenedores |
| `time_to_die` | Tiempo maximo sin comer antes de morir, en ms |
| `time_to_eat` | Tiempo que tarda un filosofo en comer, en ms |
| `time_to_sleep` | Tiempo que tarda un filosofo en dormir, en ms |
| `number_of_times_each_philosopher_must_eat` | Opcional. Si todos comen esta cantidad, termina la simulacion |

### Ejemplos

```bash
./philo 1 800 200 200
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
```

### Formato de salida

```text
0     1 has taken a fork
0     1 has taken a fork
0     1 is eating
200   1 is sleeping
200   2 has taken a fork
```

Cada linea muestra:

```text
timestamp_en_ms id_del_filosofo accion
```

---

## 🍽️ Reglas de la Simulacion

Cada filosofo repite este ciclo:

```text
tomar tenedor izquierdo/derecho
tomar el otro tenedor
comer
soltar ambos tenedores
dormir
pensar
```

La simulacion termina cuando:

- Un filosofo supera `time_to_die` sin comer.
- Todos los filosofos alcanzan el numero de comidas requerido, si se paso el quinto argumento.

### Caso de un solo filosofo

Con un unico filosofo solo existe un tenedor. El programa lanza una rutina especial donde el filosofo toma un tenedor y, al no poder tomar el segundo, termina muriendo cuando se cumple `time_to_die`.

---

## 🔐 Sincronizacion

### Estrategia de Tenedores

Cada tenedor es un `pthread_mutex_t`. Para reducir el riesgo de deadlock, el orden de asignacion de tenedores cambia segun el identificador del filosofo:

```text
Filosofos impares:
  left_fork  -> siguiente tenedor
  right_fork -> tenedor actual

Filosofos pares:
  left_fork  -> tenedor actual
  right_fork -> siguiente tenedor
```

### Inicio Coordinado

Los hilos esperan a que la mesa marque `threads_ready`. Asi se evita que unos filosofos empiecen mucho antes que otros.

```text
crear hilos de filosofos
crear hilo monitor
marcar threads_ready = true
todos empiezan la simulacion
```

### Monitor

El monitor espera a que todos los hilos esten corriendo y comprueba repetidamente si algun filosofo ha muerto:

```text
mientras la simulacion no termine:
  para cada filosofo:
    si tiempo_actual - ultima_comida > time_to_die:
      marcar fin de simulacion
      imprimir muerte
```

---

## 🔬 Caracteristicas Tecnicas

### Estructuras Principales

```c
typedef struct s_fork
{
    int             id;
    pthread_mutex_t fork;
}   t_fork;

typedef struct s_philo
{
    int             id;
    pthread_t       thread_id;
    int             meals;
    bool            full;
    long            last_meal;
    t_fork          *left_fork;
    t_fork          *right_fork;
    pthread_mutex_t mutex;
    t_table         *table;
}   t_philo;

typedef struct s_table
{
    int             philo_nbr;
    long            time_to_die_ms;
    long            time_to_eat_ms;
    long            time_to_sleep_ms;
    int             meals_todo;
    long            start_simulation;
    bool            end_simulation;
    bool            threads_ready;
    long            threads_running;
    pthread_t       monitor;
    pthread_mutex_t mutex_table;
    pthread_mutex_t mutex_write;
    t_fork          *forks;
    t_philo         *philos;
}   t_table;
```

### Funciones Clave

```c
int     init_table(t_table *table, char *av[]);
void    init_data(t_table *table);
void    simulation_start(t_table *table);
void    *simulation_dinner(void *data);
void    *simulation_monitor(void *data);
void    eat(t_philo *philo);
void    thinking(t_philo *philo, bool presimulation);
```

### Proteccion de Datos

- `mutex_table` protege el estado global de la simulacion.
- `mutex_write` evita salidas mezcladas entre hilos.
- Cada filosofo tiene su propio mutex para `last_meal` y `full`.
- Cada tenedor tiene su propio mutex.

---

## 📁 Estructura del Proyecto

```text
Philo/
├── Makefile
├── README.md
├── includes/
│   └── philo.h              # Estructuras, enums y prototipos
└── src/
    ├── actions.c            # Comer y pensar
    ├── getters_setters.c    # Acceso protegido a datos compartidos
    ├── handlers.c           # Wrappers de errores para mutex/thread
    ├── init.c               # Inicializacion de mesa, filosofos y tenedores
    ├── philo.c              # main, errores y limpieza
    ├── philo_lib.c          # Funciones auxiliares tipo libft
    ├── philo_utils.c        # Parsing, tiempo, sleep y logs
    ├── simulation.c         # Rutinas de filosofos y monitor
    └── syncro.c             # Sincronizacion de inicio y estado
```

---

## 📚 Recursos

### Concurrencia

- [pthread_create(3)](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_mutex_lock(3)](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [pthread_join(3)](https://man7.org/linux/man-pages/man3/pthread_join.3.html)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### Tiempo

- [gettimeofday(2)](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [usleep(3)](https://man7.org/linux/man-pages/man3/usleep.3.html)

---

## 🎓 Aprendizajes Clave

Este proyecto permite practicar:

- **Programacion concurrente** con hilos.
- **Sincronizacion** con mutexes.
- **Prevencion de deadlocks** mediante orden de toma de recursos.
- **Proteccion de estado compartido** para evitar data races.
- **Medicion de tiempo** en simulaciones sensibles al milisegundo.
- **Limpieza de recursos** al terminar una simulacion multihilo.

---

## 👥 Autores

- **Miguel** - [@MiMendiola](https://github.com/MiMendiola)

---

## 📄 Licencia

Este proyecto es parte del cursus de 42 Madrid y esta sujeto a sus normas academicas.

---

<p align="center">
  <sub>Desarrollado con C y pthreads en 42 Madrid</sub>
</p>
