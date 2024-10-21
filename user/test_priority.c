#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(void) {
    int n;
    int pid;

    // Crear 20 procesos hijos.
    for(n = 0; n < 20; n++) {
        pid = fork();
        if(pid < 0) {
            printf("Error al hacer fork\n");
            exit(1);
        }
        if(pid == 0) {
            sleep(10 * (n + 1)); // Simula trabajo del proceso hijo.
            // Establecer prioridad y boost para cada proceso hijo.
            setpriority(getpid(), 20 - n); // Prioridades decrecientes.
            setboost(getpid(), n % 2 == 0 ? 1 : -1); // Boost alternante.

            printf("Ejecutando proceso %d con PID %d, prioridad %d y boost %d\n",
                   n, getpid(), 20 - n, n % 2 == 0 ? 1 : -1);
            exit(0); // Termina el proceso hijo.
        }
    }

    // Esperar a que todos los procesos hijos terminen.
    for(n = 0; n < 20; n++) {
        wait(0);
    }

    exit(0); // Termina el proceso padre.
}
