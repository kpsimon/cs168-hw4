#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include "vec3.h"

#define PI 3.14159265
#define ALPHA 0.7

using namespace std;

class ray {
    public:
        ray() {}
        ray(const vec3& a, const vec3& b) { A = a; B = b; }
        vec3 orgin() const     { return A; }
        vec3 direction() const { return B; }
        vec3 point_at_parameter(float t) const { return A + t*B; }

        vec3 A;
        vec3 B;
};

struct vector {
    float x;
    float y;
    float z;
} ;

//struct point {
    //float x;
    //float y;
    //float z;
//};

//float distance(point a, point b) {
    //float one = pow((a.x-b.x),2);
    //float two = pow((a.y-b.y),2);
    //float three = pow((a.z-b.z),2);

    //float distance = sqrt(one+two+three);
    //return distance;
//}

//float area(point a, point b, point c){
   //return abs((a.x*(b.y-c.y) + b.x*(c.y-a.y)+ c.x*(a.y-b.y))/2.0);
//}

//struct Sphere {
    //point center;
    //float radius;
    //float color[3];

    //bool inSphere(point thePoint){
        //float theDistance = distance(thePoint, center);
        //if (theDistance <= radius) {
            //return true;
        //}
        //else {
            //return false;
        //}
    //}
//};

//struct Triangle {
    //point a;
    //point b;
    //point c;
    //float color[3];
//
    //bool isInside(point thePoint) {
   /* Calculate area of triangle ABC */
   //float A = area (a,b,c);

   /* Calculate area of triangle PBC */
   //float A1 = area (thePoint, b, c);

   /* Calculate area of triangle PAC */
   //float A2 = area (a, thePoint, c);

   /* Calculate area of triangle PAB */
   //float A3 = area (a, b, thePoint);

   /* Check if sum of A1, A2 and A3 is same as A */
   //return (A == A1 + A2 + A3);
    //}
//};

//vector normalize_vector(vector vec){
    //vector normalized;
    //float sum = pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2);
    //float divide = sqrt(sum);

    //normalized.x = float(vec.x / divide);
    //normalized.y = float(vec.y / divide);
    //normalized.z = float(vec.z / divide);

    //return normalized;
//}

//point RayTrace (vec3 camera, float t, vec3 direction) {
    //point thePoint;
    //thePoint.x = camera.x + t * direction.x;
    //thePoint.y = camera.y + t * direction.y;
    //thePoint.z = camera.z + t * direction.z;
    //return thePoint;
//}

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

    glBegin(GL_POLYGON);
    glColor3f(0.5,1,0);
    glVertex3f(1,1,0);
    glVertex3f(9,1,0);
    glVertex3f(9,9,0);
    glVertex3f(1,9,0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("image");
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
