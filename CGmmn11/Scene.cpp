#include "Scene.h"
#define PI 3.14159265f
#define GRASS_HEIGHT 0.4f
#define GRADIANT_INTERVAL 0.001f
#define AMOUNT_OF_STARS 110
#define AMOUNT_OF_TREES 60
#define AMOUNT_OF_HOUSES 4
#define MOON_RADIUS 0.05f
#define MY_NAME "Netanel Cohen Gindi"
#define MY_HEADER "Beautiful Night"

int scale_x_start = -960;
int scale_x_end = 960;
int scale_y_start = -540;
int scale_y_end = 540;

int scale_y = 0;
int scale_x = 800;
int AspectRatioNumerator;
int AspectRatioDenominator;
int currentWindowWidth;
int currentWindowHeight;
int CurrentSceneWidth = 1920;
int CurrentSceneHeight = 1080;
int MyParabFunc = 1;

double eq_a = 0.001;
double eq_b = 14;
double x_limit = 300;

//Draws the background: grass and sky
void DrawBackgound()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(scale_x_start, scale_y_start, scale_x_end, scale_y_end);
	glColor3f(0.0f, 0.0f, 0.0f);

	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glVertex2f(scale_x_start, 0.0f);
	glVertex2f(scale_x_end, 0.0f);
	glVertex2f(0.0f, scale_y_start);
	glVertex2f(0.0f, scale_y_end);

	glEnd();

}
void RescaleXY(int new_scale_x, int new_scale_y)
{
	if (new_scale_x != scale_x || new_scale_y != scale_y)
	{
		scale_x = new_scale_x;
		scale_y = new_scale_y;
		glutPostRedisplay();
	}
}




/// <summary>
/// 
/// </summary>
/// <param name="eq_a">the 'a' parameter of the ax^2+b parabula,assuming this isnt 0</param>
/// <param name="eq_b">the 'b' parameter of the ax^2+b parabula</param>
/// <param name="x_range">range for the positive x and also symetricly for negatives</param>
void DrawParabulaAlgoMMN(double eq_a = 0.01, double eq_b = 1.00f, double x_range = 300)
{
	if (eq_a == 0)
	{
		//Draw line
		return;
	}

	int a_sign = 1;
	if (eq_a < 0)//Keep sign positive for calculations
	{
		a_sign *= -1.0f;
		eq_a *= -1.0f;
	}

	glColor3f(1.0f, 0.0f, 0.0f);//write in red
	glPointSize(3);
	glBegin(GL_POINTS);

	double x_mid_point = 0.5f;
	double pk = 0.0f;
	double curr_x = 0.0;
	double curr_y = 0.5f;

	//glVertex2d(0.0, eq_b+0.5);
	while (curr_x <= x_range && curr_x <= currentWindowWidth && curr_y <= (currentWindowHeight))
	{
		if (((curr_x + x_mid_point) * (curr_x + x_mid_point) * eq_a) <= (curr_y + x_mid_point))
		{
			//Advance North
			curr_x += 1.0f;
		}
		else {
			if (abs((((curr_x + x_mid_point) * (curr_x + x_mid_point) * eq_a)) - (curr_y + x_mid_point)) <= 0.0001)
			{
				//Advance NE
				curr_x += 1.0f;
				curr_y += 1.0f;
			}
			else
			{
				//Advance E
				curr_y += 1.0f;
			}
		}

		double pix_center_x = curr_x - 0.5;
		double pix_center_y = a_sign * (curr_y - 0.5) + eq_b;
		glVertex2d(pix_center_x, pix_center_y);
		glVertex2d(-1.0 * pix_center_x, pix_center_y);//Mirror on y axis
	}

	glEnd();
}

