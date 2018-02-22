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

void enableRawMode() {
  struct termios kiloTerm;

  // gets the current terminal attributes and saves in kiloTerm
  tcgetattr(STDIN_FILENO, &kiloTerm);

  // sets local flag: turn off echo
  kiloTerm.c_lflag &= ~(ECHO);

  // saves terminal attributes
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &kiloTerm);
}

int main() {
  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
  return 0;
}
