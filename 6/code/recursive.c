#include <stdio.h>
#include <stdlib.h>

int f() {
  static int depth = 0;
  depth++;
  int i;
  printf("i address=%p\n", &i);
  if (depth < 100) {
    f();
  }
}

int main() {
  f();
}
