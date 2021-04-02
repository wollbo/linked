#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <C:\Users\Hilding\documents\repos\linked\functions.h>

int main () {
  char a[512], b[512];
  list_item *head1, *head2; 
  printf ("Ange ett tal:");
  scanf("%s", &a);
  head1 = create_list(a); // a is reversed in place
  //test_list(head1);
  signal(SIGINT, run_handler);
  do {
      printf ("Ange ett annat tal, eller avsluta med ctrl-c och valfritt input:");
      scanf ("%s", &b);
      if (run) {
        head2 = create_list(b);
        //test_list(head2);
        add_lists(head1, head2); 
        //test_list(head1);
        update_sum(head1, a); 
        printf ("Summan blir: %s\n", a);
      }
      else {
        printf("Avslutar...\n");
      }
  } while(run);
  FILE *fil;
  fil = fopen("result.txt", "w");
  fputs(a, fil);
  fclose(fil);
return 0;
}
