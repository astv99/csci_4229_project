// Stephen Ham
// CSCI 4229
// Final Project - First-Person Egyptian Environment
// C header file: Contains all functions used to create all scene objects

// General parameters
short TH = 0;               // Azimuth of view angle
short PH = 0;               // Elevation of view angle
short AXES = 0;             // Toggle axes
short FOV = 75;             // Field of view for perspective mode
double AR = 1;              // Aspect ratio
const float DIM = 20.0;     // Dimension of world
short TX_WALLS[15];         // Array for wall textures
short TX_SKY[2];            // Array for skybox textures
short TX_WATER[2];          // Array for water textures
short TX_TORCH[6];          // Array for torch textures
short TX_GROUND[2];         // Reference to ground texture
short FP = 1;               // Toggle 1st-person ground view vs "sky" view

// Camera values
// Initialized for startup and contain updated values as user moves the camera
float xPos = -19.0;         // x-coordinate of camera
float yPos = 0.0;           // y-coordinate of camera
float zPos = 0.0;           // z-coordinate of camera
float xRot = 0.0;           // x-rotation of camera
float yRot = 90.0;          // y-rotation of camera

// Light values
short LIGHT_ON = 1;         // "Power" status of light source
short LIGHT_MOVE = 1;       // Movement status of light source
short SHADING = 1;          // Smooth/Flat shading
short EMISSION = 30;        // Emission intensity (%)
short SPECULAR = 75;        // Specular intensity (%)
short SHININESS = 4;        // Shininess (power of two)
float SHINE[1];             // Shininess (value)
short L_TH = 90;            // Light azimuth
float L_PH = 1;             // Elevation of light

// Function prototypes
void renderPoolWallS(void);
	void renderPoolWallE(void);
	void renderPool(void);
void renderTorchSideS(void);
	void renderTorchPlateSideS(void);
	void renderTorchPlate(void);
	void renderTorchFireDishS(void);
	void renderTorch(void);
    void renderFlame(void);
	void renderAllTorches(void);
void renderObelisk(void);
	void renderAllObelisks(void);
void renderTrapezoidBldg(short tx);
	void renderAllTrapezoidBldgs(void);
void renderEntrywayColumn(void);
	void renderEntryway(void);
	void renderAllEntryways(void);
void renderOuterWall();
	void renderWallLeftSide(void);
	void renderWallBottom(void);
	void renderOneWall(void);
	void renderAreaWalls(void);
void renderPyramid();
void renderGround(void);
void renderGrid(void);
void renderSkybox(void);
void renderAxes(void);

// Create S-facing wall of pool (N wall created through transformation)
void renderPoolWallS(void)
{  
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[6]); // pool siding
        glBegin(GL_QUADS);
            glNormal3f(1.0, 0.5, 0.0);
            glTexCoord2f(00.0, 0.0); glVertex3f(-4.00, 0.00, -5.00); // inner
            glTexCoord2f(10.0, 0.0); glVertex3f(-4.00, 0.00, +5.00);
            glTexCoord2f(10.0, 1.0); glVertex3f(-4.00, 0.75, +5.00);
            glTexCoord2f(00.0, 1.0); glVertex3f(-4.00, 0.75, -5.00);
            glNormal3f(-1.0, 0.5, 0.0);
            glTexCoord2f(00.0, 0.0); glVertex3f(-4.10, 0.00, -5.00); // outer
            glTexCoord2f(10.0, 0.0); glVertex3f(-4.10, 0.00, +5.00);
            glTexCoord2f(10.0, 1.0); glVertex3f(-4.10, 0.75, +5.00);
            glTexCoord2f(00.0, 1.0); glVertex3f(-4.10, 0.75, -5.00);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[7]); // pool siding segments
        glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.00, 0.00, -5.00); // left
            glTexCoord2f(1.0, 0.0); glVertex3f(-4.10, 0.00, -5.00);
            glTexCoord2f(1.0, 1.0); glVertex3f(-4.10, 0.75, -5.00);
            glTexCoord2f(0.0, 1.0); glVertex3f(-4.00, 0.75, -5.00);
            glNormal3f(0.0, 0.0, +1.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.10, 0.00, +5.00); // right
            glTexCoord2f(1.0, 0.0); glVertex3f(-4.00, 0.00, +5.00);
            glTexCoord2f(1.0, 1.0); glVertex3f(-4.00, 0.75, +5.00);
            glTexCoord2f(0.0, 1.0); glVertex3f(-4.10, 0.75, +5.00);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[8]); // pool top & bottom
        glBegin(GL_QUADS);
            glNormal3f(0.0, +1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.10, 0.75, -5.00); // top
            glTexCoord2f(5.0, 0.0); glVertex3f(-4.10, 0.75, +5.00);
            glTexCoord2f(5.0, 1.0); glVertex3f(-4.00, 0.75, +5.00);
            glTexCoord2f(0.0, 1.0); glVertex3f(-4.00, 0.75, -5.00);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.10, 0.00, -5.00); // bottom
            glTexCoord2f(5.0, 0.0); glVertex3f(-4.10, 0.00, +5.00);
            glTexCoord2f(5.0, 1.0); glVertex3f(-4.00, 0.00, +5.00);
            glTexCoord2f(0.0, 1.0); glVertex3f(-4.00, 0.00, -5.00);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create E-facing wall of pool (W wall created through transformation)
