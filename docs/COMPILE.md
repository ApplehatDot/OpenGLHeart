# Compiling OpenGL_heart yourself
To compile this repo, you need to have an enviroment.
we'll use <a href="https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download">MinGW 6.2.0-1 win32</a> compiler,
if you wish to use other compilers, go ahead. It's your own decision. and for our editor we'll use Code::blocks

After you set the envioroment, you will need to extract the freeglut 3.0.0 (for MinGW) which is <a href="https://www.transmissionzero.co.uk/software/freeglut-devel/">here</a>
what i did is only copy freeglut.dll in the same directory as compiled program, and the files rest at ```C:\MinGW\freeglut\```:
<div align='center'>
  <img src="images\freeglutdir.png">
</div>

After you'll decompress the Source_code.zip, you'll have the files neccesary for compiling.
what i like to do is to create ```makefile.bat``` file, and whenever i test smth, i just run it and run the executable itself.
that's what we'll add - the ``makefile.bat``'s content is under:
```bat
windres my.rc -O coff -o icon.res

gcc -c -o serce.o main.c -I"C:\MinGW\freeglut"

gcc -o serce.exe serce.o icon.res -L"C:\MinGW\freeglut" -lfreeglut -lopengl32 -lglu32 -lgdi32 -luser32 -mwindows
```
after running the makefile.bat file it'll create the files for us.
but last thing we'll have to do, is to add a ```freeglut.dll``` file to the same directory. If not, you'll get an error:
<div align='center'>
  <img src="images\freegluterror.png">
</div>

### if you'll have some issues, contact me on discord: *applehat.*
