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
#include<algorithm>
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include "bitmap_image.hpp"
#define pi (2*acos(0.0))
#define EPSILON 0.0000001


using namespace std;


/////////////////////////////////////////// Class ///////////////////////////////////////// // / /


int recursionLevel;

class Vector
{
public:
    double ax, ay, az;
    
    Vector() {
        ax = 0;
        ay = 0;
        az = 0;
    }

    Vector(double ax, double ay, double az)
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
    
    Point &operator=(Point v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;

        return *this;
    }


    Point operator-(Vector v)
    {
        Point temp;
        temp.x = this->x - v.ax;
        temp.y = this->y - v.ay;
        temp.z = this->z - v.az;
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




};

Vector getVector(Point a,Point b){
    Vector temp ;
    temp.ax = b.x - a.x ;
    temp.ay = b.y - a.y ;
    temp.az = b.z - a.z ;

    return temp ;
}

Point lineParametric(Point p,Vector v,double t){
    Point ret(p.x + v.ax*t, p.y + v.ay*t , p.z + v.az*t) ;
    return ret ;
}
 //////////////////////////////

double min(double l,double r) {
    return (l<r) ? l : r;
}

double max(double l,double r) {
    return (l<r) ? r : l;
}

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
           temp.r = min(this->r+a.r,1);
           temp.g = min(this->g+a.g,1);
           temp.b = min(this->b+a.b,1);
           return temp;
       }



   Color operator*(double a)
   {
       Color temp;
       temp.r = min(this->r*a,1);
       temp.g = min(this->g*a,1);
       temp.b = min(this->b*a,1);
       return temp;
   }
    
    Color operator*(Color a)
    {
        Color temp;
        temp.r = min(this->r*a.r,1);
        temp.g = min(this->g*a.g,1);
        temp.b = min(this->b*a.b,1);
        return temp;
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
    Point reference_point;
    Color color;
    double a,d,s,r,shine; // all reflection co-effs and exponent term of specular comp
    double length, width, height;
    Vector normal;
    
    // constructor

    void setRefPoint(Point p) {
        this->reference_point = p;
    }
    
    void setDimension(double l,double w,double h) {
        this->length = l;
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
    
    virtual double getT(Ray *r){
        
        return 0;
    }
    
    virtual double intersect(Ray *r,Color *color,int level) {
        return -1;
    }
    
    virtual Vector getNormal() {
        return Vector();
    }
    
    
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
    
    double intersect(Ray *r,Color *color,int level) {
        
        return  -1.0;
    }
};

class CheckerBoard : public Object {

public:
    int N;
    int size;
    bool toggle;
    bool **board;
    Color **textureMap;
    
    double textureHeight,textureWidth;
    int tx,ty;
    bitmap_image texture;
    
    CheckerBoard(int N,int size) {
        
        this->N = N;
        this->size = size;
    
        
        board = new bool* [2*N+1];
        
        for(int i=0;i<=2*N;i++) {
            board[i] = new bool();
        }
        
        toggle = false;
        for(int i=0;i<=2*N;i++){
            for(int j=0;j<=2*N;j++){
                
                board[i][j] = toggle;
                toggle = !toggle;
            }
        }
        
        // set other parameters
        
        a = 0.4;
        d = 0.2;
        s = 0.2;
        r = 0.2;
        shine = 3;
        
        /// texture data load
//        texture = bitmap_image("text.bmp");
//        textureWidth = texture.width();
//        textureHeight = texture.height();
//
//
//        tx = floor(textureWidth/size);
//        ty = floor(textureHeight/size);
//
//        textureMap = new Color* [size];
//
//        for(int i=0;i<size;i++) {
//            textureMap[i] = new Color();
//        }
//
//        for(int i=0;i<size;i++) {
//            for(int j=0;j<size;j++) {
//                unsigned char r,g,b;
//                texture.get_pixel(i, j, r, g, b);
//                textureMap[i][j] = Color(r/255.0,g/255.0,b/255.0);
//            }
//        }


        

    }
    
    ~CheckerBoard() {
        delete [] board;
        delete [] textureMap;
    }
    
    void draw(){
        toggle = true;
            for(double i=-size*N;i<=size*N;i+=size){
                for(double j=-size*N;j<=size*N;j+=size){
                    
                    if(toggle) {
                        Square(Point(i,j,0),Color(0,0,0),size).draw();
                    }
                    else {
                        Square(Point(i,j,0),Color(1,1,1),size).draw();
                    }
                    toggle  = !toggle;
                }
            }
    }
    
    Vector getNormal() {
        return Vector(0, 0, 1);
    }
    
    double getT(Ray *r) {
        
        Vector normal = getNormal();

        double t = normal.dot(getVector(Point(0,0,0),r->start)) * (-1.0);
        t = t / normal.dot(r->direction);

        return t;
    }
    
    bool checkInside(Point p) {
        return (p.x >= -N*size) && (p.x <= N*size) && (p.y >= -N*size) && (p.y <= N*size);
    }
    
    Vector getReflection(Ray *ray,Vector normal) {
        double t = 2.0*normal.dot(ray->direction);
        Vector ans = ray->direction - normal * t;
        ans.normalize();
        return ans;
    }
    
    double intersect(Ray *r,Color *out_color,int level) {
        
        
        double t = getT(r);
        
        if(t<0) return  -1;
        
        
        
        Point ip = lineParametric(r->start, r->direction, t); // intersection point
        if( ! checkInside(ip) ) return -1;
        Vector n = getNormal();
        
        // get ii,jj
        
        if(level==0) return t;
        
            
        // calculate tile position
        int ii = (int) floor( (ip.x + N*size) / size );
        int jj = (int) floor( (ip.y + N*size) / size );
        
        
        // set ambient light
        if( board[ii][jj] ) *out_color = Color(1,1,1);
        else {
            // for black tiles : calculate texture pix
//            int TX, TY;
//
//            TX = (int)abs(ip.x)  % size;
//            TY = (int)abs(ip.y) %  size;
//
//            *out_color = textureMap[TX][TY];
            *out_color = Color(0,0,0);
        };

        *out_color = *out_color * this->a;
        
    
        
        for (int i=0; i<lights.size(); i++) {
            
            Vector direction = getVector(ip,lights[i]->light_pos);

            double ray_length = direction.dot(direction);
            ray_length=sqrt(ray_length);
            direction.normalize();
            Point start = ip + direction*1.0;

            Ray *ray_temp = new Ray(start,direction);
            
            
            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                double tempLength = objects[j]->getT(ray_temp);
                if(tempLength < 0 || tempLength > ray_length) {
                    continue;
                }
                obscured = true;
                break;
            }
            
            if(obscured==false){

                Ray indt(lights[i]->light_pos,direction*-1);
                Vector R = n * (2.0*indt.direction.dot(n)) - indt.direction ;
                R.normalize();
                double lambert = ray_temp->direction.dot(n);
                double phong = pow((r->direction*-1).dot(R),shine);
                *out_color = *out_color + (lights[i]->color)*(max(lambert,0.0)*d + max(phong,0.0)*s);
            }
            
        }
        

        

        if(level < recursionLevel) {
            Vector reflection = getReflection(r,n);
            Point start = lineParametric(ip, reflection, 1.0);
            Ray *reflectionRay = new Ray(start,reflection);

            int nearest = -1;
            double min_t = INT_MAX;
            Color *reColor = new Color();



            // find the nearest intersecting object
            for(int k=0;k<objects.size();k++) {

                double t = objects[k]->intersect(reflectionRay,reColor,0);

                if(t < min_t) {
                    nearest = k;
                    min_t = t;
                }

            }

            if(nearest != -1)
            {
                objects[nearest]->intersect(reflectionRay,reColor,level+1);
                *out_color = *out_color + (*reColor * this->r);

            }

            delete reColor;
            delete reflectionRay;

        }

        
        
        return t;
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
    
    Vector getNormal(Point ip){
        Vector ans = getVector(reference_point,ip);
        ans.normalize();
        return ans;
    }
    
    Vector getReflection(Ray *ray,Vector normal){
        double t=2.0*normal.dot(ray->direction);
        Vector ans =  ray->direction - normal* t;
        ans.normalize();
        return ans;
    }
    
    double getT(Ray *r) {
        
        // H(p) = P.P - r^2
       Vector R = getVector(reference_point,r->start);
       Vector ray_dir = r->direction;
        
       double a = 1 ;
       double b = 2*R.dot(ray_dir);
       double c = R.dot(R) - radius*radius;
       double det = b*b - (4*a*c) ;

       if(det<0) return -1 ;

       return min( (-b + sqrt(det))/2 ,(-b - sqrt(det))/2 );
    }
    
    double intersect(Ray *r,Color *out_color,int level) {
        
        
        double t = getT(r);

        if(t<=0) return -1;
    
        if(level==0) return t;

        Point intersectionPoint = lineParametric(r->start, r->direction, t);
        
        Vector normal = getNormal(intersectionPoint);
    
    
        *out_color = this->color * a ;
        
        Vector reflection = getReflection(r,normal);

        for(int i=0;i<lights.size();i++) {
            
            Vector direction = getVector(lights[i]->light_pos, intersectionPoint);
            direction.normalize();
            
            Point start = intersectionPoint + direction*1.0;
            Ray *rayTemp = new Ray(start,direction);

            double ray_length = direction.dot(direction);
            ray_length = sqrt(ray_length);
            
            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                
                double tempLength = objects[j]->getT(rayTemp);
                if(tempLength < 0 || tempLength > ray_length) {
                    continue;
                }
                obscured = true;
                break;
                
            }

            if(obscured==false){
                double lambert = normal.dot(rayTemp->direction);
                double phong =  pow(reflection.dot(r->direction),shine);

                *out_color = *out_color + (lights[i]->color)*(max(lambert,0.0)*d + max(phong,0.0)*s) ;
                
            }
            
        }
        
        if(level < recursionLevel) {

            Point start = lineParametric(intersectionPoint, reflection, 1.0);
            Ray *reflectionRay = new Ray(start,reflection);

            int nearest = -1;
            double min_t = INT_MAX;
            Color *reColor = new Color();

            // find the nearest intersecting object
            for(int k=0;k<objects.size();k++) {
                double t = objects[k]->intersect(reflectionRay,reColor,1);
              
                if(t < min_t) {
                    nearest = k;
                    min_t = t;
                }
                
            }
            
            if(nearest != -1)
            {
                objects[nearest]->intersect(reflectionRay,reColor,level+1);
                *out_color = *out_color + (*reColor * this->r ) ;
                
            }
            
            delete reColor;
            delete reflectionRay;
        }
        
        return  t;
    }
};