void renderPoolWallE(void)
{   
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[6]); // pool siding
        glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.00, +0.00, +4.90); // inner
            glTexCoord2f(8.0, 0.0); glVertex3f(+4.00, +0.00, +4.90);
            glTexCoord2f(8.0, 1.0); glVertex3f(+4.00, +0.75, +4.90);
            glTexCoord2f(0.0, 1.0); glVertex3f(-4.00, +0.75, +4.90);
            glNormal3f(0.0, 0.0, +1.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.00, +0.00, +5.00); // outer
            glTexCoord2f(8.0, 0.0); glVertex3f(+4.00, +0.00, +5.00);
            glTexCoord2f(8.0, 1.0); glVertex3f(+4.00, +0.75, +5.00);
            glTexCoord2f(0.0, 1.0); glVertex3f(-4.00, +0.75, +5.00);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[8]); // pool top
        glBegin(GL_QUADS);
            glNormal3f(0.0, +1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.00, 0.75, +5.00); // top
            glTexCoord2f(5.0, 0.0); glVertex3f(+4.00, 0.75, +5.00);
            glTexCoord2f(5.0, 1.0); glVertex3f(+4.00, 0.75, +4.90);
            glTexCoord2f(0.0, 1.0); glVertex3f(-4.00, 0.75, +4.90);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create an entire single pool structure
void renderPool(void)
{
    float orange[] = {1, 0.647, 0, 1};
    float emission[]  = {0.0, 0.0, 0.01*EMISSION, 1.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, SHINE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[5]); // pool bottom
        glBegin(GL_QUADS);
            glNormal3f(0.0, +1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-4.0, 0.0, -5.0);
            glTexCoord2f(5.0, 0.0); glVertex3f(-4.0, 0.0, +5.0);
            glTexCoord2f(5.0, 4.0); glVertex3f(+4.0, 0.0, +5.0);
            glTexCoord2f(0.0, 4.0); glVertex3f(+4.0, 0.0, -5.0);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WATER[0]); // fill it w/ clear water
        glBegin(GL_QUADS);
            glNormal3f(0.0, +1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-3.999, 0.40, -4.899);
            glTexCoord2f(5.0, 0.0); glVertex3f(-3.999, 0.40, +4.899);
            glTexCoord2f(5.0, 4.0); glVertex3f(+3.999, 0.40, +4.899);
            glTexCoord2f(0.0, 4.0); glVertex3f(+3.999, 0.40, -4.899);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    renderPoolWallS(); // S wall
    glPushMatrix();
        glTranslatef(+8.1, 0.0, 0.0); // S inner wall
        renderPoolWallS();
    glPopMatrix();
    
    renderPoolWallE(); // E wall
    glPushMatrix();
        glTranslatef(0.0, 0.0, -9.9);
        renderPoolWallE(); // W wall
    glPopMatrix();
}

// Create S-facing side of torch structure
// Other sides created through transformation
void renderTorchSideS(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_TORCH[0]); // pool siding
        glBegin(GL_QUADS);
            glNormal3f(-0.9, 0.06, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-0.3, 0.0, -0.3);
            glTexCoord2f(1.0, 0.0); glVertex3f(-0.3, 0.0, +0.3);
            glTexCoord2f(0.85, 1.5); glVertex3f(-0.2, 1.5, +0.2);
            glTexCoord2f(0.15, 1.5); glVertex3f(-0.2, 1.5, -0.2);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create S-facing side of the torch plate
// Other sides created through transformation
void renderTorchPlateSideS(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_TORCH[2]); // block plate
        glBegin(GL_QUADS);
            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-0.4, 1.5, -0.4);
            glTexCoord2f(1.0, 0.0); glVertex3f(-0.4, 1.5, +0.4);
            glTexCoord2f(1.0, 1.0); glVertex3f(-0.4, 1.6, +0.4);
            glTexCoord2f(0.0, 1.0); glVertex3f(-0.4, 1.6, -0.4);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create the lower top plate for the torch (which the fire dish is placed on)
