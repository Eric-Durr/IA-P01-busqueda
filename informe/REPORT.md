# Informe | estrategias de búsqueda

<br>

Inteligencia Artificial - ESIT (Escuela superior de Ingeniería y Tecnología) ULL
***

<br>
<br>
<br>
<br>
<br>
<br>
<br>

![IA front image](images/portada.jpg)

<br>
<br>
<br>
<br>
<br>
<br>
<br>
    
    Informe desarrollado por Éric Dürr Sierra y Elena Rijo García

                            (alu0101027005)      (alu0101265421)
<br>
<br>
<br>
<br>

<!-- end of cover page --->
***

<introducción al documento>

<br>
<br>
<br>


## **Índice** &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Página:
 

## 1. [Introducción](#id1) 
## 2. [Entrorno de simulación y programación](#id2) 
## 3. [Metodología de trabajo](#id3)  
## 4. [Algoritmos de búsqueda](#id4) 
## 5. [Evaluación experimental del algoritmo](#id5)  
## 6. [Conclusiones](#id6) 
## 7. [Referencias](#id7) 


<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

***

<!-- end of index page --->
<br>
<br>
<br>
<br>
 
<br>
<br>
<div id="id1">
<br>
<br>

## **1. Introducción.**
<br>
<br>

### 1.1. Breve descripción del problema

Nos encontramos ante un problema de estrategias de búsqueda para la resolución de la trayectoria mas óptima para un coche autónomo.

Contamos con un entorno dimensionado en MxN, en el cual nuestro coche va a efectuar sus movimientos, hacia sus casillas vecinas(Norte, Sur, Este y Oeste). Este entorno esta compuesto por celdas libres y celdas ocupadas, en donde las celdas ocupadas podrán estar constituidas por un coche, una meta o varios obstáculos.

Nuestro coche, desde un punto inicial, deberá encontrar el camino mas óptimo teniendo en cuentas los diferentes entornos y obstáculos que se le pueden presentar para llegar hasta el punto de finalización(meta).

<br>
<br>

### 1.2. Formulación del problema como espacio estados

Hablaremos sobre el espacio de estados. Este se compondrá por un estado inicial, en el cual en su entorno tendrá el coche y la meta en la posición indicada por el usuario, además de definir dónde y cuántos obstáculos habría. También un estado final, en donde el coche llegaría a la posición de la meta.

Los estados y sus operadores, dependerán tanto del número y de dónde se encuentren los obstáculos como de la posición de la meta y del coche. Además, tenemos que tener en cuenta que cada movimiento del coche se va a ver influido por el estado de la casilla, ya que si hay casillas ocupadas, este no se podría mover hacia ella, reduciendo así el número posible de pasos.
 
<br>
<br>
<div id="id2">
<br>
<br>

## **2. Entorno de simulación y programación.**
<br>
<br>

### 2.1. Descripción de la interfaz.
<br>
<br>

Hemos querido elegir C++ como lenguaje de desarrollo de simulación de esta práctica, ya que es un lenguaje de dominamos y hemos ido aprendiendo a lo largo de los cursos académicos. Nos beneficiamos de las ventajas que nos brinda la programación orientada a objetos, así como su modularidad. 

La visualización y simulación del entorno y sus elementos se ha realizado a través de terminal, gracias a un menú con diversas opciones para un fácil manejo para el usuario. Este menú da las opciones de introducir manualmente los datos, teniendo en cuenta la inserción de los obstáculos de manera manual o aleatoria, y la posibilidad de cargar un fichero con los datos introducidos en este. Los datos pedidos al usuarios serán el tamaño MxN del entorno, la posición (i,j) del coche, de la meta, y de los obstáculos, poniendo especial atención en que si se elige la opción aleatoria los obstáculos se generaran en posiciones arbitrarias, excluyendo la posición del coche y de la meta.

También, en terminal, se visualiza la elección de la función heurística deseada, ya sea la función heurística Euclidea o la Manhattan. 

Una vez se haya finalizado la inserción de todos los datos esperados, se generará visualmente nuestro entorno. De primera mano, se visualiza la posición del coche, la meta y los obstáculos, en las posiciones deseadas. Seguidamente, se vuelve a reflejar dicho entorno, pero esta vez mostrando mediante flechas el camino óptimo elegido para llegar al estado final. 

Por último, podemos destacar que cada vez que termine la ejecución del programa, se limpiará la terminal y se lanzará de nuevo el menú por si el usuario desea volver a realizar el programa desde el principio, teníendo también la opción de salir de este.


(INTRODUCIR CAPTURAS DE PANTALLA)

<br>
<br>

### 2.2. Descripción de la implementación.


<br>
<br>

### 2.3. Argumentación sobre el entorno de programación escogido.

