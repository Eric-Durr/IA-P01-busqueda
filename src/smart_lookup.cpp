#include <iostream>

#include "../include/environment.hpp"
#include "../include/obstacle.hpp"
#include "../include/slot.hpp"
#include "../include/smart_car.hpp"

int main(void) {
  int modo, fil, col, n_obs;
  int i, o_fil, o_col, m_fil, m_col;
  std::cout << "PRÁCTICA: Estrategias de Búsqueda.\n";

  try {
    std::cout << "¿De qué manera desea ejecutar su programa? \n";
    std::cout << "1.Modo manual.\t 2.Modo aleatorio.\n";
    std::cout << "Modo: ";
    std::cin >> modo;

    if (modo == 1) {
      std::cout << "\n1.Modo manual.\n";
      std::cout << "Introduzca las dimensiones del entorno(Fila Columna): ";
      std::cin >> fil >> col;
      Environment tab(fil, col);

      std::cout << "\nIntroduzca el número de obstáculos deseados: ";
      std::cin >> n_obs;

      for (i = 0; i < n_obs; i++) {
        std::cout << "\nIntroduzca la posición del obstáculo [" << i + 1
                  << "] (Fila Columna): ";
        std::cin >> o_fil >> o_col;
        tab.set_obs(o_fil - 1, o_col - 1);
      }
      std::cout << "\nIntroduzca la posición de la meta (Fila Columna): ";
      std::cin >> m_fil >> m_col;
      tab.set_goal(m_fil - 1, m_col - 1);

      tab.set_car(0, 1);

      std::cout << "\nEntorno y visualiacion de la trayectoria:\n";
      std::cout << tab << std::endl;

      tab.move_car(S, 3, tab);
      /*tab.move_car(N, 1, tab);
      tab.move_car(E, 1, tab);
*/

      std::cout << "\nEntorno y visualiacion de la trayectoria:\n";
      std::cout << tab << std::endl;
    } else if (modo == 2) {
      std::cout << "\n2.Modo aleatorio.\n";
      std::cout << "Introduzca las dimensiones del entorno(Fila Columna): ";
      std::cin >> fil >> col;
      Environment tab(fil, col);

      std::cout << "\nSe crearán de manera random los obstáculos.\n";
      tab.random_obs(0.25);

      std::cout << "\nIntroduzca la posición de la meta (Fila Columna): ";
      std::cin >> m_fil >> m_col;
      tab.set_goal(m_fil, m_col);

      tab.set_car(0, 0);

      std::cout << "\nEntorno y visualiacion de la trayectoria:\n";
      std::cout << tab << std::endl;

    } else {
      std::cerr << "[!] ERROR. Valor introducido inválido. Vuelva a ejecutar "
                   "el programa.\n\n";
      return 1;
    }

    return 0;

  } catch (...) {
    std::cerr << "\n[!] Ha ocurrido un error.\n";
    return 1;
  }
}