
#include <string.h>
#include <GL/glui.h>

float xy_aspect;
int   last_x, last_y;
float rotationX = 0.0, rotationY = 0.0;

/** These are the live variables passed into GLUI ***/
int   wireframe = 0;
int   obj_type = 1;
int   segments = 8;
int   segments2 = 8;
int   light0_enabled = 1;
int   light1_enabled = 1;
float light0_intensity = 1.0;
float light1_intensity = .4;
int   main_window;
float scale = 0.5;
int   show_sphere=1;
float sphere_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float obj_pos[] = { 0.0, 0.0, 0.0 };
GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 5;

/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui, *glui2;
GLUI_Spinner    *light0_spinner, *light1_spinner;
GLUI_RadioGroup *radio;
GLUI_Panel      *obj_panel;

/********** User IDs for callbacks ********/
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260
#define ENABLE_ID            300
#define DISABLE_ID           301
#define SHOW_ID              302
#define HIDE_ID              303


/********** Miscellaneous global variables **********/

GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
GLfloat light0_position[] = {.5f, .5f, 1.0f, 0.0f};

GLfloat light1_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light1_diffuse[] =  {.9f, .6f, 0.0f, 1.0f};
GLfloat light1_position[] = {-1.0f, -1.0f, 1.0f, 0.0f};

GLfloat lights_rotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

/**************************************** control_cb() *******************/
///////////////////////******************************************////////////////////
GLfloat RED_RGB[] = {1.0, 0.0, 0.0};            // drawing colors
GLfloat BLUE_RGB[] = {0.0, 1.0, 1.0};
GLfloat GREEN_RGB[] = {0.0, 1.0, 0.0};
GLfloat BLACK_RGB[] = {0.0, 0.0, 0.0};
GLfloat WHITE_RGB[] = {1.0, 1.0, 1.0};
GLfloat YELLOW_RGB[] = {1.0, 1.0, 0.0};
GLfloat PURPLE_RGB[] = {0.73, 0.16, 0.96};
GLfloat ORANGE_RGB[] = {1.0, 0.5, 0.0};
GLfloat GOLD_RGB[] = {0.75, 0.5, 0.0};
GLfloat GOLD_BACK[] = {0.8, 0.49803, 0.196078, 0.0};


void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glDepthMask(GL_TRUE);
   glEnable(GL_NORMALIZE); // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


