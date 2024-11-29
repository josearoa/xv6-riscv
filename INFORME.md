<h1>Descripción General</h1>
<p>
Este cambio introduce un sistema básico de permisos para archivos en xv6, con soporte para modos como solo lectura, lectura/escritura y un estado especial de inmutabilidad. También incluye un programa de prueba para validar las funcionalidades implementadas.
</p>

<h2>Cambios Realizados</h2>

<h3>1. Estructura <code>inode</code></h3>
<p>
Se añadió un nuevo campo: <code>permissions</code>. Este campo almacena el modo del archivo:
</p>
<ul>
  <li><code>0</code>: Sin permisos.</li>
  <li><code>1</code>: Solo lectura.</li>
  <li><code>2</code>: Solo escritura.</li>
  <li><code>3</code>: Lectura y escritura (por defecto).</li>
  <li><code>5</code>: Inmutable.</li>
</ul>

<h3>2. Validaciones de Permisos</h3>
<ul>
  <li>
    <strong>En apertura de archivos (<code>sys_open</code>)</strong>: 
    Se verifican los permisos al intentar abrir un archivo. Por ejemplo, no se permite abrir en modo escritura si el archivo es de solo lectura.
  </li>
  <li>
    <strong>En lectura y escritura (<code>read</code>, <code>write</code>)</strong>: 
    Se bloquean las operaciones que no cumplen con los permisos.
  </li>
</ul>

<h3>3. Nueva Llamada al Sistema: <code>chmod</code></h3>
<p>
Se implementó la función <code>chmod</code> para cambiar los permisos de un archivo:
</p>
<ul>
  <li><strong>Prototipo:</strong> <code>int chmod(char *path, int mode)</code></li>
  <li>Cambia los permisos del archivo especificado en <code>path</code> al modo <code>mode</code>.</li>
  <li>Bloquea cambios si el archivo es inmutable (<code>permissions == 5</code>).</li>
</ul>

<h3>4. Programa de Prueba</h3>
<p>Se creó un programa llamado <code>chmod_test.c</code> que:</p>
<ul>
  <li>Crea un archivo y escribe datos en él.</li>
  <li>Cambia sus permisos a solo lectura y verifica que no se pueda escribir.</li>
  <li>Cambia sus permisos a inmutable y verifica que:
    <ul>
      <li>No se puede escribir en él.</li>
      <li>No se pueden modificar sus permisos.</li>
    </ul>
  </li>
</ul>

<h2>Detalles Técnicos</h2>
<p>Archivos modificados:</p>
<ul>
  <li><code>kernel/fs.h</code>: Añadido el campo <code>permissions</code> al <code>inode</code>.</li>
  <li><code>kernel/fs.c</code>: Inicialización de <code>permissions</code> en <code>ialloc</code>.</li>
  <li><code>kernel/sysfile.c</code>: Validaciones en <code>sys_open</code>.</li>
  <li><code>kernel/file.c</code>: Restricciones de lectura y escritura.</li>
  <li><code>kernel/sysproc.c</code>: Implementación de <code>chmod</code>.</li>
  <li><code>kernel/syscall.c</code>: Registro de la llamada al sistema <code>chmod</code>.</li>
  <li><code>user/chmod.c</code>: Implementación del comando de usuario <code>chmod</code>.</li>
  <li><code>user/chmod_test.c</code>: Pruebas para verificar permisos.</li>
  <li><code>user.h</code> y <code>usys.S</code>: Declaración y enlace de <code>chmod</code>.</li>
</ul>


<h2>Pruebas</h2>
<p>El programa <code>chmod_test.c</code> valida los siguientes casos:</p>
<ul>
  <li>Crear un archivo, escribir en él, y cambiarlo a solo lectura.</li>
  <li>Intentar escribir en un archivo de solo lectura.</li>
  <li>Cambiar un archivo a inmutable y verificar que:
    <ul>
      <li>No se pueda escribir en él.</li>
      <li>No se puedan modificar sus permisos.</li>
    </ul>
  </li>
</ul>

<h3>Ejemplo de Salida del Programa de Prueba</h3>
<pre><code>$ chmod_test
Pruebas completadas
</code></pre>