// Higher top plate created through transformation
// "Lower" vs "higher" means parts for the plate to show visual thickness
void renderTorchPlate(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_TORCH[2]); // block plate
        glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-0.4, 1.5, -0.4); 
            glTexCoord2f(1.0, 0.0); glVertex3f(-0.4, 1.5, +0.4);
            glTexCoord2f(1.0, 1.0); glVertex3f(+0.4, 1.5, +0.4);
            glTexCoord2f(0.0, 1.0); glVertex3f(+0.4, 1.5, -0.4);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create bottom bowl of the fire dish
void renderTorchFireDishBtm(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_TORCH[4]); // fire dish bottom
        glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 1.601, -0.1);
            glTexCoord2f(1.0, 0.0); glVertex3f(-0.1, 1.601, +0.1);
            glTexCoord2f(1.0, 1.0); glVertex3f(+0.1, 1.601, +0.1);
            glTexCoord2f(0.0, 1.0); glVertex3f(+0.1, 1.601, -0.1);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create S-facing panel of the fire dish
// Other panels created through transformation
void renderTorchFireDishS(void)
{
    glNormal3f(-14.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_TORCH[3]); // fire dish siding
        glBegin(GL_QUADS);
            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f(0.1, 0.0); glVertex3f(-0.1, 1.601, -0.1);
            glTexCoord2f(0.9, 0.0); glVertex3f(-0.1, 1.601, +0.1);
            glTexCoord2f(0.9, 1.0); glVertex3f(-0.2, 1.75, +0.2);
            glTexCoord2f(0.0, 1.0); glVertex3f(-0.2, 1.75, -0.2);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create an entire, single flame torch structure
// Multiples can be replicated through renderAllTorches() below
void renderTorch(void)
{   
    renderTorchSideS();
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        renderTorchSideS();
        glRotatef(90, 0, 1, 0);
        renderTorchSideS();
        glRotatef(90, 0, 1, 0);
        renderTorchSideS();
    glPopMatrix();
    
    renderTorchPlate();
    glPushMatrix();
        glTranslatef(0.0, 0.1, 0.0); // because we can't have a 0-width plate
        renderTorchPlate();
    glPopMatrix();
    
    renderTorchPlateSideS();
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        renderTorchPlateSideS();
        glRotatef(90, 0, 1, 0);
        renderTorchPlateSideS();
        glRotatef(90, 0, 1, 0);
        renderTorchPlateSideS();
    glPopMatrix();
    
    
    renderTorchFireDishBtm();
    renderTorchFireDishS();
    glPushMatrix();
        glRotatef(90, 0, 1, 0);
        renderTorchFireDishS();
        glRotatef(90, 0, 1, 0);
        renderTorchFireDishS();
        glRotatef(90, 0, 1, 0);
        renderTorchFireDishS();
    glPopMatrix();
    
    glBegin(GL_QUADS);
        glVertex3f(-0.3, 0.0, -0.3); glVertex3f(-0.3, 0.0, +0.3); // bottom
        glVertex3f(+0.3, 0.0, +0.3); glVertex3f(+0.3, 0.0, -0.3);
    glEnd();
    
    renderFlame();
}

void renderFlame(void)
{
    float orange[] = {1, 0.647, 0, 1};
    float emission[]  = {0.0, 0.0, 0.01*EMISSION, 1.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, SHINE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_TORCH[5]); // flame
        glBegin(GL_QUADS);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.1, 1.65, -0.1); // bottom
            glTexCoord2f(1.00, 0.00); glVertex3f(-0.1, 1.65, +0.1);
            glTexCoord2f(1.00, 1.00); glVertex3f(+0.1, 1.65, +0.1);
            glTexCoord2f(0.00, 1.00); glVertex3f(+0.1, 1.65, -0.1);
        glEnd();
        glBegin(GL_TRIANGLES);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.1, 1.65, -0.1); // S side
            glTexCoord2f(1.00, 0.00); glVertex3f(-0.1, 1.65, +0.1);
            glTexCoord2f(1.00, 0.40); glVertex3f(+0.0, 2.05, +0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.1, 1.65, +0.1); // E side
            glTexCoord2f(1.00, 0.00); glVertex3f(+0.1, 1.65, +0.1);
            glTexCoord2f(1.00, 0.40); glVertex3f(+0.0, 2.05, +0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.1, 1.65, +0.1); // N side
            glTexCoord2f(1.00, 0.00); glVertex3f(+0.1, 1.65, -0.1);
            glTexCoord2f(1.00, 0.40); glVertex3f(+0.0, 2.05, +0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.1, 1.65, +0.1); // W side
            glTexCoord2f(1.00, 0.00); glVertex3f(-0.1, 1.65, -0.1);
            glTexCoord2f(1.00, 0.40); glVertex3f(+0.0, 2.05, +0.0);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create multiple flame torches (as many as desired)
