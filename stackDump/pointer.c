#include <stdio.h>
// stopped at Dumping the Stack

int main() {
    
    // Part 1
    int i;  	// an integer value
    int *pi;	// a pointer to an integer value
    
    i = -1;
    pi = &i ;	// set pi to the address of i
    
    // printing value of i, address, and value of pointer
    printf("i: %d, pi: %p > *pi: %d\n", i, pi, *pi);
    
    // place additional code here
    
    
    // Part 2
    int **ppi;
    ppi = &pi ; // set ppi to the address of pi
    
    printf("i: %d, pi: %p > *pi: %d, ppi: %p > **ppi: %d \n", i, pi, *pi, ppi, **ppi);
    //first half is the same as the first printf statement
    
    
    // Part 3
    int memory[] = {1,2,3,4,5,6,7,8,9};
    int *pm;

    pm = memory;  // &memory[0] is an alternative.
    for (int i=0; i<9; i++) {
        printf("pm: %p > *pm: %d\n", pm, *pm);
        pm++;
    }
    
    
    // Part 4
    int *nm;
    pm = memory;
    nm = (int *) *pm;
    printf ("pm: %p, nm: %p\n", pm, nm);
    
    
    // Part 5
    char *cp;
    cp = (char *) pm;
    
    //memory[0] = 0x12345678;
    
    for (int i=0; i<36; i++) {
      printf ("cp: %p > *cp: 0x%02X\n", cp, *cp);
      cp++;
      }
    
    return 0;    
}
