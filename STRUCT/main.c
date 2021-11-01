 /** @mainpage 
   *  \htmlinclude "STRUCTS.html"
   */
/* CS270 
 *
 * Author: Elita Danilyuk
 * Date:   11/27/21
 */
#include<stdio.h>
#include <stdlib.h>
#include "struct.h"

int main(int argc, const char **argv)
{
  // TODO: Complete the main function  
  int num_students;
  scanf("%d", &num_students);
  ClassRoster roster;
  roster.numStudents = num_students;
  roster.students = (Student**) calloc(num_students, sizeof(Student*));
  
  // step 3.3
  for(int i = 0; i < roster.numStudents; i++){
    //readStudentAndEnroll(roster.students + i); (works also)
    readStudentAndEnroll(&roster.students[i]);
  }

  // step 3.4
  for(int i = 0; i < roster.numStudents; i++){
    displayStudent(*roster.students[i]);
    free(roster.students[i]);
  }

  // step 3.5
  free(roster.students);
  return 0;
}
