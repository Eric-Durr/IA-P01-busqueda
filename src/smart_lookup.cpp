#include <unistd.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "../include/environment.hpp"
#include "../include/search.hpp"
#include "../include/slot.hpp"
#include "../include/smart_car.hpp"

using namespace std::chrono;

void error_msg(int opt);

void manual_env(void);
void introduce_obstacles(Environment& man_env);

void random_env(void);

void file_env(std::string filename);

int main(int argc, char* argv[]) {
  std::string filename;

  if (argc > 1) { /* OPCIONES DE LINEA DE COMANDO */
    /* Procesado de la linea de comandos | WIP*/
    {
      int opt;
      while ((opt = getopt(argc, argv, ":f:r")) != -1) {
        switch (opt) {
          case 'f':
            std::cout << "File reading option\n";
            file_env(optarg);
            break;
          case 'r':
            std::cout << "Random generate option\n";
            random_env();
            break;
          case ':':
            std::cout << "The option needs a value\n";
            break;
          case '?':
            std::cout << "Unknown option\n";
            std::cout << "Usage: ./smart_lookup [-f / -r] [filename]\n";
            break;
        }
      }
    }
    /* --- */
  } else { /* OPCIONES DE MENÚ */
    int op = 5;
    while (op != 0) {
      std::cout << "\n\n --- Smart lookup with a-star algorithm menú ---\n";
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "1) Manual environment creator\n";
      std::cout << "2) Semi-random environment creator\n";
      std::cout << "3) File readed environment creator\n";
      std::cout << "0) Exit program\n\n";
      std::cout << "> ";
      std::cin >> op;
      switch (op) {
        case 1:
          manual_env();
          break;

        case 2:
          random_env();
          break;

        case 3:

          std::cout << "Type a valid filename: ";
          std::cin >> filename;

          file_env(filename);
          break;
        default:
          std::cout << "Option not suported\n";
          break;
      }
      if (op != 0) {
        std::cout << "Press ENTER to continue: \n";
        std::getchar();
        std::getchar();
      }
      system("clear");
    }
  }

  return 0;
}

void error_msg(int opt) {
  switch (opt) {
    case 1:

    default:
      break;
  }
}

