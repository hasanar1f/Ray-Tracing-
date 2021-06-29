//
//  1605034_classes.h
//  OpenGL
//
//  Created by Hasan Ibn Arif Efaz on 25/6/21.
//


#include<stdio.h>
#include <vector>
#include<iostream>
#include<stdlib.h>
#include<math.h>

#ifdef __APPLE__

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#else

#include <glut.h>
#include <windows.h>

#endif

#include "bitmap_image.hpp"
#define pi (2*acos(0.0))


using namespace std;


/////////////////////////////////////////// Class ///////////////////////////////////////// // / /


class Vector
{
public:
    double ax, ay, az;

    Vector(double ax=0, double ay=0, double az=0)
    {
        this->ax = ax;
        this->ay = ay;
        this->az = az;
    }

    void normalize()
    {
        double r = sqrt((ax * ax) + (ay * ay) + (az * az));
        ax = ax / r;
        ay = ay / r;
        az = az / r;
    }

    Vector operator+(Vector v)
    {
        Vector temp;
        temp.ax = this->ax + v.ax;
        temp.ay = this->ay + v.ay;
        temp.az = this->az + v.az;

        return temp;
    }

    Vector operator-(Vector v)
    {
        Vector temp;
        temp.ax = this->ax - v.ax;
        temp.ay = this->ay - v.ay;
        temp.az = this->az - v.az;

        return temp;
    }

    Vector &operator=(Vector v)
    {
        this->ax = v.ax;
        this->ay = v.ay;
        this->az = v.az;

        return *this;
    }

    Vector operator*(double d)
    {
        Vector temp;
        temp.ax = ax * d;
        temp.ay = ay * d;
        temp.az = az * d;
        return temp;
    }
    void print()
    {
        cout << ax << " " << ay << " " << az << endl;
    }

    double dot(Vector x)
    {
        return (this->ax * x.ax) + (this->ay * x.ay) + (this->az * x.az);
    }

    Vector cross(Vector x)
    {
        Vector temp;
        temp.ax = (ay * x.az - az * x.ay);
        temp.ay = (az * x.ax - ax * x.az);
        temp.az = (ax * x.ay - ay * x.ax);
        return temp;
    }

    
};



class Point{
public:
    double x,y,z ;
    Point(double x=0,double y=0,double z=0){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point operator+(Point v)
    {
        Point temp;
        temp.x = this->x + v.x;
        temp.y = this->y + v.y;
        temp.z = this->z + v.z;
        return temp;
    }
    
    Point operator+(Vector v)
    {
        Point temp;
        temp.x = this->x + v.ax;
        temp.y = this->y + v.ay;
        temp.z = this->z + v.az;
        return temp;
    }
    
    
    Point operator-(Vector v)
    {
        Point temp;
        temp.x = this->x - v.ax;
        temp.y = this->y - v.ay;
        temp.z = this->z - v.az;
        return temp;
    }

    Point operator-(Point v)
    {
        Point temp;
        temp.x = this->x - v.x;
        temp.y = this->y - v.y;
        temp.z = this->z - v.z;
        return temp;
    }

    Point &operator=(Point v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;

        return *this;
    }

    double distance(Point a){
        Point tem = *this - a ;
        return abs(sqrt(tem.x*tem.x+tem.y*tem.y+tem.z*tem.z)) ;
    }

    void print(){
        cout<<"( "<<x<<" , "<<y<<" , "<<z<<" )"<<endl;
    }

};

Vector getVector(Point a,Point b){ //to generate vector AB
    Vector temp ;
    temp.ax = b.x - a.x ;
    temp.ay = b.y - a.y ;
    temp.az = b.z - a.z ;

    return temp ;
}

Point lineParametric(Point p,Vector v,double t){
    Point new_point ;
    new_point.x = p.x + v.ax*t ;
    new_point.y = p.y + v.ay*t ;
    new_point.z = p.z + v.az*t ;

    return new_point ;
}
 //////////////////////////////


class Color{
    
public:
    double r,g,b;
    Color(double R,double G, double B) {
        r = R; g = G; b = B;
    }
    