void Front(){


///------------upper rectangle-----

glColor3ub(17,55,66);
        glBegin(GL_POLYGON);
        glVertex3f(-0.7,0.3,-0.2);
        glVertex3f(0.7,0.3,-0.2);
        glVertex3f(0.7,0.2,-0.2);
        glVertex3f(-0.7,0.2,-0.2);
    glEnd();
    glColor3f(1,0,1);

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(-0.7,0.2,-0.21);
    glVertex3f(0.7,0.2,-0.21);
    glEnd();
    glFlush();

///------------lower rectangle-----

glColor3ub(17,55,66);
        glBegin(GL_POLYGON);
        glVertex3f(-0.7,-0.2,-0.2);
        glVertex3f(0.7,-0.2,-0.2);
        glVertex3f(0.7,-0.3,-0.2);
        glVertex3f(-0.7,-0.3,-0.2);
    glEnd();
    glColor3f(1,0,1);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(-0.7,-0.2,-0.22);
    glVertex3f(0.7,-0.2,-0.22);
    glEnd();

    glFlush();

///------------background----------

glColor3ub(192,163,107);
        glBegin(GL_POLYGON);
        glVertex3f(-0.7,0.2,-0.2);
        glVertex3f(0.7,0.2,-0.2);
        glVertex3f(0.7,-0.2,-0.2);
        glVertex3f(-0.7,-0.2,-0.2);
    glEnd();
    glFlush();

/// the first 6 lines

glColor3f(1,0,0);
        glBegin(GL_POLYGON);
        glVertex3f(-0.7,-0.1,-0.26);
        glVertex3f(-0.6,0,-0.26);
        glVertex3f(-0.6,0,-0.26);
        glVertex3f(-0.7,0.1,-0.26);
    glEnd();
    glFlush();
///---------------
 glColor3f(0,0,0);
        glBegin(GL_POLYGON);
        glVertex3f(-0.7,-0.2,-0.25);
        glVertex3f(-0.5,0,-0.25);
        glVertex3f(-0.7,0.2,-0.25);
    glEnd();
    glFlush();

///--------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(1,0,1);
        glVertex3f(-0.7,0.2,-0.24);
        glVertex3f(-0.6,0.2,-0.24);
        glVertex3f(-0.4,0,-0.24);
        glVertex3f(-0.6,-0.2,-0.24);
        glVertex3f(-0.7,-0.2,-0.24);
    glEnd();
    glFlush();

///---------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(0,0,1);
        glVertex3f(-0.7,0.2,-0.23);
        glVertex3f(-0.5,0.2,-0.23);
        glVertex3f(-0.3,0,-0.23);
        glVertex3f(-0.5,-0.2,-0.23);
        glVertex3f(-0.7,-0.2,-0.23);
    glEnd();
    glFlush();


///---------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(0,1,1);
        glVertex3f(-0.7,0.2,-0.22);
        glVertex3f(-0.4,0.2,-0.22);
        glVertex3f(-0.2,0,-0.22);
        glVertex3f(-0.4,-0.2,-0.22);
        glVertex3f(-0.7,-0.2,-0.22);
    glEnd();
    glFlush();

///---------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(1,0,1);
        glVertex3f(-0.7,0.2,-0.21);
        glVertex3f(-0.3,0.2,-0.21);
        glVertex3f(-0.1,0,-0.21);
        glVertex3f(-0.3,-0.2,-0.21);
        glVertex3f(-0.7,-0.2,-0.21);
    glEnd();
    glFlush();

///---------------------------------------------------
/// upper triangle


glColor3ub(255,255,0);
for (float i=0.0;i<1;i+=0.4){
    glBegin(GL_POLYGON);
        glVertex3f(-0.29+i,0.2,-0.21);
        glVertex3f(-0.19+i,0.1,-0.21);
        glVertex3f(-0.1+i,0.2,-0.21);
    glEnd();
}
/// upper inside triangles
glColor3ub(135,74,46);
for (float i=0.0;i<1;i+=0.4){
    glBegin(GL_POLYGON);
        glVertex3f(-0.266+i,0.2,-0.22);
        glVertex3f(-0.19+i,0.125,-0.22);
        glVertex3f(-0.124+i,0.2,-0.22);
    glEnd();
}

/// upper inside triangles 2
for (float i=0.0;i<1;i+=0.4){
glColor3ub(0,255,255);
    glBegin(GL_POLYGON);
        glVertex3f(-0.236+i,0.2,-0.23);
        glVertex3f(-0.19+i,0.15,-0.23);
        glVertex3f(-0.148+i,0.2,-0.23);
    glEnd();
}
///-------------------------------------------------------------------

///lower triangles

for (float i=0.0;i<1;i+=0.4){
    glBegin(GL_POLYGON);
         glVertex3f(-0.29+i,-0.2,-0.21);
        glVertex3f(-0.19+i,-0.1,-0.21);
        glVertex3f(-0.1+i,-0.2,-0.21);
    glEnd();

}


/// lower inside triangles
for (float i=0.0;i<1;i+=0.4){
        glColor3ub(135,74,46);
    glBegin(GL_POLYGON);
        glVertex3f(-0.266+i,-0.2,-0.22);
        glVertex3f(-0.19+i,-0.125,-0.22);
        glVertex3f(-0.124+i,-0.2,-0.22);
    glEnd();
}




/// lower inside triangles 2
for (float i=0.0;i<1;i+=0.4){
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
      glVertex3f(-0.236+i,-0.2,-0.23);
        glVertex3f(-0.19+i,-0.15,-0.23);
        glVertex3f(-0.148+i,-0.2,-0.23);
    glEnd();
}

///-------------------------------------------------------------------
/// upper diamond
glColor3f(0,1,0);

for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,0.2,-0.21);
        glVertex3f(0.1+i,0.1,-0.21);

        glVertex3f(0+i,0,-0.21);

        glVertex3f(-0.1+i,0.1,-0.21);

    glEnd();
}
///upper inside diamonds
glColor3f(0,1,1);

for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);

        glVertex3f(0+i,0.175,-0.22);
        glVertex3f(0.075+i,0.1,-0.22);
        glVertex3f(0+i,0.025,-0.22);
        glVertex3f(-0.075+i,0.1,-0.22);

    glEnd();
}
///upper inside diamonds 2
glColor3f(1,0,1);

for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);

        glVertex3f(0+i,0.15,-0.23);
        glVertex3f(0.05+i,0.1,-0.23);
        glVertex3f(0+i,0.05,-0.23);
        glVertex3f(-0.05+i,0.1,-0.23);

    glEnd();
}