/// <summary>
/// my final algo and it works!
/// </summary>
/// <param name="eq_a"></param>
/// <param name="eq_b"></param>
/// <param name="x_range"></param>
void DrawParabFinal(double eq_a = 0.01, double eq_b = 1.00f, double x_range = 300)
{
	if (eq_a == 0)
	{
		//Draw line
		return;
	}

	int a_sign = 1;
	if (eq_a < 0)//Keep sign positive for calculations
	{
		a_sign *= -1.0f;
		eq_a *= -1.0f;
	}
	
	glColor3f(0.0f, 0.0f, 1.0f);//write in blue
	glBegin(GL_POINTS);

	//start Algorithm
	float SwitchPoint = 1.0f / (2.0f * eq_a);//find switch point of when m goes from m<=1 to m>1

	float pk;
	if (a_sign > 0)
	{
		pk = eq_a - 0.5f;
	}
	else
	{
		pk = eq_a + 0.5f;
	}

	float curr_x = 0.0;
	double curr_y = eq_b;

	while (curr_x <= SwitchPoint && curr_x <= x_range)
	{
		if (a_sign > 0 && pk >= 0)
		{
			pk--;//Yk-1-Y vk=-1
			curr_y++;
		}
		else if (a_sign < 0 && pk <= 0)
		{
			pk++;//Yk-1-Y vk=-1
			curr_y--;
		}

		pk += a_sign * eq_a * (2.0f * curr_x + 3);
		curr_x++;

		glVertex2f(curr_x, curr_y);
		glVertex2f(curr_x * -1, curr_y);
	}

	pk = curr_y - (a_sign * eq_a * (curr_x + 0.5f) * (curr_x + 0.5f) + eq_b);

	while (curr_x <= x_range)
	{
		if (a_sign > 0 && pk > 0)
		{
			curr_x++;
			pk += -2.0f * eq_a * (curr_x + 1);
		}
		else if (a_sign < 0 && pk < 0)
		{
			curr_x++;
			pk += -2.0f * a_sign * eq_a * (curr_x + 1);
		}

		if (a_sign > 0)
		{
			curr_y++;
			pk++;
		}
		else
		{
			curr_y--;
			pk--;
		}
		glVertex2f(curr_x, (curr_y));
		glVertex2f(curr_x * -1, (curr_y));
	}
	glEnd();
}


/// <summary>
/// Other algo for referance
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="x_range"></param>
void PixleParabola(double a, double b, float x_range = 300)
{
	int x = 0;
	int y = b;
	float change = 1 / (2 * a);
	float incY = 2 * change; // get 1/a value
	change = abs(change); // using abs for negative a
	bool positive = (a > 0); // true if a is positve and false if not    
	float d = positive ? a - 0.5 : a + 0.5;
	glBegin(GL_POINTS);
	glVertex2i(x, y); // draw first point y(0)=b
	while (x < change && x < currentWindowWidth / 2 && abs(y) < CurrentSceneHeight / 2 && x < x_range) // while |y'(x)| < 1 go by x
	{
		if (positive && d >= 0)
		{
			d--;
			y++;
		}
		else if (!positive && d < 0)
		{
			d++;
			y--;
		}

		d += a * (2 * x + 3);
		x++;

		glVertex2i(x, y); // draw point
		glVertex2i(-x, y); // draw symetric point for negative x
	}

	d = positive ? (y + 1 - b) / a - x * (x - 2) - 0.25 : (y - 1 - b) / a - x * (x - 2) - 0.25;
	while (x < currentWindowWidth / 2 && abs(y) < currentWindowHeight / 2 && x < x_range) // go by y while in border
	{
		if (d >= 0)
		{
			d -= 2 * x + 2;
			x++;
		}
		d = positive ? d + incY : d - incY;
		y = positive ? y + 1 : y - 1;

		glVertex2i(x, y); // draw point
		glVertex2i(-x, y); // draw symetric point for negative x
	}
	glEnd();
}

void CleanupAndExit()
{
	exit(0);
}