class Triangle:public Object{
public:
    Point A,B,C ;

    Triangle(Point x,Point y,Point z){
           this->A = x ;
           this->B = y ;
           this->C = z ;
    }
    
    void draw(){
        glColor3f(color.r,color.g,color.b);
        glBegin(GL_TRIANGLES);
        glVertex3d(A.x,A.y,A.z);
        glVertex3d(B.x,B.y,B.z);
        glVertex3d(C.x,C.y,C.z);
        glEnd();
    }
    
    

    Vector getNormal(Vector r) {

       
        Vector n =  getVector(A,B).cross(getVector(A,C));
            if(n.dot(r)>0) n = n * -1 ;
        n.normalize() ;
       
        return n ;
        
        
    }
    
    Vector getReflection(Ray *ray,Vector normal){
        double t = 2.0*normal.dot(ray->direction);
        Vector ans = ray->direction - normal * t;
        ans.normalize();
        return ans;
    }
    
    double getT(Ray *ray) {
        Vector edge1 = getVector(A, B);
        Vector edge2 = getVector(A, C);

        Vector h = ray->direction.cross(edge2);
        double a = edge1.dot(h);

        if(a > -EPSILON && a < EPSILON) {
            return -1;
        }

        double f = 1.0 / a;

        Vector s = getVector(A,ray->start);

        double u = f*s.dot(h) ;

        if(u < 0.0 || u > 1.0) {
            return -1;
        }
        Vector q = s.cross(edge1);

        double v = f * ray->direction.dot(q) ;

        if(v < 0.0 || u + v  > 1.0) {
            return -1;
        }

        double t = f * edge2.dot(q) ;

        if( t > EPSILON ) { //ray intersection
            return t;
        }

        return -1;
    }
    
