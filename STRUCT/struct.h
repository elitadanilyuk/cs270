/* CS270 
 *
 * Author: Elita Danilyuk
 * Date:   11/27/21
 */
 
/********** STRUCTURE DEFINITION **********************************************/

// Structure that represents a student
typedef struct
{
  // TODO: Add required members
  char firstName[80];
  float qualityPoints; //aka GPA
  int numCredits;
} Student;

// Structure that represents a class roster
// TODO: Declare this structure
typedef struct{
  int numStudents;
  Student** students; // dynamically allocated array of students
} ClassRoster;

/********** FUNCTION PROTOTYPES ***********************************************/

// add student to roster
void readStudentAndEnroll(Student **slot);

void displayStudent(Student s);
