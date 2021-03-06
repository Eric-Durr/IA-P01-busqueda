# IA Práctica 1 | Estrategias de búsqueda
En este entorno de trabajo se desarrollará la primera práctica de Inteligencia
Artificial. El proyecto ha sido preparado para desarrollarse con el lenguaje de
programación C++ al cual se le han añadido algunas librerías.


***Estructura del directorio***

```
.
|____docs              # Directorio para los ficheros de documentación.
|____include           # Directorio para los ficheros de cabecera y librerías.
|____informe           # Directorio contenedor del informe y sus recursos.
|____test              # Directorio para los ficheros de testing.
|____src               # Directorio para los ficheros de código fuente.
|____.gitignore        # Fichero de filtrado del remoto.
|____makefile          # Fichero de automatización para C++.
|____README.md         # Fichero de presentación del repositorio.
|____smart_lookup.txt  # Fichero de descripción de un entorno a resolver.


```

## Autores
[Elena Rijo García](alu0101265421@ull.edu.es)

[Eric Dürr Sierra](eric.durr.20@ull.edu.es) 
## Dependencias

- Catch2 (Librería de testing C++ para aplicar TDD)
    [Proyecto GitHub](https://github.com/catchorg/Catch2)
    [Video informativo](https://www.youtube.com/watch?v=CGuWYqHsOxI)

## Uso del proyecto

- ```$ make``` -> Compilar el programa
- ```$ make clean``` -> Eliminar los ficheros de construcción y el binario
- ```$ make test``` -> Compilar y ejecutar los tests del proyecto

## Ejecución del programa

- ```./smart_lookup``` -> modo menú
- ```./smart_lookup -f smart_lookup.txt``` -> ejecución directa del programa por lectura de fichero

- ```./smart_lookup -r ``` -> ejecución directa del modo aleatorio