    double intersect(Ray *r,Color *out_color,int level) {
        
        double t = getT(r);

        if(t<=0) return -1;
    
        if(level==0) return t;

        Point intersectionPoint = lineParametric(r->start, r->direction, t);
        
        Vector normal = getNormal(r->direction);
    
    
        *out_color = this->color * a ;
        
        Vector reflection = getReflection(r,normal);

        for(int i=0;i<lights.size();i++) {
            
            Vector direction = getVector(lights[i]->light_pos, intersectionPoint);
            direction.normalize();
            
            Point start = intersectionPoint + direction*1.0;
            Ray *rayTemp = new Ray(start,direction);

            double ray_length = direction.dot(direction);
            ray_length = sqrt(ray_length);
            
            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                
                double tempLength = objects[j]->getT(rayTemp);
                if(tempLength < 0 || tempLength > ray_length) {
                    continue;
                }
                obscured = true;
                break;
                
            }

            if(obscured==false){
                double lambert = normal.dot(rayTemp->direction);
                double phong =  pow(reflection.dot(r->direction),shine);

                *out_color = *out_color + (lights[i]->color)*(max(lambert,0.0)*d + max(phong,0.0)*s) ;
                
            }
            
        }
        
        if(level < recursionLevel) {

            Point start = lineParametric(intersectionPoint, reflection, 1.0);
            Ray *reflectionRay = new Ray(start,reflection);

            int nearest = -1;
            double min_t = INT_MAX;
            Color *reColor = new Color();

            // find the nearest intersecting object
            for(int k=0;k<objects.size();k++) {
                double t = objects[k]->intersect(reflectionRay,reColor,1);
              
                if(t < min_t) {
                    nearest = k;
                    min_t = t;
                }
                
            }
            
            if(nearest != -1)
            {
                objects[nearest]->intersect(reflectionRay,reColor,level+1);
                *out_color = *out_color + (*reColor * this->r ) ;
                
            }
            
            delete reColor;
            delete reflectionRay;
        }
        
    
        
