#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <C:\Users\Hilding\documents\repos\C\functions.h>

int main () {
  int a, b, s; // eventually, change to char
  printf ("Ange ett tal:");
  scanf ("%d", &a); // scanf("%s", &a)
  // a = create_list(a)
  s = a; 
  signal(SIGINT, run_handler);
   do {
      printf ("Ange ett annat tal, eller avsluta med ctrl-c och valfritt input:");
      scanf ("%d", &b); // scanf("%s", &b)
      // b = create_list(b)
      if (run) {
        s = a + b; // s = add_lists(a, b)
        // potentially dealloc a, b
        a = s;
        printf ("Summan blir: %d\n", s);
      }
      else {
        printf("Avslutar...\n");
      }
  } while(run);
  printf("Summan blev: %d\n", s); 
  // save to result.txt
return 0;
}
