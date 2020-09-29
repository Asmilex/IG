# IG
Prácticas de la asignatura Informática Gráfica

## Windows

> Dependencias: cmake, ¿Visual Studio?

### A mano

#### Generar makefile

Desde `./project/cmake-win/build` ejecutar `cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..`

#### Limpiar archivos de compilación

Desde `./project/cmake-win/build` ejecutar

```
rmdir /s /q build
mkdir build
```

#### Compilar

Desde `./project/cmake-win/build` ejecutar `cmake --build .`


#### Ejecutar

Desde `./project` ejecutar `cmake-win\build\Debug\pracs_ig_exe.exe`
