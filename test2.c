#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <crtdbg.h>
#include <C:\Users\Hilding\documents\repos\C\functions.h>
// New architecture - create two separate lists a,b as per usual, save result in a new list s, deallocate through each iteration
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
      printf("creating list\n");
      head2 = create_list(b);
      test_list(head2);
      printf("list created\n");
      // printf("%d \n", head2->tail->tail->num);
      // Båda listorna skapas korrekt. Kan köras hur många gånger som helst
      if (1) {
        // test_list(head1); // funkar
        printf("adding lists\n");
        add_lists2(head1, head2); // <---- culprit. free_list()  some sort of memory leak in here
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
  } while(1);
  // printf("Summan blev: %d\n", a);
  // save to result.txt
  printf("exited");
return 0;
}