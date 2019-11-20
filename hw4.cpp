
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define ALPHA 0.7

using namespace std;



struct vec3{
    float x;
    float y;
    float z;
};

class ray {
    public:
        ray() {}

        ray(const vec3 a, const vec3 b) { 
            A = a; 
            B = b; 
        }
        vec3 orgin() const     { 
            return A; 
        }
        vec3 direction() const {
             return B; 
         }
        vec3 point_at_parameter(float t) const {
            vec3 temp;
            temp.x = t * B.x;
            temp.y = t * B.y;
            temp.z = t * B.z;

            vec3 final;
            final.x = A.x + temp.x;
            final.y = A.y + temp.y;
            final.z = A.z + temp.z;
            return final; 
        }

        vec3 A;
        vec3 B;
};

float dot(vec3 x, vec3 y){
    return ((x.x * y.x) + (x.y * y.y) + (x.z * y.z));
}

vec3 sub(vec3 x, vec3 y){
    vec3 final;
    final.x = x.x - y.x;
    final.y = x.y - y.y;
    final.z = x.z - y.z;
    return final;
}

float hit_sphere(const vec3 center, float radius, const ray r){
    vec3 oc = sub(r.orgin(), center);
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0){
        return -1.0;
    }
    else{
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

//draws polygons
void redraw ( void ) {
    const GLfloat light_ambient[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // If w is 0, it is directional. If w is 1, it is positional.
    const GLfloat light_position[] = { 500.0f, 500.0f, -1000.0f, 0.0f };
    //const GLfloat light_position[] = { 2.0f, 2.0f, -20.0f, 1.0f };
    glEnable(GL_LIGHT0);    
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    vec3 camera;
    camera.x = 500;
    camera.y = 500;
    camera.z = -1000;

    vec3 sphere_center;
    sphere_center.x = 500;
    sphere_center.y = 500;
    sphere_center.z = 0;

    glBegin(GL_POINTS);
    for(int i=0; i < 1000; ++i){
        for(int j=0; j<1000; ++j){
            vec3 point;
            point.x = j;
            point.y = i;
            point.z = 0;

            vec3 dir;
            dir.x = point.x - camera.x;
            dir.y = point.y - camera.y;
            dir.z = point.z - camera.z;

            ray r(camera, dir);
            float t = hit_sphere(sphere_center, 100.0, r);
            if(t > 0 || t == 0){
                vec3 intersection = r.point_at_parameter(t);
                glColor3f(1.0, 0.0, 0.0);
                glVertex3f(intersection.x, intersection.y, intersection.z);
            }else{
                glColor3f(0.0, 1.0, 0.0);
                glVertex3f(j, i, 0);
            }
        }
    }
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("hw4");
    glutPositionWindow(10,10);
    glutReshapeWindow(1000,1000);
    glClearColor(0.0,0.0,0.0,ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1000,0.0,1000,-1000.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(redraw);
    glutMainLoop();
    return 0;
}

