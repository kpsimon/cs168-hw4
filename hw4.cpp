#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct vector {
  float x;
  float y;
  float z;
} ;

vector normalize_vector(vector vec){
    vector normalized;
    float sum = pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2);
    float divide = sqrt(sum);

    normalized.x = float(vec.x / divide);
    normalized.y = float(vec.y / divide);
    normalized.z = float(vec.z / divide);

    return normalized;
}

void redraw( void ){

}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("HW4");
    glutPositionWindow(10,10);
    glutReshapeWindow(1000,1500);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,10.0,0.0,10.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(redraw);
    glutMainLoop();
    return 0;
}