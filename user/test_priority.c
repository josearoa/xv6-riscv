#include "kernel/types.h"
#include "user/user.h"

int main(void) {
  int i;

  // Crear 20 procesos hijos
  for (i = 0; i < 20; i++) {
    if (fork() == 0) {
      // Proceso hijo
      printf("Ejecutando proceso hijo %d\n", getpid());
      sleep(10);  // Simular algún trabajo con sleep
      exit(0);
    }
  }

  // Esperar a que todos los hijos terminen
  for (i = 0; i < 20; i++) {
    wait(0);
  }

  exit(0);
}
