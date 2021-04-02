#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

volatile sig_atomic_t run = 1;

void run_handler(int handle) {
    run = 0;
}

struct List_item {
    int num;
    struct List_item *tail;
};

typedef struct List_item list_item;

struct Sum_carry {
    int sum;
    int carry;
};

typedef struct Sum_carry sum_carry;

list_item *create_item (int list_input) {
    list_item *new_item = (list_item *)malloc(sizeof(new_item));
    new_item->num = list_input;
    new_item->tail = 0;
    return new_item;
}

list_item *create_list (char *user_input) {
    // reverse user input
    // malloc
    // construct list of list
    // set last pointer to NULL
    int digits = strlen(user_input);
    char *reverse = strrev(user_input); // strrev reverses in-place!
    //printf("%s \n", reverse);
    list_item *lsd = create_item((int) (reverse[0])-48); // '0'
    list_item *head = lsd;
    int i;
    for (i=1; i<digits; ++i){
        list_item *dig = create_item((int) (reverse[i])-48);
        lsd->tail = dig;
        lsd = dig;
    }
    return (head);
}

int add_carry(int a, int b, int d) { // to be used for each digit in linked lists, works as intended. To return both values, consider converting to sum_carry
    int s = a + b + d;
    int c = 0;
    if (s >= 10) {
        c = 1;
        s = s - 10;
    }
    return s; // only one value can be returned, use separate add cary
}

sum_carry add_carry2(int a, int b, int d) {
    int s = a + b + d;
    int c = 0;
    if (s >= 10) {
        c = 1;
        s = s - 10;
    }
    sum_carry sc;
    sc.sum = s;
    sc.carry = c;
    return sc;
}

void free_list(list_item *head){
    //printf("entering free_list \n");
    while (head->tail != 0) { 
        list_item *next = head->tail;
        //printf("freeing %p \n", head);
        free(head); 
        head = next;
        //printf("next is %p \n", next);
    }
    //printf("freeing final\n");
    free(head);
    head = NULL;
}

void test_list(list_item *head){
    while(head->tail !=0){
        printf("%d \n", head->num);
        head = head->tail;
    };
    printf("%d \n", head->num);
}

void add_lists (list_item *list1, list_item *list2) { // void method - list1 values are changed and updated in-place
    sum_carry sc;
    list_item *head1 = list1; // only saved for debugging
    list_item *head2 = list2; // saved for freeing. does not change during code execution.
    sc.sum = 0;
    sc.carry = 0;
    
    while((list1->tail != 0) && (list2->tail != 0)){ // basic case, neither last element of list1 nor list2. addition can crash here if list2 is multi digit!
        //printf("1: no NULL loop\n");
        sc = add_carry2(list1->num, list2->num, sc.carry);
        list1->num = sc.sum;
        list1 = list1->tail;
        list2 = list2->tail;
        //printf("list1 is %p \n", list1);
        //printf("list2 is %p \n", list2);
    }
    //printf("list1 is %p \n", list1);
    //printf("list2 is %p \n", list2);
    if ((list1->tail == 0) && (list2->tail == 0)) { // list1, list2 of equal length
        sc = add_carry2(list1->num, list2->num, sc.carry);
        list1->num = sc.sum;
        //printf("2a:  list1 == list2 length\n");
    }
    if (list1->tail != 0) { // if list1 longer than list2
        sc = add_carry2(list1->num, list2->num, sc.carry);
        list1->num = sc.sum;
        list1 = list1->tail;
        //printf("2b:  list1 > list2\n");
        //printf("list1 is %p \n", list1);
        //printf("list2 is %p \n", list2);
        while(list1->tail != 0){// crashes here at final execution (i.e. when list1->tail == 0)
            //printf("2b: loop\n");
            sc = add_carry2(list1->num, 0, sc.carry);
            //printf("2b: loop added\n");
            list1->num = sc.sum; 
            list1 = list1->tail; //
            //printf("list1 is %p \n", list1);
            //printf("list2 is %p \n", list2);
        } 
        //printf("adding last\n");
        sc = add_carry2(list1->num, 0, sc.carry);
        //printf("last added\n");
        list1->num = sc.sum;
    }
    // This causes problems - list1 expands into list2?
    if (list2->tail != 0) { // if list2 longer than list1
        sc = add_carry2(list1->num, list2->num, sc.carry);
        list1->num = sc.sum;
        list2 = list2->tail;
        //printf("2c:  list2 > list1\n");
        while(list2->tail != 0){ // can still go to 000
            //printf("2c: loop\n");
            sc = add_carry2(list2->num, 0, sc.carry); // may crash here
            //printf("2c: loop added\n");
            list_item *dig = create_item(sc.sum); // create new list1 element
            list1->tail = dig;
            list1 = dig;
            list2 = list2->tail; // here it breaks dereferencing null pointer
            //printf("list1 is %p \n", list1);
            //printf("list2 is %p \n", list2);
        }
        sc = add_carry2(list2->num, 0, sc.carry);
        list_item *dig = create_item(sc.sum); // create new list1 element
        list1->tail = dig;
        list1 = dig;
        //printf("list1 is %p \n", list1); // riddle me this
    }
    //printf("2: done\n");
    if (sc.carry != 0) { // create new list1 element, insert carry in num, tail->NULL
        //printf("final carry addition\n");
        list_item *dig = create_item(sc.carry); // or here
        list1->tail = dig;
        list1 = dig;
    }
    //printf("freeing list2 \n");
    //printf("list1 is %p \n", list1); // sometimes moves into list2 causing crash!!
    //test_list(head1);
    //printf("list2 is %p \n", list2);
    //test_list(head2);
    free_list(head2);
    printf("list2 freed \n");
}


void update_sum(list_item *head, char *a_item){ // updates char from result in linked list
    char *buffer = malloc(512);
    int max_len = 512;
    int length = 0;
    // printf("entering update sum\n");
    while (head->tail != 0 && length<= max_len) { 
        //printf("head->tail is: %s \n", head); 
        //printf("entering head->tail\n");
        length += snprintf(buffer+length, max_len-length, "%c", head->num + '0');
        //puts(buffer);
        //printf("next \n");
        head = head->tail;
    };
    snprintf(buffer+length, max_len-length, "%c", head->num + '0'); // final num
    strrev(buffer);
    strcpy(a_item, buffer);
    free(buffer);
}

int sum_list (list_item *list) { // old
    int sum = 0;
    while (list != NULL) {
        sum += list->num;
        list = list->tail;
    }
    return sum;
}
