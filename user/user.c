int getancestor(int n) {
    // Llama a la syscall 'getancestor' pasando 'n' como argumento.
    // Esta línea envía la solicitud al kernel para obtener el ancestro 'n'.
    return syscall(SYS_getancestor, n);
}
