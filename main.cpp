#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define ALPHA 0.7
#define kEpsilon 2.2204460492503130808472633361816
using namespace std;



struct vec3{
    float x;
    float y;
    float z;

};

vec3 crossProduct(vec3 a, vec3 b) {
    vec3 theCross;
    theCross.x = a.y * b.z - a.z * b.y;
    theCross.y = a.x * b.z - a.z * b.x;
    theCross.z = a.x * b.y - a.y * b.x;
    return theCross;

}

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

struct triangle {
    vec3 a;
    vec3 b;
    vec3 c;
};

float length(vec3 a) {
    float xSquared = pow(a.x,2);
    float ySquared = pow(a.y,2);
    float zSquared = pow(a.z,2);
    return sqrt(xSquared + ySquared + zSquared);
}

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

vec3 add(vec3 x, vec3 y) {
    vec3 final;
    final.x = x.x + y.x;
    final.y = x.y + y.y;
    final.z = x.z + y.z;
    return final;
}

vec3 mult(vec3 x, float fact) {
    vec3 final;
    final.x = x.x * fact;
    final.y = x.y * fact;
    final.x = x.z * fact;
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

bool rayTriangleIntersect(const vec3 &orig, const vec3 &dir, const vec3 &v0, const vec3 &v1, const vec3 &v2,float &t){
    // compute plane's normal
    vec3 v0v1 = sub(v1,v0);
    vec3 v0v2 = sub(v2,v0);
    // no need to normalize
    vec3 N = crossProduct(v0v1, v0v2); //N
    float area2 = length(N);

    // Step 1: finding P

    // check if ray and plane are parallel ?
    float NdotRayDirection = dot(N,dir);
    if (fabs(NdotRayDirection) < 0.1) // almost 0
        return false; // they are parallel so they don't intersect !

    // compute d parameter using equation 2
    float d = dot(N,v0);

    // compute t (equation 3)
    t = (dot(N,orig) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind

    // compute the intersection point using equation 1
    //vec3 P = orig + t * dir;
    vec3 P = add(orig, mult(dir,t));

    // Step 2: inside-outside test
    vec3 C; // vector perpendicular to triangle's plane

    // edge 0
    vec3 edge0 = sub(v1, v0);
    vec3 vp0 = sub(P, v0);
    //C = edge0.crossProduct(vp0);
    C = crossProduct(edge0,vp0);
    if (dot(N,C) < 0) return false; // P is on the right side

    // edge 1
    vec3 edge1 = sub(v2,v1);
    vec3 vp1 = sub(P,v1);
    //C = edge1.crossProduct(vp1);
    C = crossProduct(edge1,vp1);
    if (dot(N,C) < 0)  return false; // P is on the right side

    // edge 2
    vec3 edge2 = sub(v0,v2);
    vec3 vp2 = sub(P,v2);
    C = crossProduct(edge2,vp2);
    if (dot(N,C) < 0) return false; // P is on the right side;

    return true; // this ray hits the triangle
}

bool hit_triangle(const triangle theTri, const ray r, const vec3 theCamera, const vec3 theDirection, float theArray[3]) {
    vec3 edge0 = sub(theTri.a,theTri.b);
    vec3 edge1 = sub(theTri.b,theTri.c);
    vec3 edge2 = sub(theTri.a,theTri.c);
    vec3 n = crossProduct(edge0,edge1);
    float k = dot(theTri.a,n);
    float t = (k - dot(theTri.a,n))/(dot(r.direction(),n));

    vec3 bigR = r.point_at_parameter(t);
    bool a = (dot(crossProduct(edge0,sub(bigR,theTri.a)),n) > 0);
    bool b = (dot(crossProduct(edge1,sub(bigR,theTri.b)),n) > 0);
    bool c = (dot(crossProduct(edge2,sub(bigR,theTri.c)),n) > 0);

    theArray[0] = bigR.x;
    theArray[1] = bigR.y;
    theArray[2] = bigR.z;

    if (a&&b&&c) {
        return true;
    }
    else {
        return false;
    }
}

void redraw ( void ) {
    const GLfloat light_ambient[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // If w is 0, it is directional. If w is 1, it is positional.
    //const GLfloat light_position[] = { 500.0f, 500.0f, -1000.0f, 0.0f };
    const GLfloat light_position[] = { 2.0f, 2.0f, -20.0f, 1.0f };
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

    const GLfloat mat_ambient[] = {0.04f, 0.3f, 0.1f, 1.0f};
    const GLfloat diffuse_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat mat_specular[] = {.5f, 0.2f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    vec3 camera;
    camera.x = 500;
    camera.y = 500;
    camera.z = -1000;

    vec3 sphere_center;
    sphere_center.x = 500;
    sphere_center.y = 500;
    sphere_center.z = 0;

    triangle tri;
    tri.a.x = 250;
    tri.a.y = 700;
    tri.a.z = 0;
    tri.b.x = 700;
    tri.b.y = 700;
    tri.b.z = 0;
    tri.c.x = 500;
    tri.c.y = 900;
    tri.c.z = 0;

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
                float theArray[3];
                if (hit_triangle(tri,r,camera,dir,theArray)) {
                    glColor3f(1.0, 0.0, 0.0);
                    glVertex3f(theArray[0], theArray[1], theArray[2]);
                }
                else {
                    glColor3f(0.0, 1.0, 0.0);
                    glVertex3f(j, i, 0);
                }
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
