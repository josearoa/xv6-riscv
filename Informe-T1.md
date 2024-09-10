## Informe realizado por José Aguilera

Implementación de getppid()

La implementación de la syscall getppid() permite obtener el PID del proceso padre del proceso actual. Esto es crucial para el manejo y control de procesos, permitiendo que un proceso hijo obtenga información sobre su jerarquía.

Para lograr esto, se realizaron las siguientes modificaciones:

sysproc.c y syscall.c: Se agregó la función getppid(), que accede a la estructura proc para devolver el ID del proceso padre (parent->pid). La lógica incluye verificaciones básicas para evitar errores.

syscall.h y user.h: Se definió la syscall getppid y su prototipo para que pueda ser invocada desde el espacio de usuario, permitiendo la correcta integración entre kernel y usuario.

usys.pl: Este script se actualizó para generar el código de enlace que conecta las llamadas a getppid() desde el espacio de usuario con su implementación en el kernel. Este script automatiza la creación de trampas de llamada y garantiza la accesibilidad desde cualquier programa de usuario.

Makefile: Se añadió la referencia al archivo yosoytupadre.c, asegurando su compilación junto con el kernel para permitir pruebas automatizadas de la syscall.

yosoytupadre.c: Este programa fue desarrollado específicamente para probar getppid(). Al ejecutarlo, muestra el PID del proceso padre, verificando visualmente que la syscall funcione correctamente. Sirve como una prueba rápida de integración y funcionalidad.

Implementación de getancestor(int)

La syscall getancestor(int) fue diseñada para extender la funcionalidad de getppid(), permitiendo obtener el PID de ancestros de un proceso a diferentes niveles, como el abuelo, bisabuelo, etc. Esto es útil para sistemas que requieren análisis más profundo de la jerarquía de procesos.

Modificaciones realizadas:

proc.c: Se implementó la lógica para recorrer la cadena de procesos padres. La función navega desde el proceso actual hacia atrás en la cadena de procesos, buscando el ancestro especificado por el argumento int. Se añadieron verificaciones para evitar acceder a niveles inexistentes.

syscall.c y sysproc.c: Se añadió la syscall getancestor(), conectando la lógica implementada en proc.c con la interfaz de syscalls, permitiendo que el usuario especifique el nivel de ancestro deseado.

proc.h: Se actualizaron las definiciones necesarias para manejar la estructura de datos y asegurar que getancestor() opere sin errores.

Makefile y yosoytupadre.c: El programa de prueba yosoytupadre.c se amplió para probar getancestor() en diversos escenarios, como obtener el padre, abuelo y otros ancestros. Esto incluyó pruebas de casos límite, como niveles sin ancestros, que deben manejarse devolviendo -1.

Para efectos de orden, no ubique partes del codigo.
El codigo esta comentado en su respectivo archivo!

----------  ----------  ----------  ----------  ----------  ----------  ----------

Durante la implementación, surgieron varios errores y complicaciones, principalmente al integrar las nuevas syscalls con los archivos existentes del kernel. Hubo confusión al determinar la ubicación precisa de cada entrada y definir correctamente las funciones y prototipos en todos los archivos correspondientes (syscall.h, user.h, usys.pl, etc.). Estos errores se solucionaron a través de iteraciones y pruebas constantes, asegurando que cada función estuviera correctamente enlazada y funcional.