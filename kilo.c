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

void enableRawMode() {
  struct termios raw;
  // gets and sets terminal attributes
  // to turn off echoing
  tcgetattr(STDIN_FILENO, &raw);
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void) {
  enableRawMode();

  char c;
  
  // reads to c; press 'q' to exit
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
  return 0;
}