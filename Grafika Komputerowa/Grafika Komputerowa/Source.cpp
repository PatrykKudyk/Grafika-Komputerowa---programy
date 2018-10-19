/*************************************************************************************/

// Najprostszy program wykorzystuj�cy funkcje biblioteki OpenGL

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>

const float x = -50.0;
const float y = 50.0;
//wspolrzedne wierzcholka startowego



const int zoom = 70;
const int N = 255;
const float krok = 0.0025;


const int maxLevel = 3;
//maksymalny poziom dywanu

const float starterDistortion = 70.0;
//startowe znieksztalcenie

const float starterSideLength = 100.0;
//startowa dlugosc boku kwadratu

/*************************************************************************************/

// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)
/*
void DrawCarpet(float x, float y, float sideLength, int level, float distortion)
{
	if (level > maxLevel)
	{
		int draw1 = rand() % 50;
		float draw2 = (rand() % 50) + 1;

		distortion = draw2 * distortion;

		if (draw1 % 2)
			x += distortion;
		else
			x -= distortion;

		draw1 = rand() % 50;

		if (draw1 % 2)
			y += distortion;
		else
			y -= distortion;

		glBegin(GL_POLYGON);
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);
		glVertex2f(x, y);
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);
		glVertex2f(x, y - sideLength);
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);
		glVertex2f(x + sideLength, y - sideLength);
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);
		glVertex2f(x + sideLength, y);
		glEnd();
	}
	else
	{
		sideLength = sideLength / 3.0;
		//ustawienie odpowiedniej dlugosci boku

		distortion = distortion / 9.0;

		DrawCarpet(x, y, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie w lewym gornym rogu

		DrawCarpet(x + sideLength, y, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie u gory

		DrawCarpet(x + 2 * sideLength, y, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie w prawym gornym rogu

		DrawCarpet(x, y - sideLength, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie z lewej

		DrawCarpet(x + 2 * sideLength, y - sideLength, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie z prawej

		DrawCarpet(x, y - 2 * sideLength, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie w lewym dolnym rogu

		DrawCarpet(x + sideLength, y - 2 * sideLength, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie na dole

		DrawCarpet(x + 2 * sideLength, y - 2 * sideLength, sideLength, level + 1, distortion);
		//rysowanie kwadratu znajdujacego sie w prawym dolnym rogu
	}
}

int SprawdzZbieznosc(float x, float y, float pX, float pY)
{
	int iter = 0;
	for (int i = 0; i <= N; i++)
	{
		x = (x*x - y*y + pX);
		y = ((2 * y*x) + pY);
		if (sqrt(x*x + y*y) > 4)
			break;
		iter++;
	}
//	if (iter >= 100)
		return iter;
//	else
//		return 0;
}

void DrawFractal(float x, float y, float pX, float pY, int level, int maxLevel)
{
//	if(level <= maxLevel)
//		DrawFractal(((x*x - y*y) + pX), ((2 * x*y) + pY), pX, pY, level + 1, maxLevel);
//	else
//	{
		//float color = 0.0;
		float color = 0.0 + ((float)maxLevel/ 100 );
		glBegin(GL_POINTS);
	//	if (level < N)
	//		glColor3f(color, 0.0f, 0.2f);
	//	else
	//		glColor3f(0.0f, 0.0f, 0.0f);
		glColor3f(color, 0.0f, 0.0f);
		glVertex2f(x * zoom, y * zoom);
		glEnd();
//	}
}

*/

/*void DrawFractal2(float x, float y, float pX, float pY, int level, float startX, float startY)
{
	if (level <= 100)
	{
		DrawFractal2(((x*x - y*y) + pX), ((2 * x*y) + pY), pX, pY, level + 1, startX, startY);
		if (sqrt(x*x + y*y) <= 4)
		{
			float color = 0.5;
			glBegin(GL_LINES);
			glColor3f(color, 0.0f, 0.2f);
			glVertex2f(startX * zoom, startY * zoom);
			glVertex2f(x * zoom, y * zoom);
			glEnd();
		}

	}

}
*/
int iteracje(float x, float y, float rzecz, float uroj)
{
	for (int i = 0; i <= N; i++)
	{
		x = ((x*x - y*y) + rzecz);
		y = ((2 * y*x) + uroj);
		if (sqrt(x*x + y*y) >= 4)
		{
			return i;
		}
	}
	x = (x*x - y*y + rzecz);
	y = ((2 * y*x) + uroj);
	if (sqrt(x*x + y*y) >= 4)
		return N + 1;
	else
		return N + 2;
}

void DrawFractal3()
{

	for (float i = -2; i < 1; i += krok)
		for (float j = -1.5; j < 1.5; j += krok)
		{
			int	iter = iteracje(0, 0, i, j);
			if (iter != N+2 )
			{
			//	float hue = float((float)iter / (float)(N + 2));
				float color = float((255 - (float)iter )/ 255.0);
				//if(iter > 2)
			//	std::cout << color << std::endl;
				glBegin(GL_POINTS);
				glColor3f(1.0f, color, color);
				glVertex2f(i * zoom, j * zoom);
				glEnd();
			}
			else if (iter == N + 2)
			{
				glBegin(GL_POINTS);
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(i * zoom, j * zoom);
				glEnd();
			}
		/*	else
			{
				int hue = int(255 * iter / (N + 2));
				float color = float(hue / 255);
				glBegin(GL_POINTS);
				glColor3f(color, color, 0.0f);
				glVertex2f(i * zoom, j * zoom);
				glEnd();
			}*/
		}
}


void RenderScene(void)

{

	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym


//	DrawCarpet(x, y, starterSideLength, 0, starterDistortion);
	//Funkcja rysuj�ca kwadrat

	//for (int i = -25; i <= 50; i++)
		//for (int j = -25; j <= 50; j++)
		//	DrawFractal((float)i, (float)j, 0);

//	for (float i = -2.5; i < 1; i += krok)
//		for (float j = -1; j < 1; j += krok)
//		{
//			DrawFractal(i, j, i, j, 1, SprawdzZbieznosc(0,0,i,j));
//		}

	DrawFractal3();

	//	for (float i = -5; i < 5; i += 0.005)
	//		for (float j = -5; j < 5; j += 0.005)
	//			DrawFractal2(0, 0, i, j, 0, i, j);

		//	DrawFractal(0, 0, 0);


	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania

}


/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)

{

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn�trza okna- ustawiono na lekko ja�niejszy czarny

}

/*************************************************************************************/

// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)


	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora

	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okre�lenie okna obserwatora. 
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych    

	glLoadIdentity();

}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



void main(void)

{
	srand(time(NULL));

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB



	glutCreateWindow("Dywan Sierpi�skiego z perturbacjami");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna


	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/
