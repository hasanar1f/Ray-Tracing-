//
//  1605034_main.cpp
//  OpenGL
//
//  Created by Hasan Ibn Arif Efaz on 24/6/21.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "1605034_classes.h"
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
int red_dot_count;
double angle,canon_rotation_X,canon_rotation_Y_1,canon_rotation_Y_2,canon_rotation_Z;



class Vector Look, Right, Up;
class Point cam_pos;


void drawAxes()
{

    glColor3f(100.0, 100.0, 100.0);
    glBegin(GL_LINES);{
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
    }glEnd();
    
}


void drawGrid()
{
    int i;
    if(drawgrid==1)
    {
        glColor3f(0.6, 0.6, 0.6);    //grey
        glBegin(GL_LINES);{
            for(i=-8;i<=8;i++){

                if(i==0)
                    continue;    //SKIP the MAIN axes

                //lines parallel to Y-axis
                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);

                //lines parallel to X-axis
                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }glEnd();
    }
}




void drawCircle(double radius,int segments)
{
    // a comment added
    int i;
    struct Point Points[100];
    glColor3f(0.7,0.7,0.7);
    //generate Points
    for(i=0;i<=segments;i++)
    {
        Points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        Points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated Points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(Points[i].x,Points[i].y,0);
            glVertex3f(Points[i+1].x,Points[i+1].y,0);
        }
        glEnd();
    }
}




void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct Point Points[100];
    //generate Points
    for(i=0;i<=segments;i++)
    {
        Points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        Points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated Points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
            glVertex3f(Points[i].x,Points[i].y,0);
            glVertex3f(Points[i+1].x,Points[i+1].y,0);
        }
        glEnd();
    }
}




void draw_Cylinder(double radius,Point center,double length) {
    struct Point Points[100];
    int slices = 35;



    for(int i=0;i<=slices;i++) {

        Points[i].y=radius*cos(((double)i/(double)slices)*2*pi)+center.y;
        Points[i].z=radius*sin(((double)i/(double)slices)*2*pi)+center.z;
        Points[i].x=center.x;

    }


    for(int i=0;i<slices;i++) {


        if(i%2==0)
            glColor3f(1,1,1);
        else
            glColor3f(0,0,0);

        glBegin(GL_QUADS);
        {
            glVertex3f(Points[i].x,Points[i].y,Points[i].z);
            glVertex3f(Points[i+1].x,Points[i+1].y,Points[i+1].z);

            glVertex3f(Points[i].x+length,Points[i].y,Points[i].z);
            glVertex3f(Points[i+1].x+length,Points[i+1].y,Points[i+1].z);
        }
        glEnd();


    }


}

void draw_half_sphere(double radius,Point center,bool isLeft) {
    struct Point Points[100][100];
    int i,j;
    double h,r;
    int stacks = 35;
    int slices = 35;
    //generate Points
    for(i=0;i<=stacks;i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=radius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0;j<=slices;j++)
        {
            Points[i][j].y=r*cos(((double)j/(double)slices)*2*pi)+center.y;
            Points[i][j].z=r*sin(((double)j/(double)slices)*2*pi)+center.z;
            Points[i][j].x=h+center.x;
        }
    }

    for(i=0;i<stacks;i++)
    {

        for(j=0;j<slices;j++)
        {
            if(j%2==0)
                glColor3f(1,1,1);
            else
                glColor3f(0,0,0);

            glBegin(GL_QUADS);{
                //left hemisphere
                if(!isLeft) {
                    glVertex3f(Points[i][j].x,Points[i][j].y,Points[i][j].z);
                    glVertex3f(Points[i][j+1].x,Points[i][j+1].y,Points[i][j+1].z);
                    glVertex3f(Points[i+1][j+1].x,Points[i+1][j+1].y,Points[i+1][j+1].z);
                    glVertex3f(Points[i+1][j].x,Points[i+1][j].y,Points[i+1][j].z);
                }
                //Right hemisphere
                else {
                    glVertex3f(-Points[i][j].x,Points[i][j].y,Points[i][j].z);
                    glVertex3f(-Points[i][j+1].x,Points[i][j+1].y,Points[i][j+1].z);
                    glVertex3f(-Points[i+1][j+1].x,Points[i+1][j+1].y,Points[i+1][j+1].z);
                    glVertex3f(-Points[i+1][j].x,Points[i+1][j].y,Points[i+1][j].z);
                }
            }glEnd();
        }
    }

}




// L = one    R = two   U = axis



void Rotate(Vector &one,Vector &two, Vector &axis, double angle)
{

    double ldot=axis.dot(one);
    struct Vector lcross=axis.cross(one);

    double rdot=axis.dot(two);
    struct Vector rcross=axis.cross(two);

    one.ax=one.ax*cos(angle)+lcross.ax*sin(angle)+(axis.ax)*ldot*(1-cos(angle));
    one.ay=one.ay*cos(angle)+lcross.ay*sin(angle)+(axis.ay)*ldot*(1-cos(angle));
    one.az=one.az*cos(angle)+lcross.az*sin(angle)+(axis.az)*ldot*(1-cos(angle));

    two.ax=two.ax*cos(angle)+rcross.ax*sin(angle)+(axis.ax)*rdot*(1-cos(angle));
    two.ay=two.ay*cos(angle)+rcross.ay*sin(angle)+(axis.ay)*rdot*(1-cos(angle));
    two.az=two.az*cos(angle)+rcross.az*sin(angle)+(axis.az)*rdot*(1-cos(angle));


}

