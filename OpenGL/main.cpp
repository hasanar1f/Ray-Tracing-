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
#include <GLUT/glut.h>

#define pi (2*acos(0.0))


double cameraAngle;
double cameraHeight;
int drawgrid;
int drawaxes;
int red_dot_count;
double angle,canon_rotation_X,canon_rotation_Y_1,canon_rotation_Y_2,canon_rotation_Z;
int items,height,width;


double windowHeight=500;
double windowWidth=500;
double view_angle=110;

class Vector Look, Right, Up;
class Point cam_pos;


void Capture(); // will define later

void drawAxes()
{
    
    glColor3f(100.0, 100.0, 100.0);
    glBegin(GL_LINES);{
        glVertex3f( 100,0,0);
        glVertex3f(-100,0,0);

        glVertex3f(0,-100,0);
        glVertex3f(0, 100,0);

        glVertex3f(0,0, 100);
        glVertex3f(0,0,-100);
    }glEnd();
    
}










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
        case '0':
            Capture();
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





void Capture() {
    
    int image_height = (int) height ;
    int image_width = (int) width ;
    bitmap_image image(image_height,image_width);
    
    double planeDistance = (windowHeight/2.0)*tan( (view_angle*pi)/360.0);

    Vector new_l = Look*planeDistance ;
    Vector new_r = Right*(-1.0*(windowHeight/2.0)) ;
    Vector new_u = Up*(windowWidth/2.0) ;
    
    Vector resultant = new_l+new_r+new_u ;
    Point topLeft = lineParametric(cam_pos,resultant,1);

    double du = windowHeight/image_height ;
    double dv = windowWidth/image_width ;
    
    
    
    for(int i=0;i<image_height;i++){
            for(int j=0;j<image_width;j++){
                Point point;
                Vector n_u = Up*(-1.0*i*du);
                Vector n_r = Right*(j*dv);
                Vector n_resultant = n_u + n_r ;
                point = lineParametric(topLeft,n_resultant,1);
                Vector v = getVector(cam_pos,point);
                v.normalize();
                Ray *ray = new Ray(cam_pos,v);
                
                int nearest = -1;
                Color *color = new Color();
                double min_t = INT_MAX;

                // for each object

                for(int k=0;k<objects.size();k++) {
                    double t = objects[k]->intersect(ray,color,0);
                    if(t>0){
                        if(t<min_t){
                            nearest = k;
                            min_t = t;
                        }
                    }
                }
                
                if(nearest != -1){
                    objects[nearest]->intersect(ray,color,1);
                    image.set_pixel(j,i,color->r*255,color->g*255,color->b*255);
                }
            }
        }
    
    
    
    image.save_image("output.bmp");
    printf("Image generated\n");
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
    
    
    for(int i=0;i<lights.size();i++){
        glColor3f(lights[i]->color.r,lights[i]->color.g,lights[i]->color.b);
        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex3d(lights[i]->light_pos.x,lights[i]->light_pos.y,lights[i]->light_pos.z);
        glEnd();
    }
    
    for(int i=0;i<objects.size();i++) {
        objects[i]->draw();
    }
    
    //drawAxes();
    



 


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

    cam_pos = Point(120,110,50);
    
    Look = Vector(-1/sqrt(2),-1/sqrt(2),0);
    Up = Vector(0,0,1);
    Right = Vector(-1/sqrt(2),1/sqrt(2),0);
    
    cam_pos = cam_pos - Look*5;
}

void loadData() {
    
    CheckerBoard *checkerBoard = new CheckerBoard(10,40);
    objects.push_back(checkerBoard);
    
    
    string object_type;
    freopen("scene.txt","r",stdin);
    cin>>recursionLevel >> width >> items ;
    height = width;
    
    while (items--) {
        double a,d,s,r,shine;
        cin>>object_type;
        
        if(object_type=="sphere") {
            Point center;
            cin>>center.x>>center.y>>center.z;
            double rad;
            cin>>rad;
            Sphere *newObj = new Sphere(center,rad);
            Color col;
            cin>>col.r>>col.g>>col.b;
            newObj->setColor(col);
            cin>>a>>d>>s>>r>>shine;
            newObj->setCoEfficients(a, d, s, r);
            newObj->setShine(shine);
            
            objects.push_back(newObj);
       
            
            
        }
        
        else if(object_type=="triangle") {
            
            Point A,B,C;
            cin>>A.x>>A.y>>A.z;
            cin>>B.x>>B.y>>B.z;
            cin>>C.x>>C.y>>C.z;
            
            Triangle *newObj = new Triangle(A,B,C);
            
            Color col;
            cin>>col.r>>col.g>>col.b;
            newObj->setColor(col);
            cin>>a>>d>>s>>r>>shine;
            newObj->setCoEfficients(a, d, s, r);
            newObj->setShine(shine);
            
            objects.push_back(newObj);
            
            
        }
        
        else if(object_type=="general") {
            double A,B,C,D,E,F,G,H,I,J;
            cin>>A>>B>>C>>D>>E>>F>>G>>H>>I>>J;
            
            General *newObj = new General(A,B,C,D,E,F,G,H,I,J);
            
            Point p;
            cin>>p.x>>p.y>>p.z;
            newObj->setRefPoint(p);
            Point temp;
            cin>>temp.x>>temp.y>>temp.z;
            newObj->setDimension(temp.x, temp.y, temp.z);
            Color c;
            cin>>c.r>>c.g>>c.b;
            newObj->setColor(c);
            
            cin>>a>>d>>s>>r>>shine;
            newObj->setCoEfficients(a, d, s, r);
            newObj->setShine(shine);
            
            objects.push_back(newObj);
            
        }
        
        else continue;
    }
    
    cin>>items ;
    
    for(int i=0;i<items;i++){
        Point p;
        cin>>p.x>>p.y>>p.z;
        Color c;
        cin>>c.r>>c.g>>c.b;
        
        Light *newLight = new Light(p,c);
        lights.push_back(newLight);
    }
    
    
}

int main(int argc, char **argv){
    
    cout << endl << "------------------------------- Console ------------------------------------" << endl;
        
    loadData();
    
    
    //////////////////////////////////////////////////////// Scene Builder ////////////////////////////////////////////// / /
    
    
    glutInit(&argc,argv);
    glutInitWindowSize(windowWidth, windowHeight);
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
    
    cout << endl << "-------------------------------- End -------------------------------------" << endl;


    return 0;
}
