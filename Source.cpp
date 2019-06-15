// Gl_template.c
//Wy³šczanie b³êdów przed "fopen"
#define  _CRT_SECURE_NO_WARNINGS

#define STB_IMAGE_IMPLEMENTATION

// £adowanie bibliotek:

#ifdef _MSC_VER                         // Check if MS Visual C compiler
#  pragma comment(lib, "opengl32.lib")  // Compiler-specific directive to avoid manually configuration
#  pragma comment(lib, "glu32.lib")     // Link libraries
#endif




// Ustalanie trybu tekstowego:
#ifdef _MSC_VER        // Check if MS Visual C compiler
#   ifndef _MBCS
#      define _MBCS    // Uses Multi-byte character set
#   endif
#   ifdef _UNICODE     // Not using Unicode character set
#      undef _UNICODE 
#   endif
#   ifdef UNICODE
#      undef UNICODE 
#   endif
#endif

#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>
#include "resource.h"           // About box resource identifiers.
#include "include/Lazik.h"
#include "include/Terrain.h"
#include "include/AntTweakBar.h"
#include "include/stb_image.h"


#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BITMAP_ID 0x4D42		// identyfikator formatu BMP
#define GL_PI 3.14

// Color Palette handle
HPALETTE hPalette = NULL;

// Application name and instance storeage
static LPCTSTR lpszAppName = "W³azik";
static HINSTANCE hInstance;

// Rotation amounts
static GLfloat rotAngle = 0.0f;
static GLfloat rotSpeed = 15.0f;
static GLfloat swingRadius = 0.0f;
static GLfloat rotAngleDeg = 0.0f;

static GLfloat fov = 2000.0f;
static GLsizei lastHeight;
static GLsizei lastWidth;

static GLfloat posX = 0.0f;
static GLfloat posY = 0.0f;
static GLfloat posZ = 10.0f;

static GLfloat const_velocity = 0.7f;
static GLfloat velocityL = 0.0f;
static GLfloat velocityR = 0.0f;
static GLfloat velocity = 0.0f;
static GLfloat momentumConst = 0.1*const_velocity;
bool velocityUpdate = 0;
//std::vector<GLfloat> midPointLocation{ 0.0f,0.0f,0.0f,0.0f };
std::vector<GLfloat> midPointLocation{ 0.0f,0.0f,0.0f };
std::vector<GLfloat> midPointLocationScaled{ 0,0,0 };
unsigned int tekstury[6];


Terrain mars("objects/mars.obj", 0, 0, 0);
Terrain rock("objects/rock/rock.obj", 50, -100, 4);
Terrain rock2("objects/rock2/rock2.obj", 200, 0, 15);
Terrain rock3("objects/rock3/rock3.obj", 300, -200, 35);
GLfloat *rock1BB;
GLfloat *rock2BB;
GLfloat *rock3BB;
GLfloat *roverBB;
bool collision[3] = { 0,0,0 };
bool colliding = 0;
int collisionTimer = 0;

Lazik rover(0, 0, 10);

// Opis tekstury
BITMAPINFOHEADER	bitmapInfoHeader;	// nag³ówek obrazu
unsigned char*		bitmapData;			// dane tekstury
unsigned int		texture[2];			// obiekt tekstury


// Declaration for Window procedure
LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    message,
	WPARAM  wParam,
	LPARAM  lParam);

// Dialog procedure for about box
BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam);

// Set Pixel Format function - forward declaration
void SetDCPixelFormat(HDC hDC);


// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.
void ReduceToUnit(float vector[3])
{
	float length;

	// Calculate the length of the vector		
	length = (float)sqrt((vector[0] * vector[0]) +
		(vector[1] * vector[1]) +
		(vector[2] * vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if (length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
{
	float v1[3], v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
	out[z] = v1[x] * v2[y] - v1[y] * v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
}

unsigned int LoadTexture(const char* file, GLenum textureSlot)
{
	GLuint texHandle;
	// Copy file to OpenGL
	glGenTextures(textureSlot, &texHandle);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	const auto data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, nrChannels, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		// nie udalo sie zaladowac pliku
	}
	stbi_image_free(data);
	return texHandle;
}

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;
	GLfloat fAspect;
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	lastWidth = w;
	lastHeight = h;
	TwWindowSize(w, h);

	fAspect = (GLfloat)w / (GLfloat)h;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	/*
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	*/
	// Establish perspective: 

	gluPerspective(60.0f, fAspect, 1.0, fov);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}



// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
	// Light values and coordinates
	//GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	//GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat	 lightPos[] = { 0.0f, 150.0f, 150.0f, 1.0f };
	//GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };


	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	//glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	//glEnable(GL_LIGHTING);

	// Setup and enable light 0
	//glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//glEnable(GL_LIGHT0);

	// Enable color tracking
	//glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	//glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	//glMateriali(GL_FRONT,GL_SHININESS,128);


	// White background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Black brush
	glColor3f(0.0, 0.0, 0.0);

	midPointLocation = rover.getPos();
	tekstury[0] = LoadTexture("objects/mars.png", 1);
	tekstury[1] = LoadTexture("objects/rock/rock.png", 1);
	tekstury[2] = LoadTexture("objects/rock2/rock2.png", 1);
	tekstury[3] = LoadTexture("objects/rock3/rock3.png", 1);
	tekstury[4] = LoadTexture("objects/body.png", 1);
	tekstury[5] = LoadTexture("objects/wheel.png", 1);
	tekstury[6] = LoadTexture("objects/axle.png", 1);

	rover.setSzescianTex(tekstury[4]);
	rover.setWheelTex(tekstury[5]);
	rover.setAxleTex(tekstury[6]);

	TwInit(TW_OPENGL, NULL);
	TwBar *bar;
	bar = TwNewBar("Params");

	rock1BB = rock.getBB();
	rock2BB = rock2.getBB();
	rock3BB = rock3.getBB();
	roverBB = rover.getBB();


	TwAddVarRW(bar, "velocityL", TW_TYPE_FLOAT, &velocityL, "precision=1");
	TwAddVarRW(bar, "velocityR", TW_TYPE_FLOAT, &velocityR, "precision=1");
	TwAddVarRW(bar, "velocity", TW_TYPE_FLOAT, &velocity, "precision=1");
	TwAddSeparator(bar, NULL, "");

	TwAddVarRW(bar, "x position", TW_TYPE_FLOAT, &posX, "precision=1");
	TwAddVarRW(bar, "y position", TW_TYPE_FLOAT, &posY, "precision=1");
	TwAddVarRW(bar, "rotAngle", TW_TYPE_FLOAT, &rotAngleDeg, "precision=1");
	TwAddSeparator(bar, NULL, "");

	TwAddVarRW(bar, "colliding #1", TW_TYPE_BOOLCPP, &collision[0], "");
	TwAddVarRW(bar, "colliding #2", TW_TYPE_BOOLCPP, &collision[1], "");
	TwAddVarRW(bar, "colliding #3", TW_TYPE_BOOLCPP, &collision[2], "");
	TwAddVarRW(bar, "timer", TW_TYPE_INT16, &collisionTimer, "");
	GLfloat refresh = 0.1;
	TwSetParam(bar, NULL, "refresh", TW_PARAM_FLOAT, 1, &refresh);

	int barSize[2] = { 224, 250 };
	TwSetParam(bar, NULL, "size", TW_PARAM_INT32, 2, barSize);
}


// LoadBitmapFile
// opis: ³aduje mapê bitow¹ z pliku i zwraca jej adres.
//       Wype³nia strukturê nag³ówka.
//	 Nie obs³uguje map 8-bitowych.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// wskaŸnik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag³ówek pliku
	unsigned char		*bitmapImage;			// dane obrazu
	int					imageIdx = 0;		// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// wczytuje nag³ówek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje nag³ówek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaŸnik pozycji pliku na pocz¹tku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiêæ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// sprawdza, czy uda³o siê przydzieliæ pamiêæ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// sprawdza, czy dane zosta³y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// zamienia miejscami sk³adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}
// Called to draw scene
void RenderScene(void)
{
	//float normal[3];	// Storeage for calculated surface normal
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Sposób na odróŸnienie "przedniej" i "tylniej" œciany wielok¹ta:
	//glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Save the matrix state and do the rotations

	glPushMatrix();

	//if (velocityUpdate)
//	{
	velocity = (velocityL + velocityR) / 2;
	velocityUpdate = 0;
	//}

	if (velocityL != velocityR)
	{
		if (swingRadius = rover.getAxleTrack()*(velocityL + velocityR) / (2 * (velocityL - velocityR))) // to je swing radius a nie swing angle xD
			rotAngle += atan2(swingRadius, 0) - atan2(swingRadius, velocity);
		//rotAngle = asin(velocity / swingRadius);

	}
	//else 
		//rotAngle = 0;

	posX += velocity * sin(-rotAngle); // Obliczanie nowej pozycji w osi x; X = x_0 + v*t; gdzie t = sin(-a);
	posY += velocity * cos(rotAngle);// Obliczanie nowej pozycji w osi y; Y = y_0 + v*t; gdzie t = cos(a);

	gluLookAt(
		posX, // eye X
		posY - 200, // eye Y
		posZ + 200, // eye Z
		posX, // center X
		posY, // center Y
		posZ, // center Z
		0.0,
		1.0,
		0.0
	);

	//Szescian rock1BBMax(rock1BB[0], rock1BB[1],10, rock1BB[2]- rock1BB[0], rock1BB[3]- rock1BB[1],10);
	Szescian rock1BBMax(rock1BB[0] + 50, rock1BB[1] - 100, 10, 1, 1, 100);
	//Szescian rock1BBMax(rock1BB[0], rock1BB[1], 10,1,1, 100);
	rock1BBMax.setColor(0.5, 0.5, 0.5);
	rock1BBMax.draw();

	Szescian rock1BBMin(rock1BB[2] + 50, rock1BB[3] - 100, 10, 1, 1, 100);
	//Szescian rock1BBMin(rock1BB[2], rock1BB[3], 10,1,1, 100);
	rock1BBMin.setColor(1, 0, 0);
	rock1BBMin.draw();

	Szescian rock2BBMax(rock2BB[0] + 200, rock2BB[1], 10, 1, 1, 100);
	//Szescian rock2BBMax(rock1BB[0], rock1BB[1], 10,1,1, 10);
	rock2BBMax.setColor(0.5, 0.5, 0.5);
	rock2BBMax.draw();

	Szescian rock2BBMin(rock2BB[2] + 200, rock2BB[3], 10, 1, 1, 100);
	//Szescian rock2BBMin(rock1BB[0], rock1BB[1], 10,1,1, 10);
	rock2BBMin.setColor(1, 0, 0);
	rock2BBMin.draw();
	
	Szescian rock3BBMax(rock3BB[0] + 300, rock3BB[1]-200, 10, 1, 1, 100);
	//Szescian rock3BBMax(rock1BB[0], rock1BB[1], 10,1,1, 10);
	rock3BBMax.setColor(0.5, 0.5, 0.5);
	rock3BBMax.draw();

	Szescian rock3BBMin(rock3BB[2] + 300, rock3BB[3]-200, 10, 1, 1, 100);
	//Szescian rock3BBMin(rock1BB[0], rock1BB[1], 10,1,1, 10);
	rock3BBMin.setColor(1, 0, 0);
	rock3BBMin.draw();
	
	roverBB = rover.getBB();

	roverBB[0] = posX + roverBB[0] / 2;
	roverBB[1] = posY + roverBB[1] / 2;
	roverBB[2] = posX + roverBB[2] / 2;
	roverBB[3] = posY + roverBB[3] / 2;

	//Szescian roverBBMax(posX + roverBB[0] / 2, posY + roverBB[1] / 2, 10, 1, 1, 100);
	Szescian roverBBMax(roverBB[0], roverBB[1], 10, 1, 1, 100);
	roverBBMax.setColor(0, 0, 1);
	roverBBMax.draw();

	//Szescian roverBBMin(posX+roverBB[2]/2, posY+roverBB[3]/2, 10, 1, 1, 100);
	Szescian roverBBMin(roverBB[2], roverBB[3], 10, 1, 1, 100);
	roverBBMin.setColor(0, 0, 1);
	roverBBMin.draw();

	collision[0] = !(roverBB[0] < rock1BB[2]+50 || roverBB[1] < rock1BB[3]-100 || roverBB[2] > rock1BB[0] + 50 ||  roverBB[3] > rock1BB[1]-100);
	collision[1] = !(roverBB[0] < rock2BB[2] + 200 || roverBB[1] < rock2BB[3]  || roverBB[2] > rock2BB[0] + 200 || roverBB[3] > rock2BB[1] );
	collision[2] = !(roverBB[0] < rock3BB[2] + 300 || roverBB[1] < rock3BB[3] - 200 || roverBB[2] > rock3BB[0] + 300 || roverBB[3] > rock3BB[1] - 200);
	glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glScalef(2, 2, 2);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tekstury[0]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mars.draw();
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPopMatrix();


	glPushMatrix();


	rock.setColor(0.89, 0.44, 0.1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tekstury[1]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	rock.draw();
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPopMatrix();


	glPushMatrix();


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tekstury[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	rock2.setColor(0.59, 0.27, 0.08);
	rock2.draw();
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPopMatrix();

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tekstury[3]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	rock3.setColor(0.59, 0.27, 0.08);
	rock3.draw();
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPopMatrix();

	glPushMatrix();



	glTranslatef(posX, posY, posZ); // translacja o wektory przemieszczenia obliczone wy¿ej


	/*if (velocity > 0)
	{
		if (velocity - momentumConst > 0)
			velocity -= momentumConst;
		else velocityL = velocityR = velocity = 0;
	}
	else
	{
		if (velocity + momentumConst < 0)
			velocity += momentumConst;
		else velocityL = velocityR = velocity = 0;
	}*/

	if (velocityL > 0)
	{
		if (velocityL - momentumConst > 0)
			velocityL -= momentumConst;
		else velocityL = 0;
	}
	else
	{
		if (velocityL + momentumConst < 0)
			velocityL += momentumConst;
		else velocityL = 0;
	}


	if (velocityR > 0)
	{
		if (velocityR - momentumConst > 0)
			velocityR -= momentumConst;
		else velocityR = 0;
	}
	else
	{
		if (velocityR + momentumConst < 0)
			velocityR += momentumConst;
		else velocityR = 0;
	}


	midPointLocationScaled = { midPointLocation[0] / 2,midPointLocation[1] / 2 ,midPointLocation[2] }; // trzeba podzieliæ przez 2 bo skalujemy razy 0.5 

	glTranslatef(midPointLocationScaled[0], midPointLocationScaled[1], midPointLocationScaled[2]); // powrót do pozycji wyjœciowej
	glRotatef(rotAngle * 180 / GL_PI, 0.0f, 0.0f, 1.0f); // obrót wokó³ punktu 0,0 po osi Z
	glTranslatef(-midPointLocationScaled[0], -midPointLocationScaled[1], -midPointLocationScaled[2]); // translacja do punktu 0,0

	glScalef(0.5, 0.5, 0.5);

	rover.draw();

	glPopMatrix();

	glPopMatrix();

	rotAngleDeg = abs(fmod(rotAngle * 180 / GL_PI, 360));
	TwDraw();

	if (!colliding && (collision[0] || collision[1] || collision[2]))
	{
		velocityL = -0.75*velocityL;
		velocityR = -0.75*velocityR;
		velocity = -0.75*velocity;
		colliding = 1;
		collisionTimer = 5;
	}

	if (collisionTimer)
		collisionTimer--;
	else
		colliding = 0;



	glMatrixMode(GL_MODELVIEW);

	// Flush drawing commands
	glFlush();
}


// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC)
{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
		1,                                                              // Version of this structure    
		PFD_DRAW_TO_WINDOW |                    // Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |					// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,                       // Double buffered
		PFD_TYPE_RGBA,                          // RGBA Color mode
		24,                                     // Want 24bit color 
		0,0,0,0,0,0,                            // Not used to select mode
		0,0,                                    // Not used to select mode
		0,0,0,0,0,                              // Not used to select mode
		32,                                     // Size of depth buffer
		0,                                      // Not used to select mode
		0,                                      // Not used to select mode
		PFD_MAIN_PLANE,                         // Draw in main plane
		0,                                      // Not used to select mode
		0,0,0 };                                // Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}



// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC)
{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange, GreenRange, BlueRange;
	// Range for each color entry (7,7,and 3)


// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if (!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) - 1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) - 1;

	// Loop through all the palette entries
	for (i = 0; i < nColors; i++)
	{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double)pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char)NULL;
	}


	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC, hRetPal, FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
}


// Entry point of all Windows programs
int APIENTRY WinMain(HINSTANCE       hInst,
	HINSTANCE       hPrevInstance,
	LPSTR           lpCmdLine,
	int                     nCmdShow)
{
	MSG                     msg;            // Windows message structure
	WNDCLASS        wc;                     // Windows class structure
	HWND            hWnd;           // Storeage for window handle

	hInstance = hInst;

	// Register Window style
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// No need for background brush for OpenGL window
	wc.hbrBackground = NULL;

	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = lpszAppName;

	// Register the window class
	if (RegisterClass(&wc) == 0)
		return FALSE;


	// Create the main application window
	hWnd = CreateWindow(
		lpszAppName,
		lpszAppName,

		// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,

		// Window position and size
		50, 50,
		400, 400,
		NULL,
		NULL,
		hInstance,
		NULL);

	// If window was not created, quit
	if (hWnd == NULL)
		return FALSE;


	// Display the window
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}




// Window procedure, handles all messages for this program
LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    message,
	WPARAM  wParam,
	LPARAM  lParam)
{
	static HGLRC hRC;               // Permenant Rendering context
	static HDC hDC;                 // Private GDI Device context

	switch (message)
	{
		// Window creation, setup for OpenGL
	case WM_CREATE:
		// Store the device context
		hDC = GetDC(hWnd);

		// Select the pixel format
		SetDCPixelFormat(hDC);

		// Create palette if needed
		hPalette = GetOpenGLPalette(hDC);

		// Create the rendering context and make it current
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		SetupRC();




		//gluLookAt(posX, posY, posZ, 0 + posX, 0 + posY, 0.0, 0.0, 1.0, 0.0);
		//glGenTextures(2, &texture[0]);                  // tworzy obiekt tekstury			

		// ³aduje pierwszy obraz tekstury:
		//bitmapData = LoadBitmapFile("Bitmapy\\checker.bmp", &bitmapInfoHeader);

	/*	glBindTexture(GL_TEXTURE_2D, texture[0]);       // aktywuje obiekt tekstury

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

		if (bitmapData)
			free(bitmapData);

		// ³aduje drugi obraz tekstury:
		//	bitmapData = LoadBitmapFile("Bitmapy\\crate.bmp", &bitmapInfoHeader);
		glBindTexture(GL_TEXTURE_2D, texture[1]);       // aktywuje obiekt tekstury

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// tworzy obraz tekstury
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
			bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

		if (bitmapData)
			free(bitmapData);
			*/
			// ustalenie sposobu mieszania tekstury z t³em
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		break;

		// Window is being destroyed, cleanup
	case WM_DESTROY:
		// Deselect the current rendering context and delete it
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);

		// Delete the palette if it was created
		if (hPalette != NULL)
			DeleteObject(hPalette);

		// Tell the application to terminate after the window
		// is gone.
		PostQuitMessage(0);
		break;

		// Window is resized.
	case WM_SIZE:
		// Call our function which modifies the clipping
		// volume and viewport
		ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;


		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
	case WM_PAINT:
	{
		// Call OpenGL drawing code
		RenderScene();

		SwapBuffers(hDC);

		// Validate the newly painted client area
		//ValidateRect(hWnd, NULL); // not loop
		InvalidateRect(hWnd, NULL, FALSE); // loop
	}
	break;

	// Windows is telling the application that it may modify
	// the system palette.  This message in essance asks the 
	// application for a new palette.
	case WM_QUERYNEWPALETTE:
		// If the palette was created.
		if (hPalette)
		{
			int nRet;

			// Selects the palette into the current device context
			SelectPalette(hDC, hPalette, FALSE);

			// Map entries from the currently selected palette to
			// the system palette.  The return value is the number 
			// of palette entries modified.
			nRet = RealizePalette(hDC);

			// Repaint, forces remap of palette in current window
			InvalidateRect(hWnd, NULL, FALSE);

			return nRet;
		}
		break;


		// This window may set the palette, even though it is not the 
		// currently active window.
	case WM_PALETTECHANGED:
		// Don't do anything if the palette does not exist, or if
		// this is the window that changed the palette.
		if ((hPalette != NULL) && ((HWND)wParam != hWnd))
		{
			// Select the palette into the device context
			SelectPalette(hDC, hPalette, FALSE);

			// Map entries to system palette
			RealizePalette(hDC);

			// Remap the current colors to the newly realized palette
			UpdateColors(hDC);
			return 0;
		}
		break;

		// Key press, check for arrow keys to do cube rotation.
	case WM_KEYDOWN:
	{


		/*if (wParam == 'R') // skret w prawo
		{
			posX = posY =velocityL=velocityR=velocity= 0;
		}
		if (wParam == 'W') // do przodu
		{
			velocityL += const_velocity;
			velocityUpdate = 1;
		}

		if (wParam == 'S') // do tylu
		{
			velocityL -= const_velocity;
			velocityUpdate = 1;
		}

		if (wParam == 'E') // do przodu
		{
			velocityR += const_velocity;
			velocityUpdate = 1;
		}

		if (wParam == 'D') // do tylu
		{
			velocityR -= const_velocity;
			velocityUpdate = 1;
		}*/

		if (wParam == 'W') // do przodu
		{
			velocityL += const_velocity;
			velocityR += const_velocity;
			velocityUpdate = 1;
		}

		if (wParam == 'S') // do tylu
		{
			velocityL -= const_velocity;
			velocityR -= const_velocity;
			velocityUpdate = 1;
		}

		if (wParam == 'A') // do tylu
		{
			velocityL += const_velocity;
			velocityR -= const_velocity;
			velocityUpdate = 1;
		}

		if (wParam == 'D') // do tylu
		{
			velocityR += const_velocity;
			velocityL -= const_velocity;
			velocityUpdate = 1;
		}

		if (wParam == VK_CONTROL) // w gore
		{
			posZ -= 3*const_velocity;
			velocityUpdate = 1;
		}
		if (wParam == VK_SHIFT) // w dol
		{
			posZ += 3*const_velocity;
			velocityUpdate = 1;
		}
		if (wParam == VK_SPACE)
		{
			velocityR = velocityL = 0;
			velocityUpdate = 1;
		}

		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	// A menu command
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			// Exit the program
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;

			// Display the about box
			/*case ID_HELP_ABOUT:
				DialogBox (hInstance,
					MAKEINTRESOURCE(IDD_DIALOG_ABOUT),
					hWnd,
					AboutDlgProc);
				break;*/
		}
	}
	break;


	default:   // Passes it on if unproccessed
		return (DefWindowProc(hWnd, message, wParam, lParam));

	}


	if (TwEventWin(hWnd, message, wParam, lParam)) // send event message to AntTweakBar
		return 0;
	return (0L);
}




