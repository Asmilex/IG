# IG
Prácticas de la asignatura Informática Gráfica

## Exámenes
Se pueden ver los exámenes en las distintas ramas. Los enunciados se encuentran en un README o en la carpeta ./img

## Práctica 1

> En la primera práctica se completará el código de creación (constructor) de la clase Escena1, derivada de Escena. La clase Escena1 contendrá varios objetos de clases derivadas de MallaInd. Cada uno de esos objetos contiene las tablas de coordenadas de vértices, atributos e indices correspondientes a una malla indexada.

## Windows

> Dependencias: cmake, ¿Visual Studio?

Las tareas están configuradas para que funcione todo directamente. Solo dependen de `cmake`. No obstante, **se asume que el shell predeterminado es `cmd`**.

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
