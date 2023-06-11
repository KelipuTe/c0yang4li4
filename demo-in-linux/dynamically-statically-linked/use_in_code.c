#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 程序中显示调用动态库
// gcc use_in_code.c -ldl -o use_in_code

int main() {
  void *handle;
  void (*print_hello_world)(void);
  char *error;

  // dlopen(3)
  // #include <dlfcn.h>
  handle = dlopen("./dynamically_library.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  dlerror(); /* Clear any existing error */

  // dlsym(3)
  // #include <dlfcn.h>
  print_hello_world = (void (*)())dlsym(handle, "print_hello_world");

  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  print_hello_world();

  dlclose(handle);
  exit(EXIT_SUCCESS);
}