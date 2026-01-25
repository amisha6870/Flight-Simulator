#include <windows.h>
#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <cmath>

// Background image dimensions
int backgroundWidth = 1280;
int backgroundHeight = 720;

// Sun position
int SunX = 0;
int SunY = backgroundHeight - 20;
float sunAngle = 0.0f;

// Wheel Angle
float wheelAngle = 0.0f;

// Car position
int carX = 1280+200;

// Wheel position
float wheelPositionX = backgroundWidth ;
float wheelPositionY = backgroundHeight;

// Animation update rate (milliseconds)
const int animationUpdateRate = 10;

// Pillar properties
const int pillarWidth = 20;
const int pillarHeight = 400;
const int pillarOffset = 100;

// Wire properties
const int wireHeight = 400-3;
const int wireCurveHeight = 25;
const float wireCurveIntensity = 0.05f;

// Function to draw a pillar
void drawPillar(float xPos, int increaseheight) {
    glColor3f(0.1f, 0.1f, 0.1f); // Semi Black color

    glBegin(GL_QUADS);
    glVertex2f(xPos - pillarWidth / 2, 0 + increaseheight);
    glVertex2f(xPos + pillarWidth / 2, 0 + increaseheight);
    glVertex2f(xPos + pillarWidth / 2, pillarHeight + increaseheight);
    glVertex2f(xPos - pillarWidth / 2, pillarHeight + increaseheight);
    glEnd();
}

// Function to draw the wire
void drawWire(float xPos1, float xPos2, int increaseheight) {
    glColor3f(0.898, 0.945, 0.81); // Ash gray color

    glBegin(GL_LINE_STRIP);
    glVertex2f(xPos1, wireHeight + increaseheight);

    float middleX = (xPos1 + xPos2) / 2.0f;
    float middleY = wireHeight - wireCurveHeight;
    glVertex2f(middleX, middleY + increaseheight-20);

    glVertex2f(xPos2, wireHeight + increaseheight);
    glEnd();
}

// Function to handle window resizing
void resize2(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Function to draw the sun
void drawSun(){
    glColor3f(0.9, 0.1, 0.1); // Red color

    const float radius = 50.0f;
    const int numTriangles = 50;
    const float angleIncrement = 2.0f * M_PI / numTriangles;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(SunX, SunY); // Center of the sun
    for (int i = 0; i <= numTriangles; ++i)
    {
        const float angle = i * angleIncrement + sunAngle;
        const float px = SunX + radius * cos(angle);
        const float py = SunY + radius * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();
}

// Code to make a house in a village
void drawSunRays(){
    int increase=300;
    // Draw the first ray
    glColor3f(0.9, 0.1, 0.1); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(45, 705);
    glVertex2f(170, 705);
    glVertex2f(170, 705);
    glVertex2f(45, 714);
    glEnd();

    // Draw the second ray
    glColor3f(0.9, 0.1, 0.1); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(40, 680);
    glVertex2f(160, 630);
    glVertex2f(160, 630);
    glVertex2f(40, 689);
    glEnd();

    // Draw the third ray
    glColor3f(0.9, 0.1, 0.1); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(25,655);
    glVertex2f(150,555);
    glVertex2f(150,555);
    glVertex2f(25,664);
    glEnd();

    // Draw the fourth ray
    glColor3f(0.9, 0.1, 0.1); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(60, 530);
    glVertex2f(60, 530);
    glVertex2f(8, 670);
    glVertex2f(0, 670);
    glEnd();
}


// Function to handle aeroplane/airplane
void drawWheel() {
    // Draw a wheel at the current position
    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color

    glVertex2f(wheelPositionX - 0 , wheelPositionY - 20);
    glVertex2f(wheelPositionX + 20,wheelPositionY - 60);
    glVertex2f(wheelPositionX + 240 , wheelPositionY + 90);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color
    glVertex2f(wheelPositionX + 240 , wheelPositionY + 80);
    glVertex2f(wheelPositionX - 20 , wheelPositionY -20);
    glVertex2f(wheelPositionX + 20,wheelPositionY - 50);
    glEnd();

}

void drawTreeCloudLike(int moveobject, int increase_height){
    // Draw the tree trunk
    glColor3f(0.4, 0.2, 0.0); // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(610+moveobject, 200+increase_height);
    glVertex2f(635+moveobject, 200+increase_height);
    glVertex2f(635+moveobject, 300+increase_height);
    glVertex2f(610+moveobject, 300+increase_height);
    glEnd();

    // Draw the tree top (cloud-like shape)
    glColor3f(0.0, 0.6, 0.0); // Green color
    glBegin(GL_POLYGON);
    float radius = 50.0;
    int numSegments = 100;
    for (int i = 0; i < numSegments; ++i) {
        float angle = (2.0 * M_PI * i) / numSegments;
        float x = moveobject+15+610 + radius * cos(angle);
        float y = 320 +increase_height + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw another circle for tree top (cloud-like shape)
    glColor3f(0.0, 0.6, 0.0); // Green color
    glBegin(GL_POLYGON);
    float radius2 = 50.0;
    int numSegments2 = 100;
    for (int i = 0; i < numSegments2; ++i) {
        float angle = (2.0 * M_PI * i) / numSegments2;
        float x = 650+moveobject + radius2 * cos(angle);
        float y = 340+increase_height + radius2 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw another circle for tree top (cloud-like shape)
    glColor3f(0.0, 0.6, 0.0); // Green color
    glBegin(GL_POLYGON);
    float radius3 = 60.0;
    int numSegments3 = 100;
    for (int i = 0; i < numSegments3; ++i) {
        float angle = (2.0 * M_PI * i) / numSegments3;
        float x = 610+moveobject + radius3 * cos(angle);
        float y = 360+increase_height + radius3 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawTreeCloudLike2(int moveobject, int increase_height){
    // Draw the tree trunk
    glColor3f(0.4, 0.2, 0.0); // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(610+moveobject, 200+increase_height-100);
    glVertex2f(635+moveobject, 200+increase_height-100);
    glVertex2f(635+moveobject, 300+increase_height);
    glVertex2f(610+moveobject, 300+increase_height);
    glEnd();

    // Draw the tree top (cloud-like shape)
    glColor3f(0.0, 0.6, 0.0); // Green color
    glBegin(GL_POLYGON);
    float radius = 85;
    int numSegments = 100;
    for (int i = 0; i < numSegments; ++i) {
        float angle = (2.0 * M_PI * i) / numSegments;
        float x = moveobject+15+610 + radius * cos(angle);
        float y = 320 +increase_height + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw another circle for tree top (cloud-like shape)
    glColor3f(0.0, 0.6, 0.0); // Green color
    glBegin(GL_POLYGON);
    float radius2 = 85.0;
    int numSegments2 = 100;
    for (int i = 0; i < numSegments2; ++i) {
        float angle = (2.0 * M_PI * i) / numSegments2;
        float x = 650+moveobject + radius2 * cos(angle);
        float y = 340+increase_height + radius2 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw another circle for tree top (cloud-like shape)
    glColor3f(0.0, 0.6, 0.0); // Green color
    glBegin(GL_POLYGON);
    float radius3 = 85.0;
    int numSegments3 = 100;
    for (int i = 0; i < numSegments3; ++i) {
        float angle = (2.0 * M_PI * i) / numSegments3;
        float x = 610+moveobject + radius3 * cos(angle);
        float y = 360+increase_height + radius3 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

/* Circle_Model */
void circle(GLdouble rad){
    float PI = 3.1416;
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;
    glBegin(GL_POLYGON);
    {
        for (int i = 0; i <= 50; i++, theta += delTheta)
        {
            glVertex2f(rad * cos(theta), rad * sin(theta));
        }
    }
    glEnd();
}

// Code to make a house in a village
void drawVillageHouse(int increase_height){
    int increase=300;
    // Draw the house
    glColor3f(0.7, 0.4, 0.1); // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(increase+200, 200+increase_height);
    glVertex2f(increase+300, 200+increase_height);
    glVertex2f(increase+300, 300+increase_height);
    glVertex2f(increase+200, 300+increase_height);
    glEnd();

    // Draw the roof
    glColor3f(0.619, 0.192, 0.235);
   /// glColor3f(0.9, 0.1, 0.1); // Red color
    glBegin(GL_TRIANGLES);
    glVertex2f(increase+300, 300+increase_height);
    glVertex2f(increase+200, 300+increase_height);
    glVertex2f(increase+250, increase+50+increase_height);
    glEnd();

    // Draw the door
    glColor3f(0.4, 0.2, 0.1); // Dark brown color
    glBegin(GL_POLYGON);
    glVertex2f(increase+200+40, 200+increase_height);
    glVertex2f(increase+200+70, 200+increase_height);
    glVertex2f(increase+200+70, 200+60+increase_height);
    glVertex2f(increase+200+40, 200+60+increase_height);
    glEnd();

    // Draw the window
    glColor3f(0.8, 0.8, 0.8); // Light gray color
}

void staircase(int increase_height){
///this part is for
    //Background Stairs of house1
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(100, 200+increase_height);
    glVertex2f(300, 200+increase_height);
    glVertex2f(100, 250+increase_height);
    glEnd();
}


// Code to make a house in a village
void drawVillageHouse2(int increase_height){
    int increase=300;
    // Draw the house
    glColor3f(0.7, 0.4, 0.1); // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(50, 200+increase_height);
    glVertex2f(150, 200+increase_height);
    glVertex2f(150, 400+increase_height);
    glVertex2f(50, 400+increase_height);
    glEnd();

    // Draw the roof
    glColor3f(0.619, 0.192, 0.235);
    glBegin(GL_TRIANGLES);
    glVertex2f(150, 400+increase_height);
    glVertex2f(50, 400+increase_height);
    glVertex2f(100, 400+50+increase_height);
    glEnd();

    // Draw the door
    glColor3f(0.4, 0.2, 0.1); // Dark brown color
    glBegin(GL_POLYGON);
    glVertex2f(70+5, 200+increase_height);
    glVertex2f(110+5, 200+increase_height);
    glVertex2f(110+5, 400+increase_height-30*2);
    glVertex2f(70+5, 400+increase_height-30*2);
    glEnd();

    // Draw the window
    glColor3f(0.8, 0.8, 0.8); // Light gray color

}



// Function to draw the road
void drawRoad(int y){
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0+y);
    glVertex2f(backgroundWidth, 0+y);
    glVertex2f(backgroundWidth, 200+y);
    glVertex2f(0, 200+y);
    glEnd();

    // Draw road stripes
    glColor3f(0.718, 0.845, 0.91); // Ash cloud color
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 100+y);
    glVertex2f(backgroundWidth, 100+y);
    glVertex2f(backgroundWidth, 110+y);
    glVertex2f(0, 110+y);
    glEnd();
}

// Function to draw the roadside pathway/footpath
void drawFootpath(int y){
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(backgroundWidth, 0);
    glVertex2f(backgroundWidth, 200);
    glVertex2f(0, 200);
    glEnd();

    int increase_stripe= 10;
    // Draw the road stripe first ray
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(5, 0);
    glVertex2f(5+10, 60);
    glVertex2f(0+10, 60);
    glEnd();

    /*
    // Draw the road stripe second ray
    glColor3f(1.0f, 1.0f, 1.0f);//white
    glBegin(GL_POLYGON);
    glVertex2f(0+increase_stripe, 0);
    glVertex2f(5+increase_stripe, 0);
    glVertex2f(5+increase_stripe+10, 60);
    glVertex2f(0+increase_stripe+10, 60);
    glEnd();
    */

    for(int i=0; i<1400;i+=increase_stripe){

    // Draw the road stripe ray
    glColor3f(0.698, 0.745, 0.71); // Ash gray color
    glBegin(GL_POLYGON);
    glVertex2f(0+i, 0);
    glVertex2f(5+i, 0);
    glVertex2f(5+i+10, 60);
    glVertex2f(0+i+10, 60);
    glEnd();

    }
}

// Function to draw the car
void drawCar(int increase_height){

    glColor4f(1.0f, 0.7f, 0.0f, 0.0f);//yellow
    glPushMatrix();
    glTranslatef(carX, 100, 0);
    glScalef(2, 1, 1);

    // Draw car body
    glBegin(GL_POLYGON);
    glVertex2f(-60, -30+increase_height);
    glVertex2f(-60, 20+increase_height);
    glVertex2f(70, 20+increase_height);
    glVertex2f(70, -30+increase_height);
    glEnd();

    int adjustcockpit= 10;
    glBegin(GL_POLYGON);//the following points should be rotating clockwise
    glVertex2f(-35-adjustcockpit, 25+increase_height-adjustcockpit);//A
    glVertex2f(-18-adjustcockpit, 55+increase_height+adjustcockpit);//B
    glVertex2f(-5 , 55+increase_height+adjustcockpit); //C
    glVertex2f(-5 + adjustcockpit, 25+increase_height-adjustcockpit); //D
    glEnd();

    // Draw car window 1
    //glColor3f(0.698, 0.745, 0.71); // Ash gray color
    //glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green
    glBegin(GL_POLYGON);
    glVertex2f(-35, 25+increase_height-adjustcockpit/2);
    glVertex2f(-22-1, 55+increase_height);
    glVertex2f(-8, 55+increase_height);
    glVertex2f(-8, 25+increase_height-adjustcockpit/2);
    glEnd();

    // Draw car wheels
    glColor3f(0.0, 0.0, 0.0);
    const float wheelRadius = 20.0f;
    const int numTriangles = 8;
    const float angleIncrement = 2.0f * M_PI / numTriangles;

    for (int i = 0; i < numTriangles; ++i)
    {
        const float angle1 = i * angleIncrement + wheelAngle;
        const float angle2 = (i + 1) * angleIncrement + wheelAngle;

        glBegin(GL_TRIANGLES);
        glVertex2f(-30 + wheelRadius * cos(angle1), increase_height-30 + wheelRadius * sin(angle1));
        glVertex2f(-30 + wheelRadius * cos(angle2),increase_height -30 + wheelRadius * sin(angle2));
        glVertex2f(-30, -30+increase_height);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(30 + wheelRadius * cos(angle1), increase_height -30 + wheelRadius * sin(angle1));
        glVertex2f(30 + wheelRadius * cos(angle2), increase_height-30 + wheelRadius * sin(angle2));
        glVertex2f(30, -30+increase_height);
        glEnd();
    }
    glPopMatrix();
}

// Function to handle animation update
void update(int value){
    // Update wheel position
    wheelPositionX += 1.7; // Move 5 pixels to the right
    wheelPositionY += .5; // Move 5 pixels upward

    // Check if the wheel has reached the top-right corner
    if (wheelPositionX > backgroundWidth && wheelPositionY > backgroundHeight) {
        wheelPositionX = backgroundWidth-1380; // Reset X position to the left-middle
        wheelPositionY = backgroundHeight-150; // Reset Y position to the middle
    }

    // Rotate Wheel
    wheelAngle = wheelAngle - 0.4f;
    // Move the car horizontally
    carX = carX - 2;
    // Reset the positions when they reach the end of the screen
    if (carX < backgroundWidth -1380)
        carX = 1480;

    // Request redrawing of the scene
    glutPostRedisplay();
    // Schedule the next update
    glutTimerFunc(animationUpdateRate, update, 0);

    // Redraw the scene
    glutPostRedisplay();
}

// Function to handle drawing the scene
void render2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the wheel
    drawWheel();

    glutSwapBuffers();
}

// Function to display the scene
void display(){
    int increase_height= 50;
    int moveobject = 300; // in the x-axis
    glClearColor(0.258, 0.725, 0.96, 1.0); // Set background color to sky blue
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, backgroundWidth, 0, backgroundHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    drawFootpath(0);

    //draw the sun
    drawSun();
    //draw the sunrays
    drawSunRays();

    drawRoad(increase_height);
    //draw cloud like tree tops

    drawTreeCloudLike(-420, increase_height+20); // first tree
    drawTreeCloudLike(0, increase_height); // base tree
    drawTreeCloudLike2(300, increase_height+100); // third tree
    drawTreeCloudLike(610, increase_height); // third tree


    // village house function calling
    drawVillageHouse(increase_height);
    staircase(increase_height); // this will be hidden overlapped by drawVillageHouse2() because of hierarchy
    drawVillageHouse2(increase_height);

    drawCar(increase_height+60);

    drawWheel();

    //draw trees in front side of the road
    drawTreeCloudLike(-200, -200); // front first tree
    // Draw the pillars
    drawPillar(backgroundWidth * 4 / 5 +50,increase_height);
    //draw trees in front side of the road
    drawTreeCloudLike(-200+700, -200); // front first tree


    // Draw the pillars
    drawPillar(backgroundWidth / 4,increase_height);
    // Draw the wire
    drawWire(0-backgroundWidth / 4, backgroundWidth / 4, increase_height);
    drawWire(backgroundWidth / 4, backgroundWidth * 4 / 5+50,increase_height);
    drawWire(backgroundWidth * 4 / 5+50, backgroundWidth * 8 / 5+50,increase_height);

    glFlush();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv); //basic functions to initialize
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Using Single core processor and color scheme is RGB
    glutInitWindowSize(backgroundWidth, backgroundHeight);
    glutCreateWindow("Scene in a City");
    glutDisplayFunc(display); //to call the user defined function named display
    glutTimerFunc(0, update, 0);
    glutMainLoop();


    // Set up the display callback function
    glutDisplayFunc(render2);

    // Set up the resize callback function
    glutReshapeFunc(resize2);

    // Set up the update callback function
    glutTimerFunc(animationUpdateRate, update, 0);

    // Set the clear color (black)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Start the main loop
    glutMainLoop();

    return 0;
}

/*
OPENGL COLOR CODES
August 01, 2016
for Background color:
glClearColor(float red, float green, float blue, float alpha)
glClearColor(0.0,0.0,1.0,0.0);//dark blue

fill color:
glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
glColor4f(1.0f, 1.0f, 0.0f, 0.0f);//yellow
glColor4f(1.0f, 0.0f, 1.0f, 0.0f);//purple
glColor4f(0.0f, 1.0f, 1.0f, 1.0f);//light blue
glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
glColor3f(0.0f, 1.0f, 0.0f);//Green
glColor3f(0.0f, 0.0f, 1.0f);//Blue
glColor3f(0.5f, 1.0f, 1.0f);//cyan
glColor3f(0.0f, 0.0f, 0.0f);//Black
glColor3f(1.0f, 0.0f, 1.0f);//Purple
glColor3f(1.0f, 0.5f, 0.0f);//Orange
glColor3f(0.5f, 0.5f, 0.5f);//Violet
glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green
glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
glColor3f(2.0f, 0.5f, 1.0f);//Lilac
glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
glColor3f(0.1f, 0.0f, 0.1f);//Dark Purple
glColor3f(0.1f, 0.1f, 0.0f);//Bronze
glColor3f(0.0f, 0.1f, 0.1f);//Dark blue
glColor3f(0.0f, 0.1f, 0.0f);//Forest Green
glColor3f(0.1f, 0.0f, 0.0f);//Brown

*/