//fixes the current aspect ratio
void FixAspectRatio()
{
	int finalW = currentWindowWidth;
	int finalH = currentWindowHeight;
	CurrentSceneWidth = currentWindowWidth;
	CurrentSceneHeight = currentWindowHeight;
	//calculate current aspect ratio
	double WinAR = (double)CurrentSceneWidth / (double)CurrentSceneHeight;
	double RefAR = (double)AspectRatioNumerator / (double)AspectRatioDenominator;

	//if window width is highr in ratio then fix it(lower it)
	if (WinAR > RefAR)
	{
		finalW = ((double)AspectRatioNumerator * (double)CurrentSceneHeight) / (double)AspectRatioDenominator;
	}
	CurrentSceneWidth = finalW;

	//if window Height is highr in ratio then fix it(lower it)
	if (WinAR < RefAR)
	{
		finalH = ((double)AspectRatioDenominator * (double)CurrentSceneWidth) / (double)AspectRatioNumerator;
	}
	CurrentSceneHeight = finalH;

	//Center view port in window
	int StartPos_X = (currentWindowWidth - finalW) / 2;
	int StartPos_Y = (currentWindowHeight - finalH) / 2;
	glViewport(StartPos_X, StartPos_Y, finalW, finalH);
}

//Redraw callback
void DisplayCallback()
{

	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(scale_x_start, scale_x_end, scale_y_start, scale_y_end);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	FixAspectRatio();

	DrawBackgound();
	switch (MyParabFunc)
	{
	case 1:
		DrawParabulaAlgoMMN(eq_a, eq_b, x_limit);
		break;
	case 2:
		PixleParabola(eq_a, eq_b, x_limit);
		break;
	case 3:
		DrawParabFinal(eq_a, eq_b, x_limit);
		break;
	case 4:
		break;

	}


	glutSwapBuffers();
}

//window resize callback
void ReshapeCallback(int w, int h)
{
	currentWindowWidth = w;
	currentWindowHeight = h;


	glutPostRedisplay();
}

//Mouse events
void MouseEventCallback(int button, int state, int x, int y)
{
	if (state == 0)
		return;
	float converted_x = ((float)x - ((float)currentWindowWidth - (float)CurrentSceneWidth) / 2) / (float)CurrentSceneWidth;
	float converted_y = 1.0f - (((float)y - ((float)currentWindowHeight - (float)CurrentSceneHeight) / 2) / (float)CurrentSceneHeight);


}

//Keybard events
void KeyboardEventCallback(unsigned char c, int x, int y)
{
	switch (c)
	{
	case '+':
		eq_b++;
		glutPostRedisplay();
		break;

	case '-':
		eq_b--;
		glutPostRedisplay();
		break;

	case '*':
		eq_a += 0.001;
		glutPostRedisplay();
		break;

	case '/':
		eq_a -= 0.001;
		glutPostRedisplay();
		break;
	case '1':
		MyParabFunc = 1;
		glutPostRedisplay();
		break;
	case '2':
		MyParabFunc = 2;
		glutPostRedisplay();
		break;
	case '3':
		MyParabFunc = 3;
		glutPostRedisplay();
		break;
	case '4':
		MyParabFunc = 4;
		glutPostRedisplay();
		break;
	case 'q':
	case 'Q':
		exit(0);
	}
}

//my initiation function
void MyInit(int argc, char** argv)
{
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 1920;
	CurrentSceneHeight = 1080;
	currentWindowWidth = CurrentSceneWidth;
	currentWindowHeight = CurrentSceneHeight;

	AspectRatioNumerator = CurrentSceneWidth;
	AspectRatioDenominator = CurrentSceneHeight;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maman11:Towers of annoying");


	//gl init stuff

}

//set system/input events
void SetEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);
	glutKeyboardFunc(KeyboardEventCallback);
}

//start play my beautiful scene
void RunScene(int argc, char** argv)
{

	MyInit(argc, argv);
	SetEvents();
	glutMainLoop();
}