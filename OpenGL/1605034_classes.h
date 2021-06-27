//
//  1605034_classes.h
//  OpenGL
//
//  Created by Hasan Ibn Arif Efaz on 25/6/21.
//

#ifndef _605034_classes_h
#define _605034_classes_h


#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include <vector>
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#define pi (2*acos(0.0))

using namespace std;


/////////////////////////////////////// Functions ////////////////////////////////// // /











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

//    Vector generateVector(Point a,Point b){ //to generate vector AB
//        Vector temp ;
//        temp.ax = b.x - a.x ;
//        temp.ay = b.y - a.y ;
//        temp.az = b.z - a.z ;
//
//        return temp ;
//    }
    
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



class Color{
    
public:
    double r,g,b;
    Color(double R,double G, double B) {
        r = R; g = G; b = B;
    }
    
    Color() {
        r = 0; g = 0; b = 0;
    }
};




class Object{
    
public:
    int type ;
    Point reference_point;
    Color color;
    double a,d,s,r,shine; // all reflection co-effs and exponent term of specular comp
    
    // constructor
    Object() {
        
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
    
    
    
//    virtual double getParametricValue(Ray r) = 0;
//    virtual double getColor(Ray r,Color *color,int level) = 0 ;
    
    
    virtual void draw() = 0;
};

class Square : public Object {
    
public:
    
    Point corner;
    Color color;
    double size;
    

    Square(Point p,Color c,double s) {
        corner = p;
        color = c;
        size = s;
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
};

class CheckerBoard : public Object {

public:
    int N;
    int size;
    bool toggle = true;
    CheckerBoard(int N,int size){
        this->N = N;
        this->size = size;
    }
    void draw(){
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
        struct Point Points[100][100];
        int i,j;
        double h,r;
        //generate Points
        for(i=0;i<=stacks;i++)
        {
            h=radius*sin(((double)i/(double)stacks)*(pi/2));
            r=radius*cos(((double)i/(double)stacks)*(pi/2));
            for(j=0;j<=slices;j++)
            {
                Points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
                Points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
                Points[i][j].z=h;
            }
        }
        //draw quads using generated Points
        for(i=0;i<stacks;i++)
        {
            glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            for(j=0;j<slices;j++)
            {
                glBegin(GL_QUADS);{
                    //hemisphere
                    glVertex3f(Points[i][j].x,Points[i][j].y,Points[i][j].z);
                    glVertex3f(Points[i][j+1].x,Points[i][j+1].y,Points[i][j+1].z);
                    glVertex3f(Points[i+1][j+1].x,Points[i+1][j+1].y,Points[i+1][j+1].z);
                    glVertex3f(Points[i+1][j].x,Points[i+1][j].y,Points[i+1][j].z);

                }glEnd();
            }
        }
    }
    
    void draw() {
       glPushMatrix() ;
           glTranslated(reference_point.x,reference_point.y,reference_point.z);
           glColor3f(color.r,color.g,color.b);
           drawSphere(radius,25,25);
       glPopMatrix() ;
    }
};

class Light {
  
public:
    
    Point light_pos;
    Color color;
    
    
};





extern vector<Object> objects;
extern vector<Light> lights;

#endif /* _605034_classes_h */