Se ha escogido un entorno basado en el lenguaje C++ por diversos motivos. Fundamentalmente la comodidad de usar un lenguaje ya conocido y en el que ambos
componentes pueden manejarse de manera independiente.

Un punto muy positivo que ayudó a la elección del lenguaje es la amplia comunidad y volumen de documentación del que dispone. Esto ha facilitado en gran medida el desarrollo del proytecto. También haq influido en la posibilidad de implementar técnicas de desarrollo como TDD o BDD mediante librerías que la comunidad ha desarrollado de manera opensource como es Catch2.

También es bastante similar a muchos lenguajes por lo que muchas personas que quisieran acceder al proyecto podrían entender muchos de los aspectos que lo componen

Por sus características C++ es un lenguaje que tiene mucha potencia de cómputo y, para el caso que nos ocupa, resulta muy útil. Se obtendrán resultados a mayor velocidad que con muchos otros lenguajes.

Por otro lado y entrando en aspectos más generales se ha optado por un entorno de 
programación basado en directorios que separan cabeceras, código de desarrollo y tests, de manera que un solo fichero Makefile pueda componer rápidamente muchos de los comandos más frecuentes para el proyecto.

El trabajo con Git como herramienta colaborativa requiere también de un espacio organizado y fuertemente modular de cara a evitar conflictos.

<br>
<br>
<div id="id3">
<br>
<br>

## **3. Metodología de trabajo.**
<br>
<br>

### 3.1. Metodología de desarrollo.

<!-- TDD -->
Para este apartado, hemos decidido utilizar un desarrollo guiado por pruebas, también conocido como TDD (Test-driven development). Esta técnica consiste en escribir primero las pruebas unitarias, seguidamente escribir el código fuente que queremos que pase la prueba satisfactoriamente, y por último, refactorizar el código escrito.


Gracias a esto, podemos agilizar nuestro proceso de creación de código, llevado a cabo la implementación de diversos test, que nos han servido para ir desarrollando dentro de cada clase, los métodos necesarios requeridos para esta práctica. Además, hemos evitado la creación de métodos innecesarios o de código que no se utiliza en nuestro programa, produciendo así un mayor robustez y mantenibilidad ante el problema.

<br>
<br>

### 3.2. Paradigma de programación.

<!-- OOP y como -->
<br>
<br>

### 3.2. Metodología de colaboración  y distribución de carga.
<!-- Git, GitHub, GitHub projects, ... -->

<br>
<br>
<div id="id4">
<br>
<br>

## **4. Algoritmo de búsqueda.**
<br>
<br>

### 4.1. Pseudo-código.


    ALGORITMO DE BÚSQUEDA A-ESTRELLA

      nodo_inicial.valor_f = 0
      insertar nodo inicial en lista abierta 

      MIENTRAS (lista abierta no vacía)

        q = nodo mínimo de lista abierta
        borrar q de lista abierta
        insertar q en lista cerrada

        generar sucesores de q

        PARA (cada sucesor)

          SI (es el destino)

            sucesor_padre = q
            sucesor.valor_g = q.valor_g + unidad_de_coste
            sucesor.valor_f = sucesor.valor_g + función_heurística(sucesor)
            generar camino
            SALIR DE LA BÚSQUEDA
          __

          EN OTRO CASO SI (no está en la lista cerrada y no es obstáculo)
            g = q.valor_g + unidad_de_coste;
            f = funcion_heurística(sucesor)
            SI (no está en la lista abierta)
              actualizar padres en el entorno
              sucesor_padre = q
              sucesor.valor_g = g
              sucesor.valor_f = f
              insertar sucesor en lista abierta
            __
          __
        __ 
      __

      SALIR DE LA BÚSQUEDA
    __
          
La implementación del pseudocósigo implementado se traduce directamente a C++
destacando algunos aspectos esenciales
1. Se emplea una variable para detectar si la meta ha sido encontrada, de este modo al llegar al final del algoritmo si no se ha encontrado se podrá notificar de ello:

```cpp
if (found_goal == false) {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "VEHICLE CANT REACH THE GOAL\n ";
}
```

2. Para hallar el valor mínimo se itera con un bucle automático habiendo establecido un valor previo para el nodo mínimo (en este caso el útlimo valor de la lista). Acto seguido se elimina ese nodo de la lista abierta haciendo uso de la STL y se inserta en la lista cerrada.

```cpp
Slot min = open_.back();
for (auto current : open_)
  if (min.get_f() >= current.get_f()) {
    min = current;
}
open_.erase(std::find(open_.begin(), open_.end(), min));
/*  ---  */

closed_.push_back(min);
```

