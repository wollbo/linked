#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <crtdbg.h>
#include <C:\Users\Hilding\documents\repos\C\functions.h>
// Checks: update_sum is not responsible, test add_lists disabled
// create_list can be run indefinitely - with large numbers
// run_handler is not the problem
// update_sum can cause problems
// check memory addresses of the linked lists as they are iterated, sometimes point to the same address? infinite recusion?
// try changing each while(head->tail != NULL) to while(head != NULL)...
// its always inside of these loops that the program breaks.
// probable: dereferencing null pointer
// only seems to break when adding a several digit number to the sum. incremention seems to be alright.
// consider: could be that variables inside functions are also global - possible problem?
// Rebuild program - do not add to a; instead create a new list for each addition, dealloc both a, b
int main () {
  char a[512], b[512];
  list_item *head1, *head2; 
  printf ("Ange ett tal:");
  scanf("%s", &a);
  head1 = create_list(a); // funkar, men a revereseras in-place
  test_list(head1);
  signal(SIGINT, run_handler);
  do {
      printf ("Ange ett annat tal, eller avsluta med ctrl-c och valfritt input:");
      scanf ("%s", &b); // scanf("%s", &b)
      if (run) {
        printf("creating list\n");
        head2 = create_list(b);
        test_list(head2);
        printf("list created\n");
        printf("adding lists\n");
        add_lists(head1, head2); // <---- culprit. free_list()  some sort of memory leak in here
        printf("lists added\n");
        // potentially dealloc a, b, separate function iterating through all list items // not necessary, a, b const char[512]. head2 might need deallocation however. deallocat a aswell.
        // possible that old tail pointers indicate larger numbers than necessary. however, this should not be a problem given the create_list constructor ending in NULL!
        // test_list(head1); // should show updated list!
        // need to deallocate head2 since it changes every time
        //test_list(head1);
        update_sum(head1, a); // pretty much works always, does not cause crash
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
  printf("exited");
return 0;
}
