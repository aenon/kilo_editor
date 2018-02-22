/* Kilo editor
 * Xilin Sun
 * A text editor in text mode
 * Ref: http://viewsourcecode.org/snaptoken/kilo/01.setup.html
 *
 * compile and run by
 * make && ./kilo
 */


#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct termios orig_termios;

void disable_raw_mode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
  // gets the current terminal attributes and saves in orig_termios
  tcgetattr(STDIN_FILENO, &orig_termios);
  // disables raw mode at exit to avoid having to reset the terminal
  atexit(disable_raw_mode);
  struct termios kilo_termios = orig_termios;
  // sets local flag
  // ~ECHO: turn off echo
  // ~ICANON turn off canonical mode
  // ~ISIG: turn off signals (Ctrl-Z, Ctrl-C)
  kilo_termios.c_lflag &= ~(ECHO | ICANON | ISIG);
  // saves terminal attributes
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &kilo_termios);
}

int main() {
  enable_raw_mode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      // prints the ASCII code for control characters
      printf("%d\n", c);
    } 
    else {
      // prints the ASCII code and the character itself
      printf("%d (%c)\n", c, c);
    }
  }
  return 0;
}
