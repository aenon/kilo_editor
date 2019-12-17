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
  // gets and changes terminal attributes
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  // terminal local flags
  // ECHO: echo flag
  // ICANON: canonical mode flag
  // IEXTEN: disabling IEXTEN will disable Ctrl-V
  // ISIG: SIGINT(Ctrl-C, terminate)/SIGTSTP(Ctrl-Z, suspend) flags.
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  // terminal input flags
  // ICRNL: carriage return new line. disables '\r' -> '\n' feature
  // IXON: input XON and XOFF, for software flow control
  // this is not needed nowadays
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  // terminal output flags
  // OPOST: post processing.
  raw.c_oflag &= ~(OPOST);
  // legacy: sets the caracter size to 8 bits per byte
  raw.c_cflag |= (CS8);
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
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
  }
  return 0;
}