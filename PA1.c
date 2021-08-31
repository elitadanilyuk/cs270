// P1 Assignment
// Author: Elita Danilyuk
// Date:   08/30/2021
// Class:  CS270
// Email:  elita@colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// example of a global array
// int exampleGlobalArray[2];

double input[5];
double output[4];

// this function can be used as a guide for the funtions you will implement
void computeCircle(double radius, double *addressOfArea){
    // Compute area
    double result = 3.141593 * radius * radius;

    // Dereference pointer to return result
    *addressOfArea = result;
}

// this function comutes the volume of a sphere given the radius value
void computeSphere(double radius, double *addressOfArea){
    // Compute volume
    double result = (4.0 / 3.0) * 3.141593 * radius * radius * radius;

    // Dereference pointer to return result
    *addressOfArea = result;
}

// this function computes the volume of a cube given the side value
void computeCube(double side, double *addressOfArea){
    // Compute cube
    double result = side * side * side;

    // Dereference pointer to return result
    *addressOfArea = result;
}

// this function computes the volume of a tetrahedron given the side value
void computeTetrahedron(double side, double *addressOfArea){
    // Compute tetrahedron
    double result = 0.117851 * side * side * side;

    // Dereference pointer to return result
    *addressOfArea = result;
}


//this function computes the volume of a cylinder given the values for the radius and height
void computeCylinder(double radius, double height, double *addressOfArea){
    // Compute cylinder
    double result = 3.141593 * radius * radius * height;

    // Dereference pointer to return result
    *addressOfArea = result;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 6) {
        printf("usage: ./P1 <double> <double> <double> <double> <double>\n");
        return EXIT_FAILURE;
    }

    // TODO? Step 9

    // Parse arguments
    double radius = atof(argv[1]);
    double cubeSide = atof(argv[2]);
    double tetrahedronSide = atof(argv[3]);
    double cylinderRadius = atof(argv[4]);
    double cylinderHeight = atof(argv[5]);

    // Local variable
    double area;

    // Call function
    // computeCircle(radius, &area);

    // Print area
    // printf("The area of a circle with radius %.5f equals %.5f.\n", radius, area);

    // Call SPHERE
    computeSphere(radius, &area);

    // Print SPHERE area
    printf("SPHERE, radius = %.5f, volume = %.5f.\n", radius, area);

    // Call CUBE
    computeCube(cubeSide, &area);

    // Print CUBE area
    printf("CUBE, side = %.5f, volume = %.5f.\n", cubeSide, area);

    // Call TETRAHEDRON
    computeTetrahedron(tetrahedronSide, &area);

    // Print TETRAHEDRON area
     computeTetrahedron(tetrahedronSide, &area);

    // Print TETRAHEDRON area
    printf("TETRAHEDRON, side = %.5f, volume = %.5f.\n", tetrahedronSide, area);

    // Call CYLINDER
    computeCylinder(cylinderRadius, cylinderHeight, &area);

    // Print CYLINDER area
    printf("CYLINDER, radius = %.5f, height = %.5f, volume = %.5f.\n", cylinderRadius, cylinderHeight, area);

    // Return success
    return EXIT_SUCCESS;
}
