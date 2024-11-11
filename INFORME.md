# Informe Tarea 3 - José Aguilera
Este informe describe la implementación de un sistema de protección de memoria en el sistema operativo xv6, el cual permite marcar regiones de memoria como solo lectura. Para lograrlo, se crearon dos funciones principales: mprotect y munprotect. 

Cada una de estas funciones recibe una dirección y un número de páginas a modificar. La función walk() de vm.c se utiliza para recorrer la tabla de páginas del proceso y acceder a las entradas de página correspondientes (PTE). La lógica es la siguiente:
<ul>
<li>Protección (mprotect): Desactiva el bit de escritura (PTE_W) en cada entrada de página, convirtiéndola en solo lectura.</li>
<li>Desprotección (munprotect): Vuelve a activar el bit de escritura (PTE_W), restaurando el permiso para modificar la página.</li>
</ul>

### Archivos Modificados

<ul>
<li>vm.c: Se añadieron las funciones mprotect y munprotect. Ambas funciones recorren las entradas de la tabla de páginas, ajustando las banderas de protección (quitando el permiso de escritura con PTE_W para mprotect y restaurándolo en munprotect). 
Estas funciones permiten modificar permisos de escritura a nivel de página.</li>

<li>syscall.c y syscall.h: Se agregaron las llamadas al sistema para mprotect y munprotect, lo que permite que los procesos de usuario accedan a estas funcionalidades. 
En syscall.c, se mapean las funciones a sus respectivos índices, permitiendo que el sistema los reconozca como nuevas llamadas al sistema.</li>

<li>user.h: Se declararon las firmas de mprotect y munprotect para su uso en programas de usuario. 
Esto facilita la interacción con la memoria protegida desde aplicaciones en espacio de usuario.</li>

<li>defs.h: Se añadieron las declaraciones de mprotect y munprotect en este archivo de cabecera para que puedan ser referenciadas en varias partes del kernel.</li>

<li>trap.c: Se realizaron modificaciones para manejar las excepciones que ocurren cuando un proceso intenta escribir en una página protegida. 
Esto asegura que los intentos de escritura en memoria de solo lectura generen una falla de protección que puede ser gestionada o hacer que el proceso falle, mejorando la seguridad.</li>

<li>protect_test.c: Se implementó la función protect_test como un caso de prueba en el espacio de usuario. 
Esta función solicita una página de memoria mediante sbrk, aplica la protección con mprotect, y luego intenta escribir en la memoria protegida para verificar si la protección funciona correctamente.</li>
</ul>

En primer lugar, para poder tener un correcto desarrollo de la tarea, trate de basarme en trabajos realizados en internet basados en mprotect y munprotect. 
El siguiente fue uno de los trabajos en los que trate de guiarme, sin embargo, las modificaciones al kernel de xv6 eran muy significativas dado que agregaban distintos archivos en donde mencionaban distintas declaraciones de codigo
<a>https://github.com/Mohamed-Shafei20/xv6-projects</a>. Eso me llevo a incurrir en muchos errores en torno a las declaraciones de las funciones y/o los structs.

El mensaje que obtuve en base al protect_test creado fue el siguiente, sin embargo cambiaba a medida que lo ejecutaba:

    usertrap(): unexpected scause 0xf pid=3
            sepc=0x54 stval=0x4000

En algunos casos, obtuve lo siguiente:

    exec protect_test failed

Supuse que este error ocurría si las páginas de memoria no se protegían correctamente con mprotect, lo que impedía que la prueba funcionara.

Finalmente, cometí errores al modificar las instrucciones #include en vm.c, lo que generó problemas al compilar. 
Al modificar funciones como myproc(), terminé afectando el código de forma que decidí borrar la rama y crearla de nuevo para continuar con la implementación.
