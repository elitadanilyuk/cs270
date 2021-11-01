/* CS270 
 *
 * Author: Elita Danilyuk
 * Date:   11/27/21
 */

#include "struct.h"
#include<stdio.h>
#include<stdlib.h>

/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student **slot)
{
    Student* newStudent = (Student *)calloc(1, sizeof(Student));
    scanf("%s", (newStudent->firstName));
    scanf("%f", &(newStudent->qualityPoints));
    scanf("%d", &(newStudent->numCredits));
    //*newStudent = **slot;
    *slot = newStudent;
}

void displayStudent(Student s)
{
    float GPA = s.qualityPoints / s.numCredits;
    printf("%s, %.2f\n", s.firstName, GPA);
}