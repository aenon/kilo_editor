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
#include <errno.h>

struct termios orig_termios;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disable_raw_mode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
    die("tcsetattr");
  }
}

void enable_raw_mode() {
  // gets the current terminal attributes and saves in orig_termios
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    die("tcgetattr");
  }
  // disables raw mode at exit to avoid having to reset the terminal
  atexit(disable_raw_mode);


  struct termios kilo_termios = orig_termios;
  // sets c_iflag (input modes)
    // IXON: transmission pause/resume keys
    // ICRNL: translate carriage return to newline on input 
  kilo_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  // sets c_oflag (output modes)
    // OPOST: output processing
  kilo_termios.c_oflag &= ~(OPOST);
  kilo_termios.c_cflag |= (CS8);
  // sets c_lflag (local modes)
    // ECHO: echo
    // ICANON: canonical mode
    // ISIG: signals (Ctrl-Z, Ctrl-C)
    // IEXTEN: implementation-defined input processing
  kilo_termios.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  kilo_termios.c_cc[VMIN] = 0;
  kilo_termios.c_cc[VTIME] = 1;

  // saves terminal attributes
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &kilo_termios) == -1) {
    die("tcsetattr");
  }
}

int main() {
  enable_raw_mode();

  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
      die("read");
    }
    if (iscntrl(c)) {
      // prints the ASCII code for control characters
      printf("%d\r\n", c);
    } 
    else {
      // prints the ASCII code and the character itself
      printf("%d (%c)\r\n", c, c);
    }
    if (c == 'q') break;
  }
  return 0;
}