/// lower diamond
glColor3f(0,1,0);
for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,0,-0.21);
        glVertex3f(0.1+i,-0.1,-0.21);
        glVertex3f(0+i,-0.2,-0.21);
        glVertex3f(-0.1+i,-0.1,-0.21);

    glEnd();
}
/// lower inside diamond
glColor3f(0,0,1);
for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,-0.025,-0.22);
        glVertex3f(0.075+i,-0.1,-0.22);
        glVertex3f(0+i,-0.175,-0.22);
        glVertex3f(-0.075+i,-0.1,-0.22);

    glEnd();
}
/// lower inside diamond 2
glColor3f(1,0,0);
for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,-0.05,-0.23);
        glVertex3f(0.05+i,-0.1,-0.23);
        glVertex3f(0+i,-0.15,-0.23);
        glVertex3f(-0.05+i,-0.1,-0.23);

    glEnd();
}



/// centered diamond
 for(float i=0.0;i<0.7;i+=0.4){
     glColor3ub(17,55,66);
   glBegin(GL_POLYGON);
          glVertex3f(0.21+i,0.1,-0.21);
        glVertex3f(0.3+i,0,-0.21);

        glVertex3f(0.21+i,-0.1,-0.21);

        glVertex3f(0.115+i,0,-0.21);


    glEnd();
}
/// center inside diamonds
for(float i=0.0;i<0.7;i+=0.4){
    glColor3f(0,0,1);
   glBegin(GL_POLYGON);
          glVertex3f(0.21+i,0.075,-0.22);
        glVertex3f(0.275+i,0,-0.22);
        glVertex3f(0.21+i,-0.075,-0.22);
        glVertex3f(0.14+i,0,-0.22);

    glEnd();
}
/// center inside diamonds(Polygons)
for(float i=0.0;i<0.7;i+=0.4){
   glColor3f(1,0,1);
   glBegin(GL_POLYGON);
          glVertex3f(0.21+i,0.05,-0.23);

        glVertex3f(0.25+i,0,-0.23);

        glVertex3f(0.21+i,-0.05,-0.23);

        glVertex3f(0.165+i,0,-0.23);

    glEnd();
}

glFlush();



}

void Back(){


/// the first 6 lines

glColor3f(1,0,0);
        glBegin(GL_POLYGON);
        glVertex3f(-0.7,-0.1,-0.14);
        glVertex3f(-0.6,0,-0.14);
        glVertex3f(-0.6,0,-0.14);
        glVertex3f(-0.7,0.1,-0.14);
    glEnd();
    glFlush();
///---------------
 glColor3f(0,0,0);
        glBegin(GL_POLYGON);
        glVertex3f(-0.7,-0.2,-0.15);
        glVertex3f(-0.5,0,-0.15);
        glVertex3f(-0.7,0.2,-0.15);
    glEnd();
    glFlush();

///--------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(1,0,1);
        glVertex3f(-0.7,0.2,-0.16);
        glVertex3f(-0.6,0.2,-0.16);
        glVertex3f(-0.4,0,-0.16);
        glVertex3f(-0.6,-0.2,-0.16);
        glVertex3f(-0.7,-0.2,-0.16);
    glEnd();
    glFlush();

///---------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(0,0,1);
        glVertex3f(-0.7,0.2,-0.17);
        glVertex3f(-0.5,0.2,-0.17);
        glVertex3f(-0.3,0,-0.17);
        glVertex3f(-0.5,-0.2,-0.17);
        glVertex3f(-0.7,-0.2,-0.17);
    glEnd();
    glFlush();


///---------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(0,1,1);
        glVertex3f(-0.7,0.2,-0.18);
        glVertex3f(-0.4,0.2,-0.18);
        glVertex3f(-0.2,0,-0.18);
        glVertex3f(-0.4,-0.2,-0.18);
        glVertex3f(-0.7,-0.2,-0.18);
    glEnd();
    glFlush();

///---------------------------------------------------
 glBegin(GL_POLYGON);
        glColor3f(1,0,1);
        glVertex3f(-0.7,0.2,-0.19);
        glVertex3f(-0.3,0.2,-0.19);
        glVertex3f(-0.1,0,-0.19);
        glVertex3f(-0.3,-0.2,-0.19);
        glVertex3f(-0.7,-0.2,-0.19);
    glEnd();
    glFlush();

///---------------------------------------------------
/// upper triangle


glColor3ub(255,255,0);
for (float i=0.0;i<1;i+=0.4){
    glBegin(GL_POLYGON);
        glVertex3f(-0.29+i,0.2,-0.19);
        glVertex3f(-0.19+i,0.1,-0.19);
        glVertex3f(-0.1+i,0.2,-0.19);
    glEnd();
}
/// upper inside triangles
glColor3ub(255,0,255);
for (float i=0.0;i<1;i+=0.4){
    glBegin(GL_POLYGON);
        glVertex3f(-0.266+i,0.2,-0.18);
        glVertex3f(-0.19+i,0.125,-0.18);
        glVertex3f(-0.124+i,0.2,-0.18);
    glEnd();
}

/// upper inside triangles 2
for (float i=0.0;i<1;i+=0.4){
glColor3ub(0,255,255);
    glBegin(GL_POLYGON);
        glVertex3f(-0.236+i,0.2,-0.17);
        glVertex3f(-0.19+i,0.15,-0.17);
        glVertex3f(-0.148+i,0.2,-0.17);
    glEnd();
}
///-------------------------------------------------------------------

///lower triangles

for (float i=0.0;i<1;i+=0.4){
    glBegin(GL_POLYGON);
         glVertex3f(-0.29+i,-0.2,-0.19);
        glVertex3f(-0.19+i,-0.1,-0.19);
        glVertex3f(-0.1+i,-0.2,-0.19);
    glEnd();

}


/// lower inside triangles
for (float i=0.0;i<1;i+=0.4){
        glColor3f(1,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.266+i,-0.2,-0.18);
        glVertex3f(-0.19+i,-0.125,-0.18);
        glVertex3f(-0.124+i,-0.2,-0.18);
    glEnd();
}




/// lower inside triangles 2
for (float i=0.0;i<1;i+=0.4){
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
      glVertex3f(-0.236+i,-0.2,-0.17);
        glVertex3f(-0.19+i,-0.15,-0.17);
        glVertex3f(-0.148+i,-0.2,-0.17);
    glEnd();
}

///-------------------------------------------------------------------
/// upper diamond
glColor3f(0,1,0);

for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,0.2,-0.19);
        glVertex3f(0.1+i,0.1,-0.19);
        glVertex3f(0+i,0,-0.19);
        glVertex3f(-0.1+i,0.1,-0.19);

    glEnd();
}
///upper inside diamonds
glColor3f(0,1,1);

