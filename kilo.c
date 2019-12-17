/* Kilo editor
 * Xilin Sun
 * A text editor in text mode
 * Ref: http://viewsourcecode.org/snaptoken/kilo/01.setup.html
 *
 * compile and run by
 * make && ./kilo
 */

#include <unistd.h>

int main(void) {
  // the starting point of the c program
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1);
  return 0;
}