// Dialog procedure.
BOOL APIENTRY AboutDlgProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{

	switch (message)
	{
		// Initialize the dialog box
	case WM_INITDIALOG:
	{
		int i;
		GLenum glError;

		// glGetString demo
	/*	SetDlgItemText(hDlg,IDC_OPENGL_VENDOR,glGetString(GL_VENDOR));
		SetDlgItemText(hDlg,IDC_OPENGL_RENDERER,glGetString(GL_RENDERER));
		SetDlgItemText(hDlg,IDC_OPENGL_VERSION,glGetString(GL_VERSION));
		SetDlgItemText(hDlg,IDC_OPENGL_EXTENSIONS,glGetString(GL_EXTENSIONS));

		// gluGetString demo
		SetDlgItemText(hDlg,IDC_GLU_VERSION,gluGetString(GLU_VERSION));
		SetDlgItemText(hDlg,IDC_GLU_EXTENSIONS,gluGetString(GLU_EXTENSIONS));
		*/

		// Display any recent error messages
		i = 0;
		do {
			glError = glGetError();
			/*SetDlgItemText(hDlg,IDC_ERROR1+i,gluErrorString(glError));*/
			i++;
		} while (i < 6 && glError != GL_NO_ERROR);


		return (TRUE);
	}
	break;

	// Process command messages
	case WM_COMMAND:
	{
		// Validate and Make the changes
		if (LOWORD(wParam) == IDOK)
			EndDialog(hDlg, TRUE);
	}
	break;

	// Closed from sysbox
	case WM_CLOSE:
		TwTerminate();
		EndDialog(hDlg, TRUE);
		break;
	}

	return FALSE;
}
