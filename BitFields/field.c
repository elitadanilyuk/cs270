#include "field.h"

/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author Elita
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
    return ((value >> position) & 1);
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
    return (value | (1 << position));
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
    return (value &= ~(1 << position));
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
    return 0;
}