void renderAllTorches(void)
{
    glPushMatrix();
        glTranslatef(+3.0, 0.0001, -4.0);
        renderTorch();
        glTranslatef(0.0, 0.0, +8.0);
        renderTorch();
        glTranslatef(-6.0, 0.0, 0.0);
        renderTorch();
        glTranslatef(0.0, 0.0, -8.0);
        renderTorch();
    glPopMatrix();
}

// Create an entire single obelisk structure
// Multiples can be created through renderAllObelisks() below
void renderObelisk(void)
{
    float orange[] = {1, 0.647, 0, 1};
    glMaterialfv(GL_FRONT, GL_SHININESS, SHINE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[9]); // grey stone 1
        glBegin(GL_QUADS);
            glTexCoord2f(0.00, 0.00); glVertex3f(-1.0, 0.0, -1.0); // bottom
            glTexCoord2f(1.00, 0.00); glVertex3f(-1.0, 0.0, +1.0);
            glTexCoord2f(1.00, 1.00); glVertex3f(+1.0, 0.0, +1.0);
            glTexCoord2f(0.00, 1.00); glVertex3f(+1.0, 0.0, -1.0);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[12]); // column style 2
        glBegin(GL_QUADS);
            glNormal3f(-14.0, 1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.0, -1.0); // S side
            glTexCoord2f(2.0, 0.0); glVertex3f(-1.0, 0.0, +1.0);
            glTexCoord2f(1.5, 7.0); glVertex3f(-0.5, 7.0, +0.5);
            glTexCoord2f(0.5, 7.0); glVertex3f(-0.5, 7.0, -0.5);
            glNormal3f(0.0, 1.0, +14.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.0, +1.0); // E side
            glTexCoord2f(2.0, 0.0); glVertex3f(+1.0, 0.0, +1.0);
            glTexCoord2f(1.5, 7.0); glVertex3f(+0.5, 7.0, +0.5);
            glTexCoord2f(0.5, 7.0); glVertex3f(-0.5, 7.0, +0.5);
            glNormal3f(+14.0, 1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(+1.0, 0.0, +1.0); // N side
            glTexCoord2f(2.0, 0.0); glVertex3f(+1.0, 0.0, -1.0);
            glTexCoord2f(1.5, 7.0); glVertex3f(+0.5, 7.0, -0.5);
            glTexCoord2f(0.5, 7.0); glVertex3f(+0.5, 7.0, +0.5);
            glNormal3f(0.0, 1.0, -14.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(+1.0, 0.0, -1.0); // W side
            glTexCoord2f(2.0, 0.0); glVertex3f(-1.0, 0.0, -1.0);
            glTexCoord2f(1.5, 7.0); glVertex3f(-0.5, 7.0, -0.5);
            glTexCoord2f(0.5, 7.0); glVertex3f(+0.5, 7.0, -0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[13]); // blue triangle
        glBegin(GL_TRIANGLES);
            glNormal3f(-1.0, 0.5, 0.0);
            glTexCoord2f(0.000, 0.0); glVertex3f(-0.5, 7.0, -0.5); // S face
            glTexCoord2f(0.250, 0.0); glVertex3f(-0.5, 7.0, +0.5);
            glTexCoord2f(0.125, 1.0); glVertex3f(+0.0, 8.0, +0.0);
            glNormal3f(0.0, 0.5, 1.0);
            glTexCoord2f(0.000, 0.0); glVertex3f(-0.5, 7.0, +0.5); // E face
            glTexCoord2f(0.250, 0.0); glVertex3f(+0.5, 7.0, +0.5);
            glTexCoord2f(0.125, 1.0); glVertex3f(+0.0, 8.0, +0.0);
            glNormal3f(+1.0, 0.5, 0.0);
            glTexCoord2f(0.000, 0.0); glVertex3f(+0.5, 7.0, +0.5); // N face
            glTexCoord2f(0.250, 0.0); glVertex3f(+0.5, 7.0, -0.5);
            glTexCoord2f(0.125, 1.0); glVertex3f(+0.0, 8.0, +0.0);
            glNormal3f(0.0, 0.5, -1.0);
            glTexCoord2f(0.000, 0.0); glVertex3f(+0.5, 7.0, -0.5); // W face
            glTexCoord2f(0.250, 0.0); glVertex3f(-0.5, 7.0, -0.5);
            glTexCoord2f(0.125, 1.0); glVertex3f(+0.0, 8.0, +0.0);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create as many obelisks as desired
void renderAllObelisks(void)
{
    glPushMatrix(); // create two obelisks
        glTranslatef(10.0, 0.0, -14.0);
        renderObelisk();
        glTranslatef(0.0, 0.0, +28.0);
        renderObelisk();
    glPopMatrix();
}

// Create an entire single trapezoid-shaped building
// Multiples can be created through renderAllTrapezoidBlgs() below
void renderTrapezoidBldg(short tx)
{
    float orange[] = {1, 0.647, 0, 1};
    glMaterialfv(GL_FRONT, GL_SHININESS, SHINE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[tx]); // mural texture on facade
        glBegin(GL_QUADS);
            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f(0.18, 0.00); glVertex3f(-0.5, 0.0, -2.0);
            glTexCoord2f(0.82, 0.00); glVertex3f(-0.5, 0.0, +2.0);
            glTexCoord2f(0.75, 1.00); glVertex3f(-0.5, 3.0, +1.5);
            glTexCoord2f(0.25, 1.00); glVertex3f(-0.5, 3.0, -1.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[2]); // change texture file
        glBegin(GL_QUADS);
            glNormal3f(+1.0, 0.0, 0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.5, 0.0, -2.0); // rear
            glTexCoord2f(4.00, 0.00); glVertex3f(+0.5, 0.0, +2.0);
            glTexCoord2f(4.00, 3.00); glVertex3f(+0.5, 3.0, +1.5);
            glTexCoord2f(0.00, 3.00); glVertex3f(+0.5, 3.0, -1.5);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.5, 0.0, -2.0); // bottom
            glTexCoord2f(4.00, 0.00); glVertex3f(-0.5, 0.0, +2.0);
            glTexCoord2f(4.00, 1.00); glVertex3f(+0.5, 0.0, +2.0);
            glTexCoord2f(0.00, 1.00); glVertex3f(+0.5, 0.0, -2.0);
            glNormal3f(0.0, 1.5, 3.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.5, 0.0, +2.0); // E wall
            glTexCoord2f(1.00, 0.00); glVertex3f(+0.5, 0.0, +2.0);
            glTexCoord2f(1.00, 3.00); glVertex3f(+0.5, 3.0, +1.5);
            glTexCoord2f(0.00, 3.00); glVertex3f(-0.5, 3.0, +1.5);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.5, 3.0, -1.5); // top
            glTexCoord2f(3.00, 0.00); glVertex3f(-0.5, 3.0, +1.5);
            glTexCoord2f(3.00, 1.00); glVertex3f(+0.5, 3.0, +1.5);
            glTexCoord2f(0.00, 1.00); glVertex3f(+0.5, 3.0, -1.5);
            glNormal3f(0.0, 1.5, -3.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.5, 0.0, -2.0); // W wall
            glTexCoord2f(1.00, 0.00); glVertex3f(-0.5, 0.0, -2.0);
            glTexCoord2f(1.00, 3.00); glVertex3f(-0.5, 3.0, -1.5);
            glTexCoord2f(0.00, 3.00); glVertex3f(+0.5, 3.0, -1.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create as many trapezoid bldgs as desired
void renderAllTrapezoidBldgs(void)
{
    glPushMatrix();
        glTranslatef(10.0, 0.0, -6.0);
        glScalef(2.0, 2.0, 2.0);
        renderTrapezoidBldg(0); // building #1
        glTranslatef(0.0, 0.0, +6.0);
        renderTrapezoidBldg(1); // building #2
    glPopMatrix();
}

// Create a single "entryway" column
// Replicated via transformation for both columns
void renderEntrywayColumn(void)
{   
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[9]); // grey stone 1
        glBegin(GL_QUADS);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.25, 0.00, -2.00); // L bottom
            glTexCoord2f(2.00, 0.00); glVertex3f(-0.25, 0.00, -0.75);
            glTexCoord2f(2.00, 1.00); glVertex3f(+0.25, 0.00, -0.75);
            glTexCoord2f(0.00, 1.00); glVertex3f(+0.25, 0.00, -2.00);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[10]); // blue column
        glBegin(GL_QUADS);
            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.25, 0.00, -2.00); // L side, S wall
            glTexCoord2f(3.00, 0.00); glVertex3f(-0.25, 0.00, -0.75);
            glTexCoord2f(3.00, 4.00); glVertex3f(-0.25, 2.00, -0.75);
            glTexCoord2f(0.00, 4.00); glVertex3f(-0.25, 2.00, -2.00);
            glNormal3f(0.0, 0.0, +1.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.25, 0.00, -0.75); // L side, E wall
            glTexCoord2f(1.00, 0.00); glVertex3f(+0.25, 0.00, -0.75);
            glTexCoord2f(1.00, 4.00); glVertex3f(+0.25, 2.00, -0.75);
            glTexCoord2f(0.00, 4.00); glVertex3f(-0.25, 2.00, -0.75);
            glNormal3f(+1.0, 0.0, 0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.25, 0.00, -2.00); // L side, N wall
            glTexCoord2f(3.00, 0.00); glVertex3f(+0.25, 0.00, -0.75);
            glTexCoord2f(3.00, 4.00); glVertex3f(+0.25, 2.00, -0.75);
            glTexCoord2f(0.00, 4.00); glVertex3f(+0.25, 2.00, -2.00);
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.25, 0.00, -2.00); // L side, W wall
            glTexCoord2f(1.00, 0.00); glVertex3f(-0.25, 0.00, -2.00);
            glTexCoord2f(1.00, 4.00); glVertex3f(-0.25, 2.00, -2.00);
            glTexCoord2f(0.00, 4.00); glVertex3f(+0.25, 2.00, -2.00);
        glEnd();
    glDisable(GL_TEXTURE_2D);    
}