for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);

        glVertex3f(0+i,0.175,-0.18);
        glVertex3f(0.075+i,0.1,-0.18);
        glVertex3f(0+i,0.025,-0.18);
        glVertex3f(-0.075+i,0.1,-0.18);

    glEnd();
}
///upper inside diamonds 2
glColor3f(1,0,1);

for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);

        glVertex3f(0+i,0.15,-0.17);
        glVertex3f(0.05+i,0.1,-0.17);
        glVertex3f(0+i,0.05,-0.17);
        glVertex3f(-0.05+i,0.1,-0.17);

    glEnd();
}

/// lower diamond
glColor3f(0,1,0);
for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,0,-0.19);
        glVertex3f(0.1+i,-0.1,-0.19);
        glVertex3f(0+i,-0.2,-0.19);
        glVertex3f(-0.1+i,-0.1,-0.19);

    glEnd();
}
/// lower inside diamond
glColor3f(0,0,1);
for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,-0.025,-0.18);
        glVertex3f(0.075+i,-0.1,-0.18);
        glVertex3f(0+i,-0.175,-0.18);
        glVertex3f(-0.075+i,-0.1,-0.18);

    glEnd();
}
/// lower inside diamond 2
glColor3f(1,0,0);
for(float i=0.0;i<0.7;i+=0.4){
   glBegin(GL_POLYGON);
        glVertex3f(0+i,-0.05,-0.17);
        glVertex3f(0.05+i,-0.1,-0.17);
        glVertex3f(0+i,-0.15,-0.17);
        glVertex3f(-0.05+i,-0.1,-0.17);

    glEnd();
}



/// centered diamond
 for(float i=0.0;i<0.7;i+=0.4){
     glColor3f(0,0,0);
   glBegin(GL_POLYGON);
          glVertex3f(0.21+i,0.1,-0.19);
        glVertex3f(0.3+i,0,-0.19);
        glVertex3f(0.21+i,-0.1,-0.19);
        glVertex3f(0.115+i,0,-0.19);


    glEnd();
}
/// center inside diamonds
for(float i=0.0;i<0.7;i+=0.4){
    glColor3f(0,0,1);
   glBegin(GL_POLYGON);
        glVertex3f(0.21+i,0.075,-0.18);
        glVertex3f(0.275+i,0,-0.18);
        glVertex3f(0.21+i,-0.075,-0.18);
        glVertex3f(0.14+i,0,-0.17);

    glEnd();
}
/// center inside diamonds(Polygons)
for(float i=0.0;i<0.7;i+=0.4){
        glColor3f(1.0,0,0);
   glBegin(GL_POLYGON);
          glVertex3f(0.21+i,0.05,-0.17);
        glVertex3f(0.25+i,0,-0.17);
        glVertex3f(0.21+i,-0.05,-0.17);
        glVertex3f(0.165+i,0,-0.17);

    glEnd();
}

glFlush();

// Render Bottom Row
}



void caller2(){

//MainDriverFunction();

  Front();
  Back();


  glFlush();


}


