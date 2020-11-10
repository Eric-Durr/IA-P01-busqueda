#include <GL/glut.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "../include/environment.hpp"
#include "../include/search.hpp"
#include "../include/slot.hpp"
#include "../include/smart_car.hpp"

int m_x, m_y;         // mouse x y moovement
bool m_down = false;  // mouse click default state

unsigned int speed = 100;  // speed variable
int play = false;          // Default state of play
int size_ = 50;            // Size of the slots

const int X = 50;  // Whole number of slots in x axis
const int Y = 50;  // Whole number of slots in y axis

int w =
    X * size_;  // Width of the window (cell size and number by X axis cells)
int h =
    Y * size_;  // Heigt of the window (cell size and number by Y axis cells)

Environment graphic_env(X, Y);

void display() {
  // first we clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // then the object color is setted (to white in this case (RGB))
  glColor3ub(255, 255, 255);

  // We give the point a size that represents the cell
  glPointSize(size_);

  // Then GLUT is prepared to paint points
  glBegin(GL_POINTS);

  /// DEFAULT CELL PAINTING ///

  // We ride all the matrix in order to search the alive cells and draw them in
  // the window
  for (int i = 0; i < graphic_env.get_n(); ++i)
    for (int j = 0; j < graphic_env.get_m(); ++j) {
      if (graphic_env.at(i, j).s_type() == O)
        glVertex2f(graphic_env.size() / 2 + i * size_,
                   graphic_env.size() / 2 + j * size_);
    }
  /// MOUSE CELL PAINTING ///

  // This conditional check the mouse movement for the user to set  obstacles
  if (m_down && m_x > 0 && m_y > 0 &&
      m_x < graphic_env.get_n() * graphic_env.size() &&
      m_y < graphic_env.get_m() * graphic_env.size()) {
    graphic_env.at(m_x / graphic_env.size(), m_y / graphic_env.size())
        .s_type(O);
  }
  // if the mouse isn't  clicking the last position of the mouse is drawed as
  // white but not setted the cell as alive
  else {
    int i = m_x / graphic_env.size();
    int j = m_y / graphic_env.size();
    glVertex2f(graphic_env.size() / 2 + graphic_env.size() * i,
               graphic_env.size() / 2 + graphic_env.size() * j);
  }
  // finally we end the "drawing time"
  glEnd();

  // We must flush the buffer so, these two functions can achieve that
  // glutSwapBuffers();
  glFlush();
}

void selector(unsigned char key, int xmouse, int ymouse) {
  switch (key) {
    // PLAY STATUS
    case '1':
      play = 1;
      break;

    // PAUSE STATUS
    case '2':
      play = 0;
      break;

    // CLEAR STAGE
    case '3':
      // this check all the matrix killing all the cells
      for (int i = 0; i < graphic_env.get_n(); ++i)
        for (int j = 0; j < graphic_env.get_m(); ++j) {
          graphic_env.clear_obs();
        }

      play = 0;
      break;

    case '0':
      std::exit(0);
      break;

    // INCREASE SPEED
    case 'u':
      if (speed > 0) speed = speed - 50;
      break;

    // DECREASE SPEED
    case 'd':
      if (speed <= 1000)
        ;
      speed = speed + 50;
      break;
      break;
    default:
      break;
  }
}

void timer(int = 0) {
  // This reads the keyboard input in running time
  glutKeyboardFunc(selector);

  // Only if the play variable is 1 the program proceed to update (you can
  // change it by keyboard, selector function contains it)
  if (play)
    /*     update();
     */
    // this shows the actual state in the window
    display();

  // Registers a timer callback executed in a specified milliseconds number
  // (this provides changes throug running time)
  //            msecs,  callback, value
  glutTimerFunc(speed, timer, 0);
}

// this function tracks the mouse position and interaction
void mouse(int button, int state, int ax, int ay) {
  m_y = ay;                     //| -> position
  m_x = ax;                     //|
  m_down = state == GLUT_DOWN;  // | -> reads if button was clicked
}

// captures the mouse motion in the scene
void motion(int ax, int ay) {
  m_x = ax;
  m_y = ay;
}

// captures the passive mouse motion in the scene
void motionpass(int ax, int ay) {
  m_x = ax;
  m_y = ay;
}

int main(int argc, char **argv) {
  /*This statement prepare the library to run*/
  glutInit(&argc, argv);

  /*These two statements can define the display mode:
   *
   * GLUT_SIGLE/DOUBLE -> bit mask for double or single buffered window
   * GLUT_RGB/RGBA -> color mode for the window
   *
   *  */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  /* As The function says this defines thw width and height of the window
   *
   *     w and h are defined in lines 13 and 14 -> they depend on X and Y
   * parameters multiplied by the cell size (size_);
   */
  glutInitWindowSize(w, h);

  /* The next function defines the initial position of the window that we are
   * going to create
   *
   *     We must give a (X, Y) coordinates
   */
  glutInitWindowPosition(-10, -10);

  /* Whe summon a window with the next method by giving it the name of the
   * window as parameter */
  glutCreateWindow(
      "Cell matrix |  press 1 to start and 2 for stop. 3 clears the stage and "
      "0 closes the window");

  /* This statement gives the window a color by terms of RGBA
   * ([0-1][0-1][0-1][0-1] )*/
  glClearColor(0, 0, 0, 1.0);

  /* The next fucntion applies the matrix operations to the projection of the
   * matrix stack*/
  glMatrixMode(GL_PROJECTION);

  /* This replaces the current matrix with the identity matrix */
  glLoadIdentity();

  /* The next statement sets an ortographic projection (multiplies the current
   * matrix with an ortographic matrix) */
  glOrtho(0, w, h, 0, -1, 1);

  /* The next statement "paints" the function that we are going to show. In this
   * case we are passing the display function, which was defined before */
  glutDisplayFunc(display);

  /* We summon the timer function which allows us to manage time*/
  /*  timer(); */

  /* The next fuction keeps the mouse moovement */
  glutMouseFunc(mouse);

  /* This statements reports the mouse movement while a button is pressed */
  glutMotionFunc(motion);

  /* Same as previous but without dragging*/
  glutPassiveMotionFunc(motionpass);

  /* this statement should be called at least once in a GLUT program. Provides a
   * never return statement, looping the callbacks */
  glutMainLoop();
}