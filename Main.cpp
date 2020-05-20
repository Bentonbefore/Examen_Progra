#include <windows.h>  
#include <GL/glut.h>  
#include <Math.h>    
#include <stdlib.h>
#define PI 3.14159265f


char title[] = "";  
int windowWidth = 640;    
int windowHeight = 480;    
int windowPosX = 50;      
int windowPosY = 50;      

GLdouble ballRadius = 0.5f;
GLdouble ballX = 0.0f;
GLdouble ballY = 0.0f;
GLdouble ballXMax, ballXMin, ballYMax, ballYMin;
GLdouble xSpeed = 0.02f;
GLdouble ySpeed = 0.007f;
int refreshMillis = 30;      

GLdouble LeftX, RightX, DownY, UpY;

bool fullScreenMode = true; 
float color_R, color_G, color_B;

void initGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	   
}

void ChangeColor()
{
	color_R = rand() / (float)RAND_MAX;
	color_G = rand() / (float)RAND_MAX;
	color_B = rand() / (float)RAND_MAX;
}




void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_MODELVIEW);    
	glLoadIdentity();             

	glTranslatef(ballX, ballY, 0.0f);  
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color_R, color_G, color_B);  
	glVertex2f(0.0f, 0.0f);       
	int numSegments = 100;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) 
	{ 
		angle = i * 2.0f * PI / numSegments; 
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	glEnd();

	glutSwapBuffers();  

	
	ballX += xSpeed;
	ballY += ySpeed;
	
	if (ballX > ballXMax)
	{
		ballX = ballXMax;
		xSpeed = -xSpeed;
		ChangeColor();
	}
	else if (ballX < ballXMin) 
	{
		ballX = ballXMin;
		xSpeed = -xSpeed;
		ChangeColor();
	}
	if (ballY > ballYMax) 
	{
		ballY = ballYMax;
		ySpeed = -ySpeed;
		ChangeColor();
	}
	else if (ballY < ballYMin)
	{
		ballY = ballYMin;
		ySpeed = -ySpeed;
		ChangeColor();
	}
}


void reshape(GLsizei width, GLsizei height) 
{
	
	if (height == 0) height = 1;                
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	
	glViewport(0, 0, width, height);

	
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();             
	if (width >= height) {
		LeftX = -1.0 * aspect;
		RightX = 1.0 * aspect;
		DownY = -1.0;
		UpY = 1.0;
	}
	else {
		LeftX = -1.0;
		RightX = 1.0;
		DownY = -1.0 / aspect;
		UpY = 1.0 / aspect;
	}
	gluOrtho2D(LeftX, RightX, DownY, UpY);
	ballXMin = LeftX + ballRadius;
	ballXMax = RightX - ballRadius;
	ballYMin = DownY + ballRadius;
	ballYMax = UpY - ballRadius;
}


void Timer(int value) {
	glutPostRedisplay();    
	glutTimerFunc(refreshMillis, Timer, 0); 
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:   
		exit(0);
		break;
	}
}


void specialKeys(int key, int x, int y) 
{
	switch (key)
	{
	case GLUT_KEY_F4:    
		fullScreenMode = !fullScreenMode;         
		if (fullScreenMode)
		{                    
			windowPosX = glutGet(GLUT_WINDOW_X);
			windowPosY = glutGet(GLUT_WINDOW_Y);
			windowWidth = glutGet(GLUT_WINDOW_WIDTH);
			windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();                     
		}
		else
		{                                        
			glutReshapeWindow(windowWidth, windowHeight);
			glutPositionWindow(windowPosX, windowPosX);  
		}
		break;
	case GLUT_KEY_RIGHT:   
		xSpeed *= 1.05f; break;
	case GLUT_KEY_LEFT:  
		xSpeed *= 0.95f; break;
	case GLUT_KEY_UP:     
		ySpeed *= 1.05f; break;
	case GLUT_KEY_DOWN:  
		ySpeed *= 0.95f; break;
	case GLUT_KEY_PAGE_UP:  //re pag
		ballRadius *= 1.05f;
		ballXMin = LeftX + ballRadius;
		ballXMax = RightX - ballRadius;
		ballYMin = DownY + ballRadius;
		ballYMax = UpY - ballRadius;
		break;
	case GLUT_KEY_PAGE_DOWN:  //av pag
		ballRadius *= 0.95f;
		ballXMin = LeftX + ballRadius;
		ballXMax = RightX - ballRadius;
		ballYMin = DownY + ballRadius;
		ballYMax = UpY - ballRadius;
		break;
	}
}


int main(int argc, char** argv) 
{
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(windowWidth, windowHeight);  
	glutInitWindowPosition(windowPosX, windowPosY); 
	glutCreateWindow(title);      
	glutDisplayFunc(display);    
	glutReshapeFunc(reshape);    
	glutTimerFunc(0, Timer, 0);  
	glutSpecialFunc(specialKeys); 
	glutKeyboardFunc(keyboard);  
	glutFullScreen();             
	initGL();                    
	glutMainLoop();              
	return 0;
}