void keyboardListener(unsigned char key, int x,int y){
    switch(key){

        case '1':
            Rotate(Look,Right,Up,angle*5);
            break;

        case '2':
            Rotate(Look,Right,Up,-angle*5);
            break;
        case '3':
            Rotate(Look,Up,Right,angle*5);
            break;
        case '4':

            Rotate(Look,Up,Right,-angle*5);
            break;
        case '5':
            Rotate(Up,Right,Look,angle*5);
            break;
        case '6':
            Rotate(Up,Right,Look,-angle*5);
            break;
        case 'p':
          
            break;

     
        default:
            break;
    }
}


void specialKeyListener(int key, int x,int y){
    switch(key){
        case GLUT_KEY_DOWN:        //down arrow key
            cam_pos = cam_pos - Look*5;
            break;
        case GLUT_KEY_UP:        // Up arrow key
            cam_pos = cam_pos + Look*5;
            break;

        case GLUT_KEY_RIGHT:
            cam_pos = cam_pos + Right*5;
            break;
        case GLUT_KEY_LEFT:
            cam_pos = cam_pos - Right*5;
            break;

        case GLUT_KEY_PAGE_UP:
            cam_pos = cam_pos + Up*5;
            break;
        case GLUT_KEY_PAGE_DOWN:
            cam_pos = cam_pos - Up*5;
            break;

        case GLUT_KEY_INSERT:
            break;

        case GLUT_KEY_HOME:
            break;
        case GLUT_KEY_END:
            break;

        default:
            break;
    }
}


void mouseListener(int button, int state, int x, int y){    //x, y is the x-y of the screen (2D)
    switch(button){
        case GLUT_LEFT_BUTTON:

            break;

        case GLUT_RIGHT_BUTTON:
            //........
            if(state == GLUT_DOWN){        // 2 times?? in ONE click? -- solution is checking DOWN or Up
                drawaxes=1-drawaxes;
            }
            break;

        case GLUT_MIDDLE_BUTTON:
            //........
            break;

        default:
            break;
    }
}



void draw_front(Point center) {

    double radius = 25;

    struct Point Points[100][100];
    int i,j;
    double h,r;
    int stacks = 35;
    int slices = 35;
    //generate Points
    for(i=0;i<=stacks;i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=radius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0;j<=slices;j++)
        {
            Points[i][j].y=r*cos(((double)j/(double)slices)*2*pi)+center.y;
            Points[i][j].z=r*sin(((double)j/(double)slices)*2*pi)+center.z;
            Points[i][j].x=h+center.x;
        }
    }

    for(i=0;i<stacks;i++)
    {

        for(j=0;j<slices;j++)
        {
            if(j%2==0)
                glColor3f(1,1,1);
            else
                glColor3f(0,0,0);

            glBegin(GL_QUADS);{

                glVertex3f(Points[i][j].x,Points[i][j].y,Points[i][j].z);
                glVertex3f(Points[i][j+1].x,Points[i][j+1].y,Points[i][j+1].z);
                glVertex3f(Points[i+1][j+1].x,Points[i+1][j+1].y,Points[i+1][j+1].z);
                glVertex3f(Points[i+1][j].x,Points[i+1][j].y,Points[i+1][j].z);


            }glEnd();
        }
    }
}






void draw_plane(double side, double dist) {

    glColor3f(.5,.5,.5);
    glBegin(GL_QUADS);{

        glVertex3f(dist,side,side);
        glVertex3f(dist,-side,side);
        glVertex3f(dist,-side,-side);
        glVertex3f(dist,side,-side);

    }glEnd();


}





void display(){

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);    //color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-Up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera Looking?
    //3. Which angle is the camera's Up angle?

    gluLookAt(cam_pos.x,cam_pos.y,cam_pos.z,
                cam_pos.x+Look.ax,cam_pos.y+Look.ay,cam_pos.z+Look.az,
                Up.ax,Up.ay,Up.az
             );


    /****************************
    / Add your objects from here
    ****************************/
    //add objects
    
    CheckerBoard checkerBoard(20,20);
    checkerBoard.draw();


 


    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate(){
    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init(){
    //codes for initialization
    drawgrid=1;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=(pi)/360.0;

    canon_rotation_X = 0.0;
    canon_rotation_Y_1 = 0.0;
    canon_rotation_Y_2 = 0.0;
    canon_rotation_Z = 0.0;

    red_dot_count = 0;



    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-Up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80,    1,    1,    1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X angle (horizontally)
    //near distance
    //far distance

    cam_pos = Point(500,500,300);
    Look = Vector(-1/sqrt(2),-1/sqrt(2),0);
    Up = Vector(0,0,1);
    Right = Vector(-1/sqrt(2),1/sqrt(2),0);
    
    //gluLookAt(cam_pos.x,cam_pos.y,cam_pos.z,   0,0,0,    0,1,0);

}

void loadData() {
    
    int items,recursionLevel,height,width;
    string object_type;
    freopen("scene.txt","r",stdin);
    cin>>recursionLevel >> width >> items ;
    height = width;
    
    while (items--) {
        double a,d,s,r,shine;
        cin>>object_type;
        
        if(object_type=="sphere") {
            Object newObj = new Sphere(
        }
        
        else if(object_type=="triangle") {
            
            
            
        }
        
        else if(object_type=="general") {
            
            
            
        }
        
        else continue;
    }
    
}

int main(int argc, char **argv){
        
    loadData();
    
    
    //////////////////////////////////////////////////////// Scene Builder //////////////////////////////////////// / /
    
    
    glutInit(&argc,argv);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);    //Depth, Double buffer, RGB color
    glutCreateWindow("Ray Tracing Offline - 1605034");

    init();

    glEnable(GL_DEPTH_TEST);    //enable Depth Testing
    glutDisplayFunc(display);    //display callback function
    glutIdleFunc(animate);        //what you want to do in the idle time (when no drawing is occuring)
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);
    glutMainLoop();        //The main loop of OpenGL

    return 0;
}