3. Los sucesores se generan haciendo uso de un método privado, este emplea el entorno para localizar el nodo origen y componer un vector que contenga en orden los puntos cardinales que se consideran como sucesores. Dentro de este método si la posición no es accesible se sitúa en (-1, -1) y se establece su estado como obstáculo. 

```cpp
std::vector<Slot> Search::get_successors(const Slot& q) {
  Slot north = env_.pos(q.pos_i() - 1, q.pos_j()) != -1
                   ? env_.at(q.pos_i() - 1, q.pos_j())
                   : Slot(-1, -1, O);
  ...
  return std::vector<Slot>{north, ...};
}
```

4. Luego esta lista de casillas será iterada para escoger las no visitadas e introducirlas en la lista abierta con sus respectivos valores o localizar la meta. También se actualizan los estados que componen el camino.

```cpp
for (auto var : successors) {
      if (var.get_obs() == G) {
        env_.at(var.pos_i(), var.pos_j()).set_parents(min.pos_i(), min.pos_j());
        var.set_parents(min.pos_i(), min.pos_j());
        var.set_g(min.get_g() + MOVE_VAL); /* 2nd arg is in doubt */
        var.set_f(var.get_g() + heuristic_function(var)); /* blocked h */

        std::cout << std::endl;
        std::cout << "\nGOAL FOUND !\n";
        trace_path(var);
        found_goal = true;
        return;

        /* If it's not yet at close list and it´s not an obstacle */
      } else if ((is_in_close(var) == false) && (var.is_obs() == false)) {
        new_g = min.get_g() + MOVE_VAL;
        new_h = heuristic_function(var);
        new_f = new_g + new_h;

        /* If it's not at open list or it is but with lower f, insert it */
        if (is_in_open(var) == false) {
          env_.at(var.pos_i(), var.pos_j())
              .set_parents(min.pos_i(), min.pos_j());
          var.set_parents(min.pos_i(), min.pos_j());
          var.set_g(new_g);
          var.set_f(new_f);

          open_.push_back(var);
        }
      }
    }
```
5. Cuando se alcanza la meta se llama a trace_path() para componer el camino. Este método va recorriendo los predecesores de cada casilla hasta llegar al origen, el resultado se guarda en un atributo. "temp" hace alusión al último nodo revisado, osea la meta.

```cpp
while (temp.parent_i() != -1 && temp.parent_j() != -1) {
    path_.push_back(temp);
    temp = env_.at(temp.parent_i(), temp.parent_j());
  }

```




      



<br>
<br>

### 4.2. Estructura de datos empleada.

Se pueden distinguir tres estructuras de datos. Empezaremos por el propio entorno.

1. El entorno que describe la ubicación de todas las casillas se  compone por un vector que simula una matriz, dentro de cada elemento del vector se halla cada casilla.


```
<-------NxM------->   
[ | | | ... | | | ] 


      j0 j1 j2    jm        j0 j1 j2    jm             j0 j1 j2    jm
 [i0(|  |  | ... |  |), i1(|  |  | ... |  |), ..., in(|  |  | ... |  |)]
```

  Se opera por completo dentro de este medio a la hora de localizar obstáculos, mover el coche y situar la meta. Su localización se describe en el apartado 2.2 junto a la descripción de la implementación del entorno.

2. Luego se distinguen las listas cerrada y abierta que nuevamente son vectores de casillas, sin embargo estas estructuras sencillamente son contenedores, no simulan una matriz como lo hace el entorno. También se emplea un vector denominado como "path" que contendrá, en orden, las casillas del camino óptimo.  


3. Por último el  objeto casilla (Slot) sirve de nodo para almacenar cada elemento del entorno así como su posición y la de su predecesor.
```
 (ELEMENTO DEL ENTORNO | POS_I ,POS_J | PADRE_I, PADRE_J)
```

<br>
<br>

### 4.3. Funciones heurísticas y justificación.

Las funciones heurísticas utilizadas han sido la Euclidea y la Manhattan. Hablaremos de ellas:

- Función heurística Euclidea:
Esta función aplica la fórmula matemática que nos permite medir la distancia en línea recta entre dos puntos en un espacio de n-dimensiones. En nuestro caso, esta función se realizará en línea recta entre la posición del coche y la posición de la meta, sin tener en cuenta los obstáculos definidos, por lo que se obtendrá el resultado de esta operación matemática. Este resultado nos será útil posteriormente, ya que será uno de los factores que utilizarémos para hallar el camino óptimo.


- Función heurística Manhattan:
Esta función, de forma similar a la anterior, trata de una fórmula matemática que nos permite calcular la distancia entre dos puntos, esta vez haciendo uso de la suma absoluta de las distancias horizontal y vertical de las direncias de sus coordenadas. Es mayor que la distancia euclídea pero también es más real en la práctica. En nuestro caso, esta función se realizará entre la posición del coche y la posición de la meta, sin tener en cuenta los obstáculos definidos, por lo que se obtendrá el resultado de esta operación matemática. Este resultado nos será útil posteriormente, ya que será uno de los factores que utilizarémos para hallar el camino óptimo.