void drawDots3D(GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat* lineColor, int num){
    GLfloat x1,x2,y1,y2, xGap, m, yGap;
    y1 = y;
    y2 = y;
    m = (4 / 7);
    x2=x;
    xGap = w / (num * 2);
    yGap = (h / 2) / num;
    glColor3fv (lineColor);
    glPointSize(3.0);
    glBegin (GL_POINTS);
        //glVertex2f (x+w,y);
    for (x1 = 0; x1 <= (num * 2); x1++ ){
        glVertex2f (x2,y1);
        glVertex2f (x2,y2);
        if(x1 < (num)){
            y1 += yGap;
            y2 -= yGap;
        }
        else{
            y1 -= yGap;
            y2 += yGap;
        }
        x2 += xGap;
    }
    glEnd ();
    glFlush();

    //glFlush();
}
void drawLine3D(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat* lineColor){
    GLfloat x1,x2,x3,x4,y1,y2,y3,y4;
    x1 = x;
    x2 = x + (w / 2);
    x3 = x + w;
    x4 = x + (w / 2);
    y1 = y;
    y2 = y - (h / 2);
    y3 = y;
    y4 = y + (h / 2);
    glColor3fv(lineColor);                      // set line color
    glLineWidth(4.0);
    glBegin(GL_LINES);                        // draw the line
        glVertex3f(x1, y1, z);
        glVertex3f(x2, y2, z);
    glEnd();
    glFlush();

    glBegin(GL_LINES);                        // draw the line
        glVertex3f(x2, y2, z);
        glVertex3f(x3, y3, z);
    glEnd();
    glFlush();

    glBegin(GL_LINES);                        // draw the line
        glVertex3f(x3, y3, z);
        glVertex3f(x4, y4, z);
    glEnd();
    glFlush();

    glBegin(GL_LINES);                        // draw the line
        glVertex3f(x4, y4, z);
        glVertex3f(x1, y1, z);
    glEnd();
    glFlush();

    //glFlush();
}

void drawDiamond3D(GLfloat* diamColor, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, bool Dtype = true){
    glColor3fv(diamColor);                      // set diamond color
    glBegin(GL_POLYGON);                        // draw the diamond
        glVertex3f(x, y, z);
        glVertex3f(x+(w/2), y-(h/2), z);
        glVertex3f(x+w, y, z);
        glVertex3f(x+(w/2), y+(h/2), z);
    glEnd();
    glFlush();

    if(Dtype)
        drawLine3D(x, y, z, w, h, BLACK_RGB);
    //glFlush();
}

void drawCenter3D(GLfloat* diamColor1, GLfloat* diamColor2, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h){
    drawDiamond3D(diamColor1, x, y, z, w, h);
    drawDiamond3D(diamColor2, (x + w/2), (y - h/2), z, w, h);
    drawDiamond3D(diamColor1, (x + w), y, z, w, h);
    drawDiamond3D(diamColor2, (x + w/2), (y + h/2), z, w, h);
}

