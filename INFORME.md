Trabajo realizado por José Aguilera

Para instalar de manera correcta xv6-riscv en mi PC, debí seguir los siguientes pasos:

En primer lugar, y luego de muchos intentos fallidos con WSL, tuve que instalar Oracle VM Virtualbox y instalar una versión de Ubuntu en mi Virtualbox.

Luego, en la terminal tuve que correr los siguientes comandos:

sudo apt update && sudo apt upgrade -y

sudo apt install -y build-essential gdb gcc-riscv64-unknown-elf qemu-system-misc git ninja-build

Luego, clonar los repos de xv6 y el toolchain

git clone https://github.com/josearoa/xv6-riscv.git

git clone https://github.com/riscv/riscv-gnu-toolchain

Para configurar el toolchain, tuve que realizar lo siguiente:

Instalar las siguientes dependencias

sudo apt install -y autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

cd riscv-gnu-toolchain

./configure --prefix=/opt/riscv 

sudo make

Y finalmente, configurarlo en el PATH de mi VM:

nano ~/.bashrc

y agregar: export PATH=/opt/riscv/bin:$PATH

Finalmente, en la carpeta de xv6-riscv debemos configurar el Makefile:

make clean

make

make qemu

Y listo!

-----------------------------------

Mi mayor problema era la instalación en WSL dado que no pude configurarlo para que la terminal de QEMU apareciera en mi terminal de Ubuntu con WSL, por lo que mi solución fue instalar Oracle VM Virtualbox que puede ser un poco tedioso pero totalmente util para terminos de este ramo.