    Color() {
        r = 0; g = 0; b = 0;
    }
    
    Color operator+(Color a){
           Color temp;
           temp.r = this->r+a.r;
           temp.g = this->g+a.g;
           temp.b = this->b+a.b;
           return temp;
       }

   Color operator+(double a){
       Color temp;
       temp.r = this->r+a;
       temp.g = this->g+a;
       temp.b = this->b+a;
       return temp;
   }

   Color operator*(double a)
   {
       Color temp;
       temp.r = this->r*a;
       temp.g = this->g*a;
       temp.b = this->b*a;
       return temp;
   }

   Color &operator=(Color c)
   {
       this->r = c.r;
       this->g = c.g;
       this->b = c.b;

       return *this;
   }
};


class Ray {
    
public:
    Point start;
    Vector direction;
    
    Ray(Point start, Vector direction) {
        this->start = start;
        this->direction = direction;
    }
    
    
        
};



class Object{
    
public:
    enum type {primary, secondary} ;
    Point reference_point;
    Color color;
    double a,d,s,r,shine; // all reflection co-effs and exponent term of specular comp
    double lenght, width, height;
    Vector normal;
    
    // constructor

    void setRefPoint(Point p) {
        this->reference_point = p;
    }
    
    void setDimension(double l,double w,double h) {
        this->lenght = l;
        this->width = w;
        this->height = h;
    }
    
    void setColor(Color color) {
        this->color = color;
    }
    
    void setShine(double shine) {
        this->shine = shine;
    }
    
    void setCoEfficients(double a,double d, double s, double r) {
        this->a = a;
        this->d = d;
        this->s = s;
        this->r = r;
    }
    
    // pore = 0 kore dibo
    
    virtual double getParametricValue(Ray *r){
        
        return 0;
    };
    
    virtual double intersect(Ray *r,Color *color,int level) {
        return -1;
    } ;
    
    
    virtual void draw() = 0;
};

class Light {
  
public:
    
    Point light_pos;
    Color color;
    
    Light(Point p,Color c) {
        this->light_pos = p;
        this->color = c;
    }
    
    
};

vector<Object*> objects;
vector<Light*> lights;

class Square : public Object {
    
public:
    
    Point corner;
    Color color;
    double size;
    

    Square(Point p,Color c,double s) {
        corner = p;
        color = c;
        size = s;
        
        normal = Vector(0,0,1);
    }
 

    
    void draw()
    {
        glColor3f(color.r,color.g,color.b);
        glBegin(GL_QUADS);{
            glVertex3f(corner.x,corner.y,corner.z);
            glVertex3f(corner.x,corner.y+size,corner.z);
            glVertex3f(corner.x+size,corner.y+size,corner.z);
            glVertex3f(corner.x+size,corner.y,corner.z);
        }glEnd();
    }
    
    double intersect(Ray r,Color *color,int level) {
        
        
        return  -1.0;
    }
};

class CheckerBoard : public Object {

public:
    int N;
    int size;
    bool toggle;
    CheckerBoard(int N,int size){
        this->N = N;
        this->size = size;
    }
    void draw(){
        toggle = true;
            for(double i=-size*N;i<=size*N;i+=size){
                for(double j=-size*N;j<=size*N;j+=size){
                    
                    if(toggle)
                        Square(Point(i,j,0),Color(0,0,0),size).draw();
                    else
                        Square(Point(i,j,0),Color(1,1,1),size).draw();
                    toggle  = !toggle;
                }
            }
    }
    
    double intersect(Ray r,Color *color,int level) {
        
        // which
        
        
        
        return  -1;
    }
};


class Sphere : public Object {
    
public:
    double radius;
    