void drawCenterT2D3D(GLfloat* diamColor1, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h){
    if(z>=0){
        drawDiamond3D(BLACK_RGB, x, y, z-0.01, w, h, false);
        drawLine3D(x, y, z+0.01, w, h, BLACK_RGB);
    }
    else{
        drawDiamond3D(BLACK_RGB, x, y, z+0.01, w, h, false);
        drawLine3D(x, y, z-0.01, w, h, BLACK_RGB);
    }
    drawDiamond3D(diamColor1, (x + w/8), (y - h/4), z, (w-(w/4)), (((w-(w/4))*4)/7), false);
    drawDiamond3D(diamColor1, (x + w/8), (y + h/4), z,(w-(w/4)), (((w-(w/4))*4)/7), false);
    //drawLine3D(x, y, z, w, h, BLACK_RGB);
}
void drawSmallD3D(GLfloat* diamColor1, GLfloat* diamColor2, GLfloat* diamColor3, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, int num){
    bool colorSwitch = true;
    GLfloat y1 = y;
    int c = 0;
    do{
        if(c == (num/2)){
            diamColor2 = diamColor3;
        }
        if(colorSwitch){
            drawDiamond3D(diamColor1, x, y, z, w, h);
            drawDiamond3D(diamColor1, x, y1, z, w, h);
            colorSwitch = !colorSwitch;
        }
        else{
            drawDiamond3D(diamColor2, x, y, z, w, h);
            drawDiamond3D(diamColor2, x, y1, z, w, h);
            colorSwitch = !colorSwitch;
        }
        c++;
        x = x +(w/2);
        if (c < (num/2)+1){
            y = y + (h/2);
            y1 = y1 - (h/2);
        }
        else{
            y = y - (h/2);
            y1 = y1 + (h/2);
        }
    }while(c<num);
}
void hananFront()
{
    GLfloat GREY_RGB[] = {0.5, 0.5, 0.5};
    glColor3fv(GREY_RGB);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,-0.20,0);
        glVertex3f(.20,-0.20,0);
        glVertex3f(.20,.50,0);
        glVertex3f(-0.20,.50,0);
    glEnd();
    glFlush();
    //glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1.0,1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,.20,.1);
        glVertex3f(.20,.20,.1);
        glVertex3f(.20,.10,.1);
        glVertex3f(-0.20,.10,.1);
    glEnd();
    glFlush();
    glColor4f(0.0,0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,.10,.1);
        glVertex3f(.20,.10,.1);
        glVertex3f(.20,0.0,.1);
        glVertex3f(-0.20,0.0,.1);
 glEnd();
    glFlush();
    glColor4f(1.0,1.0,0.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,0.0,.1);
        glVertex3f(.20,0.0,.1);
        glVertex3f(.20,-0.10,.1);
        glVertex3f(-0.20,-0.10,.1);
     glEnd();
    glFlush();
    glColor4f(1.0,0.5,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,-0.10,.1);
        glVertex3f(.20,-0.10,.1);
        glVertex3f(.20,-0.20,.1);
        glVertex3f(-0.20,-0.20,.1);


    glEnd();
    glFlush();
}
void hananBack()
{

   //glClear(GL_COLOR_BUFFER_BIT);


 glColor4f(1.0,1.0,0.0,0.0);
  glBegin(GL_POLYGON);

        glVertex3f(-0.20,.20,-0.1);
        glVertex3f(.20,.20,-0.1);
        glVertex3f(.20,.10,-0.1);
        glVertex3f(-0.20,.10,-0.1);
 glEnd();
    glFlush();
    glColor4f(0.0,0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,.10,-0.1);
        glVertex3f(.20,.10,-0.1);
        glVertex3f(.20,0.0,-0.1);
        glVertex3f(-0.20,0.0,-0.1);
 glEnd();
    glFlush();
    glColor4f(1.0,1.0,0.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,0.0,-0.1);
        glVertex3f(.20,0.0,-0.1);
        glVertex3f(.20,-0.10,-0.1);
        glVertex3f(-0.20,-0.10,-0.1);
 glEnd();
    glFlush();
    glColor4f(1.0,0.5,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.20,-0.10,-0.1);
        glVertex3f(.20,-0.10,-0.1);
        glVertex3f(.20,-0.20,-0.1);
        glVertex3f(-0.20,-0.20,-0.1);
    glEnd();
    glFlush();
}

void henockFrontandBack(){
    GLfloat bigW = 1.25; //big diamond width
    GLfloat smallW = (2.3/2.8); //small diamond width
    GLfloat biggerW = 1; //Main diamond width
    GLfloat yi = 0; //y-axis initial
    GLfloat w = (bigW / 6); // current width
    GLfloat h = (w*4)/7; // current height
    bool colorSwitchY = true;
    GLfloat e = ( ( (bigW + (bigW/3) )*4 ) / 7) - h;//y-axis increment
    GLfloat x = 0; //x-axis initial
    GLfloat x1= x-(w/2)-0.03;
    w = biggerW/4;
    h = (w*4)/7;
    GLfloat SdW = bigW/6;
    GLfloat SdH = (SdW*4)/7;
    GLfloat d1 = ((bigW / 6) * 8 ) + 0.06;//x-axis interval
    yi = ((bigW*4)/14) + (((bigW/6)*4)/14);
    GLfloat y = yi;
    GLfloat i=-0.5;
    int loopC = 0;
    GLfloat fi=0;
    do{
        drawDots3D((i-0.0625), y, (1.125), (((1.125)*4)/7), BLACK_RGB, 19);
        drawDiamond3D(RED_RGB, i, y, 0, biggerW, (biggerW*4)/7);
        drawCenter3D(YELLOW_RGB, PURPLE_RGB, (i + w), y, 0.05, w, h);
        drawCenter3D(YELLOW_RGB, PURPLE_RGB, (i + w), y, -0.05, w, h);
        drawSmallD3D(ORANGE_RGB, WHITE_RGB, GREEN_RGB, (i-0.125-SdW), y, 0, SdW, SdH, 15);
        y = -yi;
        loopC++;
        fi=i-0.15-SdW;
    }while(loopC < 2);
    smallW= ((SdW*4)+0.125);
    //i = fi-(smallW/2);

    y=0;
    GLfloat newH = yi + SdH + 0.25;
    GLfloat newW = (newH * 7)/4;
    i=fi - (newW/2) - 0.08;
    w=(newW/7);
    h=(w*4)/7;
    smallW = (w*4);
    GLfloat i2 = fi - (smallW/2)- 0.08;
    drawDots3D((i2-0.05), y, (smallW+0.1), (((smallW+0.1)*4)/7), BLACK_RGB, 14);
    drawDiamond3D(ORANGE_RGB, i2, y, 0, smallW, (smallW*4)/7);
    drawCenterT2D3D(ORANGE_RGB, (i2 + (smallW/4)), y, 0.05, (smallW/2), (((smallW/2)*4)/7));
    drawCenterT2D3D(ORANGE_RGB, (i2 + (smallW/4)), y, -0.05, (smallW/2), (((smallW/2)*4)/7));
    drawSmallD3D(RED_RGB, PURPLE_RGB, YELLOW_RGB, i, y,0, w, h, 13);
    i = i+ (fi*-2) + 0.16;
    i2 = i2+ (fi*-2) + 0.16;
    drawDots3D((i2-0.05), y, (smallW+0.1), (((smallW+0.1)*4)/7), BLACK_RGB, 14);
    drawDiamond3D(GREEN_RGB, i2, y, 0, smallW, (smallW*4)/7);
    drawCenterT2D3D(GREEN_RGB, (i2 + (smallW/4)), y, 0.05, (smallW/2), (((smallW/2)*4)/7));
    drawCenterT2D3D(GREEN_RGB, (i2 + (smallW/4)), y, -0.05, (smallW/2), (((smallW/2)*4)/7));
    drawSmallD3D(RED_RGB, PURPLE_RGB, YELLOW_RGB, i, y,0, w, h, 13);
}
void caller(){
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    hananFront();
    hananBack();
    glFlush();
}
void caller1(){
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    henockFrontandBack();
    glFlush();
}



