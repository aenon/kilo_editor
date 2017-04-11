// Kilo editor
// Xilin Sun
// A text editor in text mode
// Ref: http://viewsourcecode.org/snaptoken/kilo/01.setup.html

#include <unistd.h>

int main() {
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
	return 0;
}
