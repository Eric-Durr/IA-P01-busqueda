#include <fstream>
#include <iostream>

#include "../include/environment.hpp"
#include "../include/obstacle.hpp"
#include "../include/slot.hpp"
#include "../include/smart_car.hpp"

int main(void) {
  int modo, fil, col, n_obs;
  int i, o_fil, o_col, m_fil, m_col;
  float rand_obs;
  std::cout << "PRÁCTICA: Estrategias de Búsqueda.\n";

  try {
    std::cout << "¿De qué manera desea ejecutar su programa? \n";
    std::cout << "1.Modo manual.\t 2.Modo aleatorio.\t 3.Modo insertar nombre "
                 "del fichero (smart_lookup.txt)\n";
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

      tab.move_car(S, 3);
      tab.move_car(N, 1);
      tab.move_car(E, 1);

      std::cout << "\nEntorno y visualiacion de la trayectoria:\n";
      std::cout << tab << std::endl;

    } else if (modo == 2) {
      std::cout << "\n2.Modo aleatorio.\n";
      std::cout << "Introduzca las dimensiones del entorno(Fila Columna): ";
      std::cin >> fil >> col;
      Environment tab(fil, col);

      std::cout << "\nSe crearán de manera random los obstáculos.\n";
      std::cin >> rand_obs;
      tab.random_obs(rand_obs);

      std::cout << "\nIntroduzca la posición de la meta (Fila Columna): ";
      std::cin >> m_fil >> m_col;
      tab.set_goal(m_fil, m_col);

      tab.set_car(0, 0);

      std::cout << "\nEntorno y visualiacion de la trayectoria:\n";
      std::cout << tab << std::endl;

    } else if (modo == 3) {
      int fil, col, g_fil, g_col, num_obs, o_fil, o_col;
      std::string nombreArchivo;

      std::cout << "Introduzca el nombre del fichero de entrada: ";
      std::cin >> nombreArchivo;

      std::ifstream file(nombreArchivo);
      if (!file) std::cout << "[!] Error. No se ha encontrado el fichero.\n";

      file >> fil >> col;
      Environment tab(fil, col);
      file >> g_fil >> g_col;
      tab.set_goal(g_fil, g_col);
      file >> num_obs;

      for (int i = 0; i < num_obs; i++) {
        file >> o_fil >> o_col;
        tab.set_obs(o_fil - 1, o_col - 1);
      }

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