/* GLUI control callback                                                 */

void control_cb( int control )
{
  if ( control == LIGHT0_ENABLED_ID ) {
    if ( light0_enabled ) {
      glEnable( GL_LIGHT0 );
      light0_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT0 );
      light0_spinner->disable();
    }
  }
  else if ( control == LIGHT1_ENABLED_ID ) {
    if ( light1_enabled ) {
      glEnable( GL_LIGHT1 );
      light1_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT1 );
      light1_spinner->disable();
    }
  }
  else if ( control == LIGHT0_INTENSITY_ID ) {
    float v[] = {
      light0_diffuse[0],  light0_diffuse[1],
      light0_diffuse[2],  light0_diffuse[3] };

    v[0] *= light0_intensity;
    v[1] *= light0_intensity;
    v[2] *= light0_intensity;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT1_INTENSITY_ID ) {
    float v[] = {
      light1_diffuse[0],  light1_diffuse[1],
      light1_diffuse[2],  light1_diffuse[3] };

    v[0] *= light1_intensity;
    v[1] *= light1_intensity;
    v[2] *= light1_intensity;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
  }
  else if ( control == ENABLE_ID )
  {
    glui2->enable();
  }
  else if ( control == DISABLE_ID )
  {
    glui2->disable();
  }
  else if ( control == SHOW_ID )
  {
    glui2->show();
  }
  else if ( control == HIDE_ID )
  {
    glui2->hide();
  }
}

/**************************************** myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
  case 27:
  case 'q':
    exit(0);
    break;
  };

  glutPostRedisplay();
}


/***************************************** myGlutMenu() ***********/

void myGlutMenu( int value )
{
  myGlutKeyboard( value, 0, 0 );
}


/***************************************** myGlutIdle() ***********/

void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */

  glutPostRedisplay();
}

/***************************************** myGlutMouse() **********/

void myGlutMouse(int button, int button_state, int x, int y )
{
}


/***************************************** myGlutMotion() **********/

void myGlutMotion(int x, int y )
{
  glutPostRedisplay();
}

/**************************************** myGlutReshape() *************/

void myGlutReshape( int x, int y )
{
  int tx, ty, tw, th;
  GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
  glViewport( tx, ty, tw, th );

  xy_aspect = (float)tw / (float)th;

  glutPostRedisplay();
}


/************************************************** draw_axes() **********/
/* Disables lighting, then draws RGB axes                                */



/***************************************** myGlutDisplay() *****************/

void myGlutDisplay( void )
{
  glClearColor( .9f, .9f, .9f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .2, 15.0 );

  glMatrixMode( GL_MODELVIEW );

  glLoadIdentity();
  glMultMatrixf( lights_rotation );
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  glLoadIdentity();
  glTranslatef( 0.2, 0.0, -2.6f );
  glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );


  glScalef( scale, scale, scale );

  /*** Now we render object, using the variables 'obj_type', 'segments', and
    'wireframe'.  These are _live_ variables, which are transparently
    updated by GLUI ***/

  glPushMatrix();
  glTranslatef( -.5, 0.0, 0.0 );
  glMultMatrixf( sphere_rotate );
  if ( obj_type == 0 )
    caller();
    else if ( obj_type == 1 )
        caller2();
  else
    caller1();



    glEnable( GL_LIGHTING );


  glutSwapBuffers();
}


