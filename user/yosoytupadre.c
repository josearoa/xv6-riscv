#include "kernel/types.h"
#include "user/user.h"

int main() {
    int ppid = getppid();
    printf("El PID del proceso padre es: %d\n", ppid);
    exit(0);
}
