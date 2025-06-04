#include <stdio.h>
int main() {
	FILE *w = fopen("/home/mateo/taller-terminal/win/wc.txt", "r");
	char line[500];
  if (w == NULL)
    return 1;
  while (fgets(line, sizeof(line), w) != NULL) {
    printf("%s", line);
  }
	fclose(w);
	return 0;
}
