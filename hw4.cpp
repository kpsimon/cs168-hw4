
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define ALPHA 0.7

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

//draws polygons
void redraw ( void ) {
    const GLfloat light_ambient[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // If w is 0, it is directional. If w is 1, it is positional.
    const GLfloat light_position[] = { 5.0f, 5.0f, 5.0f, 0.0f };
    //const GLfloat light_position[] = { 2.0f, 2.0f, -20.0f, 1.0f };
    glEnable(GL_LIGHT0);    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("polygons");
    glutPositionWindow(10,10);
    glutReshapeWindow(1000,1500);
    glClearColor(0.5,0.0,0.0,ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,10,0.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(redraw);
    glutMainLoop();
    return 0;
}

