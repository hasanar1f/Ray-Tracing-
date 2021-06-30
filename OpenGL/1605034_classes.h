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
#ifdef __APPLE__

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#else

#include <glut.h>
#include <windows.h>

#endif

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

   Color operator+(double a){
       Color temp;
       temp.r = min(this->r*a,1);
       temp.g = min(this->g*a,1);
       temp.b = min(this->b*a,1);
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
    
    Square() {
        
    }

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
    
    double textureHeight,textureWidth;
    double tx,ty;
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
        
        a = 0.33;
        d = 0.2;
        s = 0.3;
        r = 0.2;
        shine = 5;
        
        /// texture data load
        texture = bitmap_image("texture.png");
        textureWidth = texture.width();
        textureHeight = texture.height();
        
        // map
        tx = textureWidth / (2*N*size);
        ty = textureHeight / (2*N*size);
        
    }
    
    ~CheckerBoard() {
        delete [] board;
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
    
    double getParametricValue(Ray *r) {
        
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
        
        double t = getParametricValue(r);
        
        if(t<0) return  -1;
        
        else if(level==0) return t;
        
        
        
        Vector reflection = getReflection(r,normal);
        Point ip = lineParametric(r->start, r->direction, t); // intersection point
        Vector n = getNormal();
        
        // get ii,jj
        if( ! checkInside(ip) ) return -1;

        
            
        // calculate tile position
        int ii = (int) floor( (ip.x + N*size) / size );
        int jj = (int) floor( (ip.y + N*size) / size );
        
        
        // set ambient light
        if( board[ii][jj] ) *out_color = Color(1,1,1);
        else *out_color = Color(0,0,0);

        *out_color = *out_color * this->a;
        
        
        // calculate texture pix
        int TX, TY;
        
        TX = (ip.x + N*size) * tx;
        TY = (ip.y + N*size) * ty;
        
        
        unsigned char red, green, blue;
        texture.get_pixel(TX, TY, red, green, blue);
        Color Txr((double)red,(double)green,(double)blue);
        
      //  *out_color = *out_color + Txr;
        
        
        for (int i=0; i<lights.size(); i++) {
            
            Vector direction = getVector(ip,lights[i]->light_pos);

            double ray_length = direction.dot(direction);
            ray_length=sqrt(ray_length);
            direction.normalize();
            Point start = ip + direction*1.0;

            Ray *ray_temp = new Ray(start,direction);
            
            
            bool obscured = false;

            for(int j=0;j<objects.size();j++){
                double Ltemp = objects[j]->getParametricValue(ray_temp);
                if(Ltemp < 0 || Ltemp > ray_length) {
                    continue;
                }
                obscured = true;
                break;
            }
            
            if(obscured==false){

                Ray indt(lights[i]->light_pos,direction*-1);
                Vector light_ref = n * (2.0*indt.direction.dot(n)) - indt.direction ;
                light_ref.normalize();
                double lambert = ray_temp->direction.dot(n);
                double phong = pow((r->direction*-1).dot(light_ref),shine);
                lambert = max(lambert,0.0);
                phong = max(phong,0.0);
                *out_color = *out_color + (lights[i]->color)*(lambert*d + phong*s);
            }
            
        }
        

        if(level < recursionLevel) {
            
            Point start = lineParametric(ip, reflection, 1.0);
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
                *out_color = *out_color + (*reColor * this->r);
                
            }
        
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
    
    Vector getReflection(Ray *ray,Vector normal){
        double t=2.0*normal.dot(ray->direction);
        Vector ans =  ray->direction - normal* t;
        ans.normalize();
        return ans;
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
        
        Vector reflection = getReflection(r,n);
        
        *out_color = this->color * a;
        
        for(int i=0;i<lights.size();i++) {
            
            Vector l_dir = getVector(ip,lights[i]->light_pos);
            double ray_length = l_dir.dot(l_dir);
            ray_length = sqrt(ray_length);
            l_dir.normalize();
            Point s_p = lineParametric(ip,l_dir,1);
            Vector s_l = getVector(s_p,lights[i]->light_pos);
            s_l.normalize() ;
            Ray *l_r = new Ray(s_p,s_l) ;
            
            

            // chayaaa
            bool obscured = false;

            for(int j=0;j<objects.size();j++) {

                double Ltemp = objects[j]->getParametricValue(l_r);
                if(Ltemp < 0 || Ltemp > ray_length) {
                    continue;
                }
                obscured = true;
                break;
            }
              
            if(obscured==false) {
                
               Ray indt(lights[i]->light_pos,l_dir*-1);
               Vector light_ref = n*(2.0*indt.direction.dot(n)) - indt.direction ;
               light_ref.normalize();
               double lambert = l_r->direction.dot(n);
               double phong = pow((r->direction*-1).dot(light_ref),shine) ;
               lambert = max(lambert,0.0);
               phong = max(phong,0.0);

               *out_color = *out_color + (lights[i]->color)*(lambert*d + phong*s);
            }
            
            
        }
        
        if(level < recursionLevel) {

            Point start = lineParametric(ip, reflection, 1.0);
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
    
    
    Vector getNormal(){
        Vector n =  getVector(A,B).cross(getVector(A,C));
        n.normalize() ;
        return n ;
    }
    
    Vector getCross(Point a,Point b,Point c){
        Vector v1 = getVector(a,b) ;
        Vector v2 = getVector(a,c) ;

        Vector r = v1.cross(v2) ;

        return r ;
    }
    
    Vector getNormal(Vector r) {

        Vector n =  getVector(A,B).cross(getVector(A,C));
        if(n.dot(r)>0) n = n*-1 ;
        n.normalize() ;
        return n ;
        
    }
    
    Vector getReflection(Ray *ray,Vector normal){
        double t = 2.0*normal.dot(ray->direction);
        Vector ans = ray->direction - normal * t;
        ans.normalize();
        return ans;
    }
    
    double getParametricValue(Ray *ray) {
        Vector n = getNormal();
        double d = - ( n.ax * A.x + n.ay * A.y + n.az * A.z ) ;
        double t = - ((d+n.dot(getVector(Point(0,0,0),ray->start)))/n.dot(ray->direction));
        Point P = lineParametric(ray->start,ray->direction,t);

        Vector i,j,k ;

        i = getCross(A,B,P) ;
        j = getCross(B,C,P) ;
        k = getCross(C,A,P) ;

        if(i.dot(j)>=1 && i.dot(k)>=1) return t ;

        return -1 ;
    }
    
    double intersect(Ray *r,Color *out_color,int level) {
        
        double t = getParametricValue(r);
        
        
        if(t<=0) return -1;

        if(level==0) return t;
        
        *out_color = (this->color) * a ;
        
        Point ip = lineParametric(r->start,r->direction,t) ;
        Vector n = getNormal(r->direction) ;
        
        Vector reflection = getReflection(r,n);
        
        for(int i=0;i<lights.size();i++){

            Vector l_dir = getVector(ip,lights[i]->light_pos);
            l_dir.normalize();
            Point s_p = lineParametric(ip,l_dir,1);
            Vector s_l = getVector(s_p,lights[i]->light_pos);
            s_l.normalize() ;
            Ray *l_r = new Ray(s_p,s_l);
            
            // shadow
            bool obscured = false;
            
            double ray_length = l_dir.dot(l_dir);
            ray_length = sqrt(ray_length);
            
            for(int j=0;j<objects.size();j++){
                double Ltemp = objects[j]->getParametricValue(l_r);
                if(Ltemp < 0 || Ltemp > ray_length) {
                    continue;
                }
                obscured = true;
                break;
            }
            
            if(obscured==false){
                Ray indt(lights[i]->light_pos,l_dir*-1);
                Vector light_ref = n * (2.0*indt.direction.dot(n)) - indt.direction ;
                light_ref.normalize();
                double lambert = l_r->direction.dot(n);
                double phong = pow((r->direction*-1).dot(light_ref),10) ;
                lambert = max(lambert,0.0);
                phong = max(phong,0.0);
                *out_color = *out_color + (lights[i]->color)*(lambert*d + phong*s) ;
            }
         

        }
        
        if(level < recursionLevel) {

            Point start = lineParametric(ip, reflection, 1.0);
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
    
    double getParametricValue(Ray* ray) {

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

        Point intersectionPoint[2];
        intersectionPoint[0] = lineParametric(ray->start, ray->direction, t1);
        intersectionPoint[1] = lineParametric(ray->start, ray->direction, t2);

        double min_x = reference_point.x, max_x = reference_point.x + lenght;

        double min_y = reference_point.y, max_y = reference_point.y + width;

        double min_z = reference_point.z, max_z = reference_point.z + height;

        bool check[2];

        for(int i=0;i<2;i++)
        {
            check[i] = (lenght > 0 && ( intersectionPoint[i].x < min_x || intersectionPoint[i].x > max_x) ||
                      width > 0 && ( intersectionPoint[i].y < min_y || intersectionPoint[i].y > max_y) ||
                      height > 0 && ( intersectionPoint[i].z < min_z || intersectionPoint[i].z > max_z));
        }
        bool check1 = check[0] && check[1];
        if (check1) {
            return -1;
        } else if (check[1]) {
            return t1;
        } else if (check[0]) {
            return t2;
        } else {
            if(t1<t2)
                return t1;
            else
                return t2;
                }
        
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

            double t = getParametricValue(r);

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
                    
                    double Ltemp = objects[j]->getParametricValue(rayTemp);
                    if(Ltemp < 0 || Ltemp > ray_length) {
                        continue;
                    }
                    obscured = true;
                    break;
                    
                }

                if(obscured==false){
                    double lambert = normal.dot(rayTemp->direction);
                    double phong =  pow(reflection.dot(r->direction),shine);

                    lambert = max(lambert,0.0);
                    phong = max(phong,0.0);
                    *out_color = *out_color + (lights[i]->color)*(lambert*d + phong*s) ;
                    
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
        }
        
        return t;
    }
    
};