// Create an entire single entryway structure
void renderEntryway(void)
{
    float white[] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, SHINE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    
    renderEntrywayColumn(); // create the "left" column
    glPushMatrix(); // translate for the "right" column
        glTranslatef(0.0, 0.0, 2.75);
        renderEntrywayColumn();
    glPopMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[9]); // grey stone 1
        glBegin(GL_QUADS); // create the top piece
            glNormal3f(0.0, -1.0, 0.0);
            glTexCoord2f(00.00, 0.00); glVertex3f(-0.25, 2.00, -2.00); // sub-top
            glTexCoord2f(16.00, 0.00); glVertex3f(-0.25, 2.00, +2.00);
            glTexCoord2f(16.00, 1.00); glVertex3f(+0.25, 2.00, +2.00);
            glTexCoord2f(00.00, 1.00); glVertex3f(+0.25, 2.00, -2.00);
            glNormal3f(0.0, +1.0, 0.0);
            glTexCoord2f(00.00, 0.00); glVertex3f(-0.25, 3.10, -2.00); // top-top
            glTexCoord2f(16.00, 0.00); glVertex3f(-0.25, 3.10, +2.00);
            glTexCoord2f(16.00, 1.00); glVertex3f(+0.25, 3.10, +2.00);
            glTexCoord2f(00.00, 1.00); glVertex3f(+0.25, 3.10, -2.00);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[11]); // blue trim
        glBegin(GL_QUADS);
            glNormal3f(-1.0, 0.0, 0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.25, 2.00, -2.00); // S-top
            glTexCoord2f(4.00, 0.00); glVertex3f(-0.25, 2.00, +2.00);
            glTexCoord2f(4.00, 1.00); glVertex3f(-0.25, 3.10, +2.00);
            glTexCoord2f(0.00, 1.00); glVertex3f(-0.25, 3.10, -2.00);
            glNormal3f(0.0, 0.0, +1.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(-0.25, 2.00, +2.00); // E-top
            glTexCoord2f(0.50, 0.00); glVertex3f(+0.25, 2.00, +2.00);
            glTexCoord2f(0.50, 1.00); glVertex3f(+0.25, 3.10, +2.00);
            glTexCoord2f(0.00, 1.00); glVertex3f(-0.25, 3.10, +2.00);
            glNormal3f(+1.0, 0.0, 0.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.25, 2.00, +2.00); // N-top
            glTexCoord2f(4.00, 0.00); glVertex3f(+0.25, 2.00, -2.00);
            glTexCoord2f(4.00, 1.00); glVertex3f(+0.25, 3.10, -2.00);
            glTexCoord2f(0.00, 1.00); glVertex3f(+0.25, 3.10, +2.00);
            glNormal3f(0.0, 0.0, -1.0);
            glTexCoord2f(0.00, 0.00); glVertex3f(+0.25, 2.00, -2.00); // W-top
            glTexCoord2f(0.50, 0.00); glVertex3f(-0.25, 2.00, -2.00);
            glTexCoord2f(0.50, 1.00); glVertex3f(-0.25, 3.10, -2.00);
            glTexCoord2f(0.00, 1.00); glVertex3f(+0.25, 3.10, -2.00);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create all desired entryways
void renderAllEntryways(void)
{
    glPushMatrix(); // create one entryway
        glTranslatef(-14.0, 0.0, 0);
        renderEntryway();
    glPopMatrix();
}

// Create the outer part of a wall (for depth to the wall)
// Inner segment created through transformation
void renderOuterWall(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[3]);
        glBegin(GL_QUADS);
            glTexCoord2f(00.0, 00.0); glVertex3f(-DIM, 0.0, -DIM+0.5); // S wall outer
            glTexCoord2f(40.0, 00.0); glVertex3f(-DIM, 0.0, +DIM-0.5);
            glTexCoord2f(40.0, 02.0); glVertex3f(-DIM, 2.0, +DIM-0.5);
            glTexCoord2f(00.0, 02.0); glVertex3f(-DIM, 2.0, -DIM+0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create the left segment of a wall
// Right segment created through transformation
void renderWallLeftSide(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[4]);
        glBegin(GL_QUADS);
            glTexCoord2f(00.0, 00.0); glVertex3f(-DIM+0.5, 0.0, -DIM+0.5);
            glTexCoord2f(00.5, 00.0); glVertex3f(-DIM,     0.0, -DIM+0.5);
            glTexCoord2f(00.5, 04.0); glVertex3f(-DIM,     2.0, -DIM+0.5);
            glTexCoord2f(00.0, 04.0); glVertex3f(-DIM+0.5, 2.0, -DIM+0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create the bottom segment of a wall
// Top segment created through transformation
void renderWallBottom(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[4]);
        glBegin(GL_QUADS);
            glTexCoord2f(00.0, 00.0); glVertex3f(-DIM,     0.0, -DIM+0.5);
            glTexCoord2f(40.0, 00.0); glVertex3f(-DIM,     0.0, +DIM-0.5);
            glTexCoord2f(40.0, 01.0); glVertex3f(-DIM+0.5, 0.0, +DIM-0.5);
            glTexCoord2f(00.0, 01.0); glVertex3f(-DIM+0.5, 0.0, -DIM+0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create an entire single S-facing wall section
// Other directions created via transformation
void renderOneWall(void)
{
    glPushMatrix();
        renderOuterWall();
        glTranslatef(0.5, 0.0, 0.0);
        renderOuterWall();
    glPopMatrix();
    glPushMatrix();
        renderWallLeftSide();
        glTranslatef(0.0, 0.0, (DIM-0.5)*2.0);
        renderWallLeftSide();
    glPopMatrix();
    glPushMatrix();
        renderWallBottom();
        glTranslatef(0.0, 2.0, 0.0);
        renderWallBottom();
    glPopMatrix();
}

// Create all 4 walls to define the "arena", via transformation
void renderAreaWalls(void)
{
    glPushMatrix();
        renderOneWall();
            glRotatef(90, 0.0, 1.0, 0.0);
            renderOneWall();
            glRotatef(90, 0.0, 1.0, 0.0);
            renderOneWall();
            glRotatef(90, 0.0, 1.0, 0.0);
            renderOneWall();
    glPopMatrix();
}

// Create a pyramid
void renderPyramid(void)
{
    float orange[] = {1, 0.647, 0, 1};
    glMaterialfv(GL_FRONT, GL_SHININESS, SHINE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange);
   
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_WALLS[3]);
    glBegin(GL_TRIANGLES); // 4 sides
    glNormal3f(0.0, 3.0, 8.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-3.0, 0.0, 3.0); // E side
    glTexCoord2f(4.0, 0.0); glVertex3f(+3.0, 0.0, 3.0);
    glTexCoord2f(2.0, 12.0); glVertex3f(+0.0, 8.0, 0.0);
    glNormal3f(8.0, 3.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(3.0, 0.0, +3.0); // N side
    glTexCoord2f(4.0, 0.0); glVertex3f(3.0, 0.0, -3.0);
    glTexCoord2f(2.0, 12.0); glVertex3f(0.0, 8.0, +0.0);
    glNormal3f(0.0, 3.0, -8.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(+3.0, 0.0, -3.0); // W side
    glTexCoord2f(4.0, 0.0); glVertex3f(-3.0, 0.0, -3.0);
    glTexCoord2f(2.0, 12.0); glVertex3f(+0.0, 8.0, +0.0);
    glNormal3f(-8.0, 3.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-3.0, 0.0, -3.0); // S side
    glTexCoord2f(4.0, 0.0); glVertex3f(-3.0, 0.0, +3.0);
    glTexCoord2f(2.0, 12.0); glVertex3f(+0.0, 8.0, +0.0);
    glEnd();
    glBegin(GL_QUADS); // bottom
    glTexCoord2f(0.0, 0.0); glVertex3f(-3.0, 0.0001, -3.0);
    glTexCoord2f(2.0, 0.0); glVertex3f(-3.0, 0.0001, +3.0);
    glTexCoord2f(2.0, 2.0); glVertex3f(+3.0, 0.0001, +3.0);
    glTexCoord2f(2.0, 0.0); glVertex3f(+3.0, 0.0001, -3.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create the ground
void renderGround(void)
{
    float orange[] = {1, 0.647, 0, 1};
    glMaterialfv(GL_FRONT, GL_SHININESS, SHINE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TX_GROUND[0]);
        glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(00.0, 00.0); glVertex3f(-DIM, 0.0, -DIM+0.5);
            glTexCoord2f(10.0, 00.0); glVertex3f(-DIM, 0.0, +DIM-0.5);
            glTexCoord2f(10.0, 03.0); glVertex3f(-4.0, 0.0, +DIM-0.5);
            glTexCoord2f(00.0, 03.0); glVertex3f(-4.0, 0.0, -DIM+0.5);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(00.00, 00.00); glVertex3f(-4.0, 0.0, -DIM+0.5);
            glTexCoord2f(03.72, 00.00); glVertex3f(-4.0, 0.0, -5.0);
            glTexCoord2f(03.72, 01.50); glVertex3f(+4.0, 0.0, -5.0);
            glTexCoord2f(00.00, 01.50); glVertex3f(+4.0, 0.0, -DIM+0.5);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(00.0, 00.0); glVertex3f(+4.0, 0.0, -DIM+0.5);
            glTexCoord2f(10.0, 00.0); glVertex3f(+4.0, 0.0, +DIM-0.5);
            glTexCoord2f(10.0, 03.0); glVertex3f(+DIM, 0.0, +DIM-0.5);
            glTexCoord2f(00.0, 03.0); glVertex3f(+DIM, 0.0, -DIM+0.5);
        glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_GROUND[1]);
        glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(00.00, 00.00); glVertex3f(-4.0, 0.0, +4.88);
            glTexCoord2f(03.75, 00.00); glVertex3f(-4.0, 0.0, +DIM-0.5);
            glTexCoord2f(03.75, 01.50); glVertex3f(+4.0, 0.0, +DIM-0.5);
            glTexCoord2f(00.00, 01.50); glVertex3f(+4.0, 0.0, +4.88);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create a skybox
void renderSkybox(void)
{
    float D = 3.0 * DIM;
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TX_SKY[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.00, 0); glVertex3f(-D, -D, -D);
			glTexCoord2f(0.25, 0); glVertex3f(+D, -D, -D);
			glTexCoord2f(0.25, 1); glVertex3f(+D, +D, -D);
			glTexCoord2f(0.00, 1); glVertex3f(-D, +D, -D);
			glTexCoord2f(0.25, 0); glVertex3f(+D, -D, -D);
			glTexCoord2f(0.50, 0); glVertex3f(+D, -D, +D);
			glTexCoord2f(0.50, 1); glVertex3f(+D, +D, +D);
			glTexCoord2f(0.25, 1); glVertex3f(+D, +D, -D);
			glTexCoord2f(0.50, 0); glVertex3f(+D, -D, +D);
			glTexCoord2f(0.75, 0); glVertex3f(-D, -D, +D);
			glTexCoord2f(0.75, 1); glVertex3f(-D, +D, +D);
			glTexCoord2f(0.50, 1); glVertex3f(+D, +D, +D);
			glTexCoord2f(0.75, 0); glVertex3f(-D, -D, +D);
			glTexCoord2f(1.00, 0); glVertex3f(-D, -D, -D);
			glTexCoord2f(1.00, 1); glVertex3f(-D, +D, -D);
			glTexCoord2f(0.75, 1); glVertex3f(-D, +D, +D);
		glEnd();
    glBindTexture(GL_TEXTURE_2D, TX_SKY[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0); glVertex3f(+D, +D, -D);
			glTexCoord2f(0.5, 0); glVertex3f(+D, +D, +D);
			glTexCoord2f(0.5, 1); glVertex3f(-D, +D, +D);
			glTexCoord2f(0.0, 1); glVertex3f(-D, +D, -D);
			glTexCoord2f(1.0, 1); glVertex3f(-D, -D, +D);
			glTexCoord2f(0.5, 1); glVertex3f(+D, -D, +D);
			glTexCoord2f(0.5, 0); glVertex3f(+D, -D, -D);
			glTexCoord2f(1.0, 0); glVertex3f(-D, -D, -D);
		glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Create the coordinate axes & label them
void renderAxes(void)
{
	const double len = 15;
	glColor3f(1, 1, 1);
	if (AXES)
	{
		glBegin(GL_LINES);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(len, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, len, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, len);
		glEnd();
		glRasterPos3d(len, 0.0, 0.0); // labels
		Print("X");
		glRasterPos3d(0.0, len, 0.0);
		Print("Y");
		glRasterPos3d(0.0, 0.0, len);
		Print("Z");
	}
}