        return  t;
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
        this->J = J;
    }
    
    Vector getNormal(Point in) {

        Vector ans;
        
        ans.ax=2.0 * A * in.x + D * in.y + E * in.z  + G;
        ans.ay=2.0 * B * in.y + D * in.x + F * in.z  + H;
        ans.az=2.0 * C * in.z + E * in.x + F * in.y  + I;
        
        ans.normalize();

        return ans;
    }
    
    double getT(Ray* ray) {

        double dx=ray->direction.ax, dy=ray->direction.ay, dz=ray->direction.az;
        double sx=ray->start.x, sy=ray->start.y, sz=ray->start.z;

        double a = A * dx * dx + B * dy * dy + C * dz * dz + D * dx * dy + E * dy * dz + F * dz * dx;
        
        double b = 2 * (A * sx * dx + B * sy * dy + C * sz * dz) + G * dx + H * dy + I * dz +E * (sy * dz + dy * sz) + D * (sx * dy + dx * sy) + F * (sz * dx + dz * sx);
        
        double c = A * sx * sx + B * sy * sy + C * sz * sz + G * sx + H * sy + I * sz + J + D * sx * sy + E * sy * sz + F * sz * sx;;


        double d = b*b - (4*a*c) ;

        if(d<0){
            return -1 ;
        }

        double temp=2.0*a;
        double t1 = (- b + sqrt(d)) / temp, t2 = (- b - sqrt(d)) / temp;

        // Calculate intersecting_point1  and intersecting_point
        Point ip1,ip2;
        ip1 = lineParametric(ray->start, ray->direction, t1);
        ip2 = lineParametric(ray->start, ray->direction, t2);

        double minX = reference_point.x, maxX = reference_point.x + length;
        double minY = reference_point.y, maxY = reference_point.y + width;
        double minZ = reference_point.z, maxZ = reference_point.z + height;

        bool flag1 = true, flag2 = true;

        if((length > 0 && ( ip1.x < minX || ip1.x > maxX)) ||
                    (width > 0 && ( ip1.y < minY || ip1.y > maxY)) ||
                    (height > 0 && ( ip1.z < minZ || ip1.z > maxZ))) flag1 = false;
        
        if ((length > 0 && ( ip2.x < minX || ip2.x > maxX)) ||
                (width > 0 && ( ip2.y < minY || ip2.y > maxY)) ||
                (height > 0 && ( ip2.z < minZ || ip2.z > maxZ))) flag2 = false;
        
        
       // If both point within volume return smallest t
        
       // If only one then return that
        
       // If none return -1
 
        
        if(flag1 && flag2)
            return min(t1,t2);
        
        else if(flag1)
            return t1;
        
        else if(flag2)
            return t2;
        
        else return -1;

        
    }
    
    void draw(){
        // nothing to do!
    }
    
    Vector getReflection(Ray *ray,Vector normal){
        double t=2.0*normal.dot(ray->direction);
        Vector ans = ray->direction - normal*t;
        ans.normalize();
        return ans;
    }
    
    double intersect(Ray *r,Color *out_color,int level) {

            double t = getT(r);

            if(t<=0) return -1;
        
            if(level==0) return t;

            Point intersectionPoint = lineParametric(r->start, r->direction, t);
            
            Vector normal = getNormal(intersectionPoint);
        
        
            *out_color = this->color * a ;
            
            Vector reflection = getReflection(r,normal);

            for(int i=0;i<lights.size();i++) {
                
                Vector direction = getVector(lights[i]->light_pos, intersectionPoint);
                direction.normalize();
                
                Point start = intersectionPoint + direction*1.0;
                Ray *rayTemp = new Ray(start,direction);

                double ray_length = direction.dot(direction);
                ray_length = sqrt(ray_length);
                
                bool obscured = false;

                for(int j=0;j<objects.size();j++){
                    
                    double tempLength = objects[j]->getT(rayTemp);
                    if(tempLength < 0 || tempLength > ray_length) {
                        continue;
                    }
                    obscured = true;
                    break;
                    
                }

                if(obscured==false){
                    double lambert = normal.dot(rayTemp->direction);
                    double phong =  pow(reflection.dot(r->direction),shine);

                    *out_color = *out_color + (lights[i]->color)*(max(lambert,0.0)*d + max(phong,0.0)*s) ;
                    
                }
                
            }
        
        if(level < recursionLevel) {

            Point start = lineParametric(intersectionPoint, reflection, 1.0);
            Ray *reflectionRay = new Ray(start,reflection);

            int nearest = -1;
            double min_t = INT_MAX;
            Color *reColor = new Color();

            // find the nearest intersecting object
            for(int k=0;k<objects.size();k++) {
                double t = objects[k]->intersect(reflectionRay,reColor,1);
              
                if(t < min_t) {
                    nearest = k;
                    min_t = t;
                }
                
            }
            
            if(nearest != -1)
            {
                objects[nearest]->intersect(reflectionRay,reColor,level+1);
                *out_color = *out_color + (*reColor * this->r ) ;
                
            }
            delete reColor;
            delete reflectionRay;
        }
        
        return t;
    }
    
};


// done