void manual_env(void) {
  long row_sz, col_sz, st_pos_i, st_pos_j, g_pos_i, g_pos_j, h_op;
  std::string obs_bool;
  bool inrange = false;

  std::cout << "\n\n\nWelcome to the manual environment creator \n\n";
  std::cout << "Start by defining the row and column size (Example: row col): ";
  std::cin >> row_sz >> col_sz;
  std::cout << std::endl;
  std::cout << std::endl;
  Environment man_env(row_sz, col_sz);
  while (inrange == false) {
    std::cout << "Now introduce the start position (Example: 1 1): ";
    std::cin >> st_pos_i >> st_pos_j;
    if (man_env.pos(st_pos_i - 1, st_pos_j - 1) != -1) {
      inrange = true;
    } else {
      std::cout << "\nERROR: Make sure that the numbers are between 1 and the "
                   "limits\n"
                << "try again\n\n";
    }
  }

  std::cout << std::endl;
  std::cout << std::endl;
  inrange = false;
  while (inrange == false) {
    std::cout << "Now introduce the goal position (Example: 5 5): ";
    std::cin >> g_pos_i >> g_pos_j;
    if (man_env.pos(g_pos_i - 1, g_pos_j - 1) != -1) {
      inrange = true;
    } else {
      std::cout << "\nERROR: Make sure that the numbers are between 1 and the "
                   "limits\n"
                << "try again\n\n";
    }
  }
  std::cout << std::endl;
  std::cout << std::endl;

  man_env.clear_obs();
  man_env.set_car(st_pos_i - 1, st_pos_j - 1);
  man_env.set_goal(g_pos_i - 1, g_pos_j - 1);

  std::cout << "Do you want to introduce some obstacles? (yes/no): ";
  std::cin >> obs_bool;
  if (obs_bool[0] == 'Y' || obs_bool[0] == 'y') {
    introduce_obstacles(man_env);
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Which heuristic value you want to use ?\n";
  std::cout << "1) Euclidean distance\n";
  std::cout << "2) Manhattan distance\n";
  std::cout << "> ";
  std::cin >> h_op;

  Search man_env_search(man_env, h_op);

  auto start = high_resolution_clock::now();

  man_env_search.a_star_algorithm();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  std::cout << "Time taken by function: " << duration.count() << " milliseconds"
            << "\n";

  if (row_sz >= 100 || col_sz >= 100) {
    std::cout << "Output file generated because of the size\n";
    std::ofstream output("man_result.txt");
    output << man_env_search << std::endl;
    output.close();
  } else {
    std::cout << man_env_search << std::endl;
  }
}

void introduce_obstacles(Environment& man_env) {
  int obs_i_pos, obs_j_pos;
  std::string continuer;
  while (1) {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Set an obstacle as done with the start or goal point "
                 "(Example: 2 2): ";
    std::cin >> obs_i_pos >> obs_j_pos;

    if (man_env.pos(obs_i_pos - 1, obs_j_pos - 1) == -1) {
      std::cout << "\nERROR: Make sure that the numbers are between 1 and "
                   "the limits\n"
                << "try again\n\n";
    }

    man_env.set_obs(obs_i_pos - 1, obs_j_pos - 1);
    std::cout << "Do you want to stop adding obstacles? (yes/no): ";
    std::cin >> continuer;
    if (continuer[0] == 'Y' || continuer[0] == 'y') {
      return;
    }
  }
}

void random_env(void) {
  long row_sz, col_sz, st_pos_i, st_pos_j, g_pos_i, g_pos_j, rand_vol, h_op;

  bool inrange = false;

  std::cout << "\n\n\nWelcome to the random environment creator \n\n";
  std::cout << "Start by defining the row and column size (Example: row col): ";
  std::cin >> row_sz >> col_sz;
  std::cout << std::endl;
  std::cout << std::endl;
  Environment rand_env(row_sz, col_sz);
  while (inrange == false) {
    std::cout << "Now introduce the start position (Example: 1 1): ";
    std::cin >> st_pos_i >> st_pos_j;
    if (rand_env.pos(st_pos_i - 1, st_pos_j - 1) != -1) {
      inrange = true;
    } else {
      std::cout << "\nERROR: Make sure that the numbers are between 1 and the "
                   "limits\n"
                << "try again\n\n";
    }
  }

  std::cout << std::endl;
  std::cout << std::endl;
  inrange = false;
  while (inrange == false) {
    std::cout << "Now introduce the goal position (Example: 5 5): ";
    std::cin >> g_pos_i >> g_pos_j;
    if (rand_env.pos(g_pos_i - 1, g_pos_j - 1) != -1) {
      inrange = true;
    } else {
      std::cout << "\nERROR: Make sure that the numbers are between 1 and the "
                   "limits\n"
                << "try again\n\n";
    }
  }
  std::cout << std::endl;
  std::cout << std::endl;

  rand_env.clear_obs();
  rand_env.set_car(st_pos_i - 1, st_pos_j - 1);
  rand_env.set_goal(g_pos_i - 1, g_pos_j - 1);

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Select a volume of obstacles in the environment:\n";
  std::cout << "1) 5%\n";
  std::cout << "2) 10%\n";
  std::cout << "3) 15%\n";
  std::cout << "4) 25%\n";
  std::cout << "5) 35%\n";
  std::cout << "6) 50%\n";
  std::cout << "> ";
  std::cin >> rand_vol;

  switch (rand_vol) {
    case 1:
      rand_env.random_obs(0.05);
      break;

    case 2:
      rand_env.random_obs(0.1);
      break;

    case 3:
      rand_env.random_obs(0.15);
      break;
    case 4:
      rand_env.random_obs(0.25);
      break;

    case 5:
      rand_env.random_obs(0.35);
      break;

    case 6:
      rand_env.random_obs(0.50);
      break;

    default:

      rand_env.random_obs(0.15);
      break;
  }

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Which heuristic value you want to use ?\n";
  std::cout << "1) Euclidean distance\n";
  std::cout << "2) Manhattan distance\n";
  std::cout << "> ";
  std::cin >> h_op;

  Search rand_env_search(rand_env, h_op);

  auto start = high_resolution_clock::now();

  rand_env_search.a_star_algorithm();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  std::cout << "Time taken by function: " << duration.count() << " milliseconds"
            << "\n";

  if (row_sz >= 100 || col_sz >= 100) {
    std::cout << "Output file generated because of the size\n";
    std::ofstream output("rand_result.txt");
    output << rand_env_search << std::endl;
    output.close();
  } else {
    std::cout << rand_env_search << std::endl;
  }
}

void file_env(std::string filename) {
  long row_sz, col_sz, st_pos_i, st_pos_j, g_pos_i, g_pos_j, num_obs, obs_pos_i,
      obs_pos_j, h_op;

  std::ifstream file(filename);
  if (!file)
    std::cout << "[!] ERROR. No filename found in the root directory of the "
                 "project.\n";

  file >> row_sz >> col_sz;
  Environment env(row_sz, col_sz);
  file >> st_pos_i >> st_pos_j;
  env.set_car(st_pos_i - 1, st_pos_j - 1);
  file >> g_pos_i >> g_pos_j;
  env.set_goal(g_pos_i - 1, g_pos_j - 1);
  file >> num_obs;

  for (int i = 0; i < num_obs; i++) {
    file >> obs_pos_i >> obs_pos_j;
    env.set_obs(obs_pos_i - 1, obs_pos_j - 1);
  }

  file >> h_op;

  Search a_star(env, h_op);

  auto start = high_resolution_clock::now();

  a_star.a_star_algorithm();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  std::cout << "Time taken by function: " << duration.count() << " milliseconds"
            << "\n";

  if (row_sz >= 100 || col_sz >= 100) {
    std::cout << "Output file generated because of the size\n";
    std::ofstream output("file_result.txt");
    output << a_star << std::endl;
    output.close();
  } else {
    std::cout << a_star << std::endl;
  }
}