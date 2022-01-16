#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 程序中显示调用动态库
// gcc dynamically_call.c -ldl -o dynamically_call

int main() {
  void *handle;
  void (*print_hello)(void);
  char *error;

  // dlopen(3)
  // #include <dlfcn.h>
  handle = dlopen("./library.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  dlerror(); /* Clear any existing error */

  // dlsym(3)
  // #include <dlfcn.h>
  print_hello = (void (*)())dlsym(handle, "print_hello");

  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  print_hello();

  dlclose(handle);
  exit(EXIT_SUCCESS);
}