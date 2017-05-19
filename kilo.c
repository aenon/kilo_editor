// Kilo editor
// Xilin Sun
// A text editor in text mode
// Ref: http://viewsourcecode.org/snaptoken/kilo/01.setup.html

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void enableRawMode() {
  struct termios raw;

  tcgetattr(STDIN_FILENO, &raw);

  raw.c_lflag &= ~(ECHO);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
  enableRawMode();

	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {printf("%c", c);}
	return 0;
}
