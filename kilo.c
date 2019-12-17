/* Kilo editor
 * Xilin Sun
 * A text editor in text mode
 * Ref: http://viewsourcecode.org/snaptoken/kilo/01.setup.html
 *
 * compile and run by
 * make && ./kilo
 */

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct termios orig_termios;

void disableRawMode() {
  // resets terminal attibutes to disable raw mode
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  // gets and changes terminal attributes to enable raw mode and turn off
  // canonical mode
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  // ECHO: echo flag
  // ICANON: canonical mode flag
  // ISIG: SIGINT(Ctrl-C, terminate)/SIGTSTP(Ctrl-Z, suspend) flags.
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  // stdlib.h atexit will be called when the program exits
  atexit(disableRawMode);
}

int main(void) {
  enableRawMode();

  char c;
  // reads to c; press 'q' to exit
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    // ctype.h iscntrl tests if a character is a control character
    if (iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c, c);
    }
  }
  return 0;
}