/**************************************** main() ********************/

int main(int argc, char* argv[])
{
  /****************************************/
  /*   Initialize GLUT and create window  */
  /****************************************/

  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1000, 600 );

  main_window = glutCreateWindow( "Ethiopian Cultural  Cloth" );
  glutDisplayFunc( myGlutDisplay );
  GLUI_Master.set_glutReshapeFunc( myGlutReshape );
  GLUI_Master.set_glutKeyboardFunc( myGlutKeyboard );
  GLUI_Master.set_glutSpecialFunc( NULL );
 initGL();

  /****************************************/
  /*       Set up OpenGL lights           */
  /****************************************/

  glEnable(GL_LIGHTING);
  glEnable( GL_NORMALIZE );

  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

  /****************************************/
  /*          Enable z-buferring          */
  /****************************************/

  glEnable(GL_DEPTH_TEST);

  /****************************************/
  /*         Here's the GLUI code         */
  /****************************************/

  printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

  /*** Create the side subwindow ***/
  glui = GLUI_Master.create_glui_subwindow( main_window,
					    GLUI_SUBWINDOW_RIGHT );



  /******** Add some controls for lights ********/

  GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Lights", true );

  GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Light 1" );

  new GLUI_Checkbox( light0, "Enabled", &light0_enabled,
                     LIGHT0_ENABLED_ID, control_cb );
  light0_spinner =
    new GLUI_Spinner( light0, "Intensity:",
                      &light0_intensity, LIGHT0_INTENSITY_ID,
                      control_cb );
  light0_spinner->set_float_limits( 0.0, 1.0 );
  GLUI_Scrollbar *sb;
  sb = new GLUI_Scrollbar( light0, "Red",GLUI_SCROLL_HORIZONTAL,
                           &light0_diffuse[0],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light0, "Green",GLUI_SCROLL_HORIZONTAL,
                           &light0_diffuse[1],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light0, "Blue",GLUI_SCROLL_HORIZONTAL,
                           &light0_diffuse[2],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);



  /*** Add another rollout ***/
  GLUI_Rollout *options = new GLUI_Rollout(glui, "Options", true );
    radio = new GLUI_RadioGroup(options,&obj_type,4,control_cb);

  new GLUI_RadioButton( radio, "Tilit 1" );
  new GLUI_RadioButton( radio, "Tilit 2" );
  new GLUI_RadioButton( radio, "Tilit 3" );

  /**** Add listbox ****/

  new GLUI_StaticText( glui, "" );




  new GLUI_StaticText( glui, "" );

  /****** A 'quit' button *****/
  new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );


  /**** Link windows to GLUI, and register idle callback ******/

  glui->set_main_gfx_window( main_window );


  /*** Create the bottom subwindow ***/
  glui2 = GLUI_Master.create_glui_subwindow( main_window,
                                             GLUI_SUBWINDOW_LEFT );
  glui2->set_main_gfx_window( main_window );

  GLUI_Spinner *scale_spinner = new GLUI_Spinner( glui2, "Scale:", &scale);
  scale_spinner->set_float_limits( .2f, 4.0 );
  scale_spinner->set_alignment( GLUI_ALIGN_LEFT );

  GLUI_Rotation *sph_rot = new GLUI_Rotation(glui2, "Rotate", sphere_rotate );
  sph_rot->set_spin( .98 );

  GLUI_Rotation *lights_rot = new GLUI_Rotation(glui2, "Blue Light", lights_rotation );
  lights_rot->set_spin( .82 );

  GLUI_Translation *trans_xy =
    new GLUI_Translation(glui2, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
  trans_xy->set_speed( .005 );

  GLUI_Translation *trans_x =
    new GLUI_Translation(glui2, "Objects X", GLUI_TRANSLATION_X, obj_pos );
  trans_x->set_speed( .005 );

  GLUI_Translation *trans_y =
    new GLUI_Translation( glui2, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
  trans_y->set_speed( .005 );

  GLUI_Translation *trans_z =
    new GLUI_Translation( glui2, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
  trans_z->set_speed( .005 );

#if 0
  /**** We register the idle callback with GLUI, *not* with GLUT ****/
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
#endif

  /**** Regular GLUT main loop ****/

  glutMainLoop();

  return EXIT_SUCCESS;
}