    Sphere(Point center, double radius) {
        this->reference_point = center;
        this->radius = radius;
    }
    

    
    void drawSphere(double radius,int slices,int stacks)
    {
        Point p[stacks + 1][slices + 1];
        double h, r, angle1, angle2;
        for (int i = 0; i <= stacks; i++)
        {
            angle1 = ((double)i / (double)stacks) * (acos(-1.0)*2);
            h = radius * sin(angle1);
            r = radius * cos(angle1);
            for (int j = 0; j <= slices; j++)
            {
                angle2 = ((double)j / (double)slices) * acos(-1.0) * 2;
                p[i][j].x = r * cos(angle2);
                p[i][j].y = r * sin(angle2);
                p[i][j].z = h  ;
            }
        }
        for (int i = 0; i < stacks; i++)
        {
            for (int j = 0; j < slices; j++)
            {
                glBegin(GL_QUADS);
                {
                    glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
                    glVertex3f(p[i][j + 1].x, p[i][j + 1].y, p[i][j + 1].z);
                    glVertex3f(p[i + 1][j + 1].x, p[i + 1][j + 1].y, p[i + 1][j + 1].z);
                    glVertex3f(p[i + 1][j].x, p[i + 1][j].y, p[i + 1][j].z);
                }
                glEnd();
            }
        }
        
        
    }
    
    void draw() {
       glPushMatrix() ;
           glTranslated(reference_point.x,reference_point.y,reference_point.z);
           glColor3f(color.r,color.g,color.b);
           drawSphere(radius,50,50);
       glPopMatrix() ;
        
    }
    
    double getParametricValue(Ray *r) {
        
       Vector r0 = getVector(reference_point,r->start);
       Vector rd = r->direction;
       double a = 1 ;
       double b = 2*r0.dot(rd);
       double c = r0.dot(r0)- radius*radius;
       double d = b*b - (4*a*c) ;

       if(d<0){
           return -1 ;
       }

       double alpha = (-b + sqrt(d))/2 ;
       double beta = (-b - sqrt(d))/2 ;

       return min(alpha,beta);
    }
    
    double intersect(Ray *r,Color *out_color,int level) {
        
        
        
        double t = getParametricValue(r);
        
        if(t<1) return -1;
        if(level==0) return t;
        
        Point ip = lineParametric(r->start,r->direction,t) ;
        Vector n = getVector(reference_point,ip);
        n.normalize() ;
        
        *out_color = this->color * a;
        
        for(int i=0;i<lights.size();i++) {
            
               Vector l_dir = getVector(ip,lights[i]->light_pos);
               l_dir.normalize();
               Point s_p = lineParametric(ip,l_dir,1);
               Vector s_l = getVector(s_p,lights[i]->light_pos);
               s_l.normalize() ;
               Ray *l_r = new Ray(s_p,s_l) ;
//               int touch = 0 ;
//               double distance = s_p.distance(lights[i]->light_pos);
            

          /// touch check
                   
               Ray indt(lights[i]->light_pos,l_dir*-1);
               Vector light_ref = n*(2.0*indt.direction.dot(n)) - indt.direction ;
               light_ref.normalize();
               double lambert = l_r->direction.dot(n);
               double phong = pow((r->direction*-1).dot(light_ref),shine) ;
               lambert = max(lambert,0.0);
               phong = max(phong,0.0);

               *out_color = *out_color + (lambert*d + phong*s);
            
            
           
            
            }
        
        return  t;
    }
};

class Triangle:public Object{
public:
    Point a,b,c ;

    Triangle(Point x,Point y,Point z){
           this->a = x ;
           this->b = y ;
           this->c = z ;
    }
    
    void draw(){
        glColor3f(color.r,color.g,color.b);
        glBegin(GL_TRIANGLES);
        glVertex3d(a.x,a.y,a.z);
        glVertex3d(b.x,b.y,b.z);
        glVertex3d(c.x,c.y,c.z);
        glEnd();
    }
    
    double intersect(Ray r,Color *color,int level) {
        
        
        return  -1;
    }
    
};



class General : public Object {
public:
    double A, B, C, D, E, F, G, H, I, J;
    
    General(double A,double B,double C,double D,double E,double F,double G,double H, double I, double J) {
        
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
        this->E = E;
        this->F = F;
        this->G = G;
        this->H = H;
        this->I = I;
    }
    
    void draw(){
        // nothing to do!
    }
    
    double intersect(Ray r,Color *color,int level) {
        
        
        return  -1;
    }
    
    
};








