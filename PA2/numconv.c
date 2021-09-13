/**
 *  @author  Elita Danilyuk
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int_to_char (int value, int radix) {
  if ((value >= 0) & (value < radix)){
    if (value < 10){
      return ('0' + value);
    }
    else {
      value = value - 10;
      return ('A' + value);
    }
  } 
  else {
    return '?';
  }
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char_to_int (char digit, int radix) {
  if ((((digit - '0') >= 0) & ((digit - '7') < radix)) | 
      (((digit - 'W') >= 0) & ((digit - '7' - 'W') < radix))) {
        //come back if time
    if ((digit - '0') < 10) {
      return (digit - '0');
    }
    else if ((digit - '7') < 36) {
      return (digit - '7');
    }
    else {
      return (digit - 'W');
    }
  }
  else {
    return -1;
  }
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void div_rem (int numerator, int divisor, int* remainder, int* quotient) {
  do {
    *remainder = numerator / divisor; 
    *quotient = numerator % divisor;
  } while (*remainder > 0);
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii_to_int (int valueOfPrefix, int radix) {
  return -1;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int_to_ascii (int value, int radix) {
  
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac_to_double (int radix) {
  return -1.0;
}