<br>
<br>
<div id="id5">
<br>
<br>

## **5. Evaluación experimental del algoritmo.**
<br>
<br>

<br>
<br>

### Evaluación de las tablas sin obstáculos 
<br>

Escenario pequeño (50*50). Encontrándose el coche en la posición (1,1) y la meta en la (50,50)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (ms) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | 98    | 13081730 |
| Manhattan   | xxxxxxxxx | 98  | 47356 |

<br>
<br>


Escenario mediano (100*100). Encontrándose el coche en la posición (1,1) y la meta en la (100,100)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (ms) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx |   198  | 134254257 |
| Manhattan   | xxxxxxxxx |  198 | 251489 |

<br>
<br>

Escenario grande (200*200). Encontrándose el coche en la posición (1,1) y la meta en la (200,200)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (ms) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | xxxxxxxx    | xxxx |
| Manhattan   | xxxxxxxxx | 398  | 1664532 |



<br>
<br>
<br><br>

### Evaluación de las tablas  25% obstáculos 

<br>

Escenario pequeño (50*50). Encontrándose el coche en la posición (1,1) y la meta en la (50,50)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | 98    | 7283968 |
| Manhattan   | xxxxxxxxx | 98  | 425149 |

<br>
<br>

Escenario mediano (100*100). Encontrándose el coche en la posición (1,1) y la meta en la (100,100)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | 198    | 80207118 |
| Manhattan   | xxxxxxxxx | 200  | 39743238 |

<br>
<br>

Escenario grande (200*200). Encontrándose el coche en la posición (1,1) y la meta en la (200,200)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | xxxxxxxx    | xxxx |
| Manhattan   | xxxxxxxxx | 398  | 48296333 |



<br>
<br>
<br><br>

### Evaluación de las tablas 50% obstáculos 

<br>

Escenario pequeño (50*50). Encontrándose el coche en la posición (1,1) y la meta en la (50,50)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | 126    | 913220 |
| Manhattan   | xxxxxxxxx | No encuentra la meta  | 3683 |

<br>
<br>

Escenario mediano (100*100). Encontrándose el coche en la posición (1,1) y la meta en la (100,100)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | xxxxxxxx    | xxxx |
| Manhattan   | xxxxxxxxx | No encuentra la meta  | 1821 |

<br>
<br>

Escenario grande (200*200). Encontrándose el coche en la posición (1,1) y la meta en la (200,200)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | xxxxxxxx    | xxxx |
| Manhattan   | xxxxxxxxx | xxxxxxxx  | xxxx |



<br>
<br>
<br><br>

### Evaluación de las tablas 80% obstáculos 

<br>

Escenario pequeño (50*50). Encontrándose el coche en la posición (1,1) y la meta en la (50,50)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | xxxxxxxx    | xxxx |
| Manhattan   | xxxxxxxxx | xxxxxxxx  | xxxx |

<br>
<br>

Escenario mediano (100*100). Encontrándose el coche en la posición (1,1) y la meta en la (100,100)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | xxxxxxxx    | xxxx |
| Manhattan   | xxxxxxxxx | xxxxxxxx  | xxxx |

<br>
<br>

Escenario grande (200*200). Encontrándose el coche en la posición (1,1) y la meta en la (200,200)

| Funciones H | Número de nodos expandidos | Longitud del camino (pasos) | tiempo (s) |
| :------------- | :----------: | :-----------: | -----------: | 
|  Euclidea | xxxxxxxxx | xxxxxxxx    | xxxx |
| Manhattan   | xxxxxxxxx | xxxxxxxx  | xxxx |



<br>
<br>
<br><br>


<br>
<br>
<div id="id6">
<br>
<br>

## **6. Conclusiones.**
<br>
<br>


<br>
<br>
<div id="id7">
<br>
<br>

## **7. Referencias.**

<!-- aportadas por eric -->
- [Implementación de algoritmo a-estrella | GeeksForGeeks](https://www.geeksforgeeks.org/a-search-algorithm/)
  > Implementación en un solo fichero del algoritmo a-estrella en lenguaje c++.

- [Cálculo del tiempo de ejecución | GeeksForGeeks](https://www.geeksforgeeks.org/measure-execution-time-function-cpp/)
  >

- [advantages and disadvantages of C++ | Data flair ](https://data-flair.training/blogs/advantages-and-disadvantages-of-cpp/)

<!-- Aportadas por Elena -->


<br>
<br>