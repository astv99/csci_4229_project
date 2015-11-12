// Stephen Ham
// CSCI 4229
// Final Project - First-Person Egyptian Environment
// C main file: Contains all main & "driver" code

#define LEN 8192 // Maximum length of text string
#define GL_GLEXT_PROTOTYPES // OpenGL with prototypes for glext

#include "CSCIx229.h"
#include "fp_ee.h"

// Function Prototypes
void setProjection(void);
void showInstructionsFPView(void);
void showInstructionsSkyView(void);
void moveCam(void);
void display(void);
void idle(void);
void special(int key, int x, int y);
void collisionDetections();
void key(unsigned char ch, int x, int y);
void reshape(int width, int height);

void setProjection(void)
{
    glMatrixMode(GL_PROJECTION); // Manipulate the projection matrix
    glLoadIdentity(); // Undo previous transformations
    gluPerspective(FOV, AR, 0.1, 6*DIM); // Perspective view only
    glMatrixMode(GL_MODELVIEW); // Manipulate the model matrix
    glLoadIdentity(); // Undo previous transformations
}

void showInstructionsFPView(void)
{
	glColor3f(1.0, 1.0, 1.0);
    glWindowPos2i(7, 205);
    Print("First-Person View");
    glWindowPos2i(7, 183);
    Print("- f : switch to Sky View");
    glWindowPos2i(7, 161);
    Print("- w/s : move forward/backward");
    glWindowPos2i(7, 139);
    Print("- a/d : strafe left/right");
    glWindowPos2i(7, 117);
    Print("- q/e : turn left/right");
    glWindowPos2i(7, 95);
    Print("- +/- : increase/decrease field of view");
    glWindowPos2i(7, 73);
    Print("- v : reset field of view");
    glWindowPos2i(7, 51);
    Print("- x : show/hide coordinate axes");
    glWindowPos2i(7, 29);
    Print("- p : enable/disable lighting effects");
    glWindowPos2i(7, 7);
    Print("- Esc : quit");
    glWindowPos2i(1040, 7);
    Print("Position (x, z): %.2f, %.2f", xPos, zPos);
}

void showInstructionsSkyView(void)
{
	glColor3f(1.0, 1.0, 1.0);
    glWindowPos2i(7, 117);
    Print("Sky View");
    glWindowPos2i(7, 95);
    Print("<Arrow Keys> : adjust view in indicated direction");
    glWindowPos2i(7, 73);
    Print("- f : switch to First-Person View");
    glWindowPos2i(7, 51);
    Print("- p : enable/disable lighting");
    glWindowPos2i(7, 29);
    Print("- x : show/hide coordinate axes");
    glWindowPos2i(7, 7);
    Print("- Esc : quit");
}

void moveCam(void)
{
    if (FP) // if first-person view is enabled
    {
		showInstructionsFPView();
        glRotatef(yRot, 0.0, 1.0, 0.0); // spin camera on its y-axis
        glTranslatef(-xPos, -1.5, -zPos); // move camera just above XZ-plane
    }
    else // sky-view is enabled (locked to origin)
    {
		showInstructionsSkyView();
        double Ex, Ey, Ez;
        Ex = -2 * DIM * Sin(TH) * Cos(PH);
        Ey = +2 * DIM           * Sin(PH);
        Ez = +2 * DIM * Cos(TH) * Cos(PH);
        gluLookAt(Ex,Ey,Ez , 0,0,0, 0,Cos(PH),0);
    }
}

// Called by GLUT to display the scene
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // Undo previous transformations
    glTranslatef(0, 0, 0);
    
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    moveCam();
    glShadeModel(SHADING ? GL_SMOOTH : GL_FLAT);
    
    if (LIGHT_ON)
    {
        float ambient[] = {0.45, 0.45, 0.45, 1.0};
        float diffuse[] = {0.3, 0.3, 0.3, 1.0};
        float specular[] = {0.01*SPECULAR, 0.01*SPECULAR, 0.01*SPECULAR, 1.0};
        float lightPos0[] = {+3, 1.35, -4, 0.75};
        float lightPos1[] = {+3, 1.35, +4, 0.75};
        float lightPos2[] = {-3, 1.35, +4, 0.75};
        float lightPos3[] = {-3, 1.35, -4, 0.75};
        glColor3f(1, 1, 1);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
        
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
        
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
    }
    else
        glDisable(GL_LIGHTING);
    
    renderAllEntryways();
    renderAllTrapezoidBldgs();
    renderAllObelisks();
    
    glPushMatrix();
        glTranslatef(0.0, -0.45, 0.0);
        renderPool();
        renderAllTorches();
    glPopMatrix();
    
    renderAreaWalls();
    renderGround();
    renderSkybox();
    
    glPushMatrix();
        glTranslatef(35.5, 0.0, 5.0);
        glScalef(5.0, 3.5, 5.0);
        renderPyramid();
    glPopMatrix();
    
    glDisable(GL_LIGHTING); // don't try to light the axes
    renderAxes();
	glFlush(); // Render the entire scene
	glutSwapBuffers(); // Make the rendered scene visible
}

void idle(void)
{
   double et = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // elapsed time (s)
   L_TH = fmod(90*et, 360.0);
   glutPostRedisplay();
}

// Called by GLUT when arrow key is pressed
void special(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_RIGHT :
            TH += 1;
            break;
        case GLUT_KEY_LEFT :
            TH -= 1;
            break;
        case GLUT_KEY_UP :
            PH += 1;
            break;
        case GLUT_KEY_DOWN :
            PH -= 1;
            break;
        case GLUT_KEY_PAGE_UP :
            L_PH += 0.1;
            break;
        case GLUT_KEY_PAGE_DOWN :
            L_PH -= 0.1;
            break;
    }
    
    TH %= 360;
    PH %= 360;
    setProjection();
    glutPostRedisplay();
}

void collisionDetections()
{
    // Area Walls
    if (xPos > DIM-1.0) // N wall
        xPos = DIM-1.0;
    if (xPos < -DIM+1.0) // S wall
        xPos = -DIM+1.0;
    if (zPos > DIM-1.0) // E wall
        zPos = DIM-1.0;
    if (zPos < -DIM+1.0) // W wall
        zPos = -DIM+1.0;
        
    // Entryway, left column
    if ((xPos > -14.5) && (xPos < -14.0) && (zPos > -2.00) && (zPos < -0.75))
        xPos = -14.5; // S wall
    if ((zPos < -0.55) && (zPos > -0.75) && (xPos < -13.75) && (xPos > -14.25))
        zPos = -0.55; // E wall
    if ((xPos < -13.5) && (xPos > -14.0) && (zPos > -2.00) && (zPos < -0.75))
        xPos = -13.5; // N wall
    if ((zPos > -2.2) && (zPos < -2.0) && (xPos < -13.75) && (xPos > -14.25))
        zPos = -2.2; // W wall
    // Entryway, right column    
    if ((xPos > -14.5) && (xPos < -14.0) && (zPos > 0.75) && (zPos < 2.00))
        xPos = -14.5; // S wall
    if ((zPos > 2.0) && (zPos < 2.2) && (xPos < -13.75) && (xPos > -14.25))
        zPos = 2.2; // E wall
    if ((xPos < -13.5) && (xPos > -14.0) && (zPos < 2.00) && (zPos > 0.75))
        xPos = -13.5; // N wall
    if ((zPos > 0.55) && (zPos < 0.75) && (xPos < -13.75) && (xPos > -14.25))
        zPos = 0.55; // W wall
        
    // Pool
    if ((xPos > -4.3) && (xPos < -4.1) && (zPos > -5.0) && (zPos < 5.0))
        xPos = -4.3; // S side
    if ((zPos < 5.2) && (zPos > 5.0) && (xPos > -4.0) && (xPos < 4.0))
        zPos = 5.2; // E side
    if ((xPos < 4.3) && (xPos > 4.1) && (zPos > -5.0) && (zPos < 5.0))
        xPos = 4.3; // N side
    if ((zPos > -5.2) && (zPos < -5.0) && (xPos > -4.0) && (xPos < 4.0))
        zPos = -5.2; // W side
        
    // Trapezoid Building, left
    if ((xPos > 8.7) && (xPos < 9.0) && (zPos > -10) && (zPos < -2))
        xPos = 8.7; // S side
    if ((zPos < -1.7) && (zPos > -2.0) && (xPos > 9) && (xPos < 11))
        zPos = -1.7; // E side
    if ((xPos < 11.3) && (xPos > 11) && (zPos > -10) && (zPos < -2))
        xPos = 11.3; // N side
    if ((zPos > -10.3) && (zPos < -10.0) && (xPos > 9) && (xPos < 11))
        zPos = -10.3; // W wide
        
    // Trapezoid Building, right
    if ((xPos > 8.7) && (xPos < 9.0) && (zPos > 2) && (zPos < 10))
        xPos = 8.7; // S side
    if ((zPos < 10.3) && (zPos > 10) && (xPos > 9) && (xPos < 11))
        zPos = 10.3; // E side
    if ((xPos < 11.3) && (xPos > 11) && (zPos > 2) && (zPos < 10))
        xPos = 11.3; // N side
    if ((zPos > 1.7) && (zPos < 2) && (xPos > 9) && (xPos < 11))
        zPos = 1.7; // W side
        
    // Obelisk, left
    if ((xPos > 8.7) && (xPos < 9.0) && (zPos > -15.0) && (zPos < -13.0))
        xPos = 8.7; // S side
    if ((zPos < -12.7) && (zPos > -13.0) && (xPos > 9.0) && (xPos < 11.0))
        zPos = -12.7; // E side
    if ((xPos < 11.3) && (xPos > 11.0) && (zPos > -15.0) && (zPos < -13.0))
        xPos = 11.3; // N side
    if ((zPos > -15.3) && (zPos < -15.0) && (xPos > 9.0) && (xPos < 11.0))
        zPos = -15.3; // W side
        
    // Obelisk, right
    if ((xPos > 8.7) && (xPos < 9.0) && (zPos > 13.0) && (zPos < 15.0))
        xPos = 8.7; // S side
    if ((zPos > 12.7) && (zPos < 13.0) && (xPos > 9.0) && (xPos < 11.0))
        zPos = 12.7; // W side
    if ((xPos < 11.3) && (xPos > 11.0) && (zPos > 13.0) && (zPos < 15.0))
        xPos = 11.3; // N side
    if ((zPos < 15.3) && (zPos > 15.0) && (xPos > 9.0) && (xPos < 11.0))
        zPos = 15.3; // E side
}

// Called by GLUT when non-arrow key is pressed
void key(unsigned char ch, int x, int y)
{
	switch (ch)
	{
		case 27 : // Esc key
			exit(0);
			break;
        case 'w' :
		case 'W' :
            xPos += (float)Sin(yRot) * 0.1;
            yPos -= (float)Sin(xRot) * 0.1;
            zPos -= (float)Cos(yRot) * 0.1;
            collisionDetections();
			break;
        case 'a' :
		case 'A' :
            xPos -= (float)Cos(yRot) * 0.1;
            zPos -= (float)Sin(yRot) * 0.1;
            collisionDetections();
			break;
        case 's' :
		case 'S' :
            xPos -= (float)Sin(yRot) * 0.1;
            yPos += (float)Sin(xRot) * 0.1;
            zPos += (float)Cos(yRot) * 0.1;
            collisionDetections();
			break;
        case 'd' :
		case 'D' :
            xPos += (float)Cos(yRot) * 0.1;
            zPos += (float)Sin(yRot) * 0.1;
            collisionDetections();
			break;
        case 'q' :
		case 'Q' :
            yRot -= 2.0;
            if (yRot < -360) yRot += 360;
			break;
        case 'e' :
		case 'E' :
            yRot += 2.0;
            if (yRot > 360) yRot -= 360;
			break;
        case 'f' :
        case 'F' :
            FP = 1 - FP;
        case 'v' :
		case 'V' :
			FOV = 75;
			break;
        case 'p' :
        case 'P' :
            LIGHT_ON = 1 - LIGHT_ON;
            break;
        case 'x' :
		case 'X' :
			AXES = 1 - AXES;
			break;
        case '-' :
            FOV -= 1;
            break;
        case '+' :
            FOV += 1;
            break;
	}
    
    SHINE[0] = SHININESS<0 ? 0 : pow(2.0, SHININESS);
    glutIdleFunc(LIGHT_MOVE ? idle : NULL);
    setProjection(); // Re-project
	glutPostRedisplay();
}

// Called by GLUT when window is resized
void reshape(int width, int height)
{
    AR = (height>0) ? (double)width/height : 1;
    glViewport(0, 0, width, height); // Set viewport to the entire window
    setProjection();
}

// Main method
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1280, 800); // widescreen
	glutCreateWindow("Final Project: First-Person Egypt Environment");
	glutDisplayFunc(display); // Call display() when scene should be drawn
	glutReshapeFunc(reshape); // Call reshape() when window is resized
	glutSpecialFunc(special); // Call special() when arrow key is pressed
	glutKeyboardFunc(key); // Call key() when a key is pressed
    glutIdleFunc(idle);
    TX_GROUND[0] = LoadTexBMP("block10c_1.bmp"); // Ground tile
    TX_GROUND[1] = LoadTexBMP("block10c_2.bmp"); // Ground tile (swapped)
    TX_SKY[0] = LoadTexBMP("desert_all_sides.bmp"); // Skybox sides
    TX_SKY[1] = LoadTexBMP("desert_top_bottom.bmp"); // Skybox top & bottom
    TX_WALLS[0] = LoadTexBMP("w_mural1a.bmp"); // Mural of trapezoid wall
    TX_WALLS[1] = LoadTexBMP("w_mural2a.bmp"); // Horizontal flip of mural
    TX_WALLS[2] = LoadTexBMP("trpz_wall.bmp"); // Trapezoid-building walls
    TX_WALLS[3] = LoadTexBMP("egypt01a.bmp"); // Outer & inner part of area wall
    TX_WALLS[4] = LoadTexBMP("egypt01b.bmp"); // Area wall side-segment & top
    TX_WALLS[5] = LoadTexBMP("pool_block.bmp"); // Pool bottom
    TX_WALLS[6] = LoadTexBMP("pool_side.bmp"); // Pool siding
    TX_WALLS[7] = LoadTexBMP("pool_side_seg.bmp"); // Pool side segment
    TX_WALLS[8] = LoadTexBMP("pool_top.bmp"); // Pool wall top
    TX_WALLS[9] = LoadTexBMP("grey_stone1.bmp"); // Entryway toplining
    TX_WALLS[10] = LoadTexBMP("blue_column.bmp"); // Entryway siding
    TX_WALLS[11] = LoadTexBMP("blue_trim.bmp"); // Entryway upper trim
    TX_WALLS[12] = LoadTexBMP("column_s2.bmp"); // Column style 2
    TX_WALLS[13] = LoadTexBMP("blue_triangs.bmp"); // Obelisk 4 triangles
    TX_WATER[0] = LoadTexBMP("water_s1.bmp"); // Water surface 1
    TX_TORCH[0] = LoadTexBMP("column_s1.bmp"); // Column style 1
    TX_TORCH[1] = LoadTexBMP("column_s1_sm.bmp"); // Column style 1, small
    TX_TORCH[2] = LoadTexBMP("block02a.bmp"); // Torch plate
    TX_TORCH[3] = LoadTexBMP("fire_dish_side.bmp"); // Torch fire dish siding
    TX_TORCH[4] = LoadTexBMP("fire_dish_btm.bmp"); // Torch fire dish bottom
    TX_TORCH[5] = LoadTexBMP("flame.bmp"); // Flame
	glutMainLoop(); // Pass control to GLUT for user interaction
	
	return 0;
}
