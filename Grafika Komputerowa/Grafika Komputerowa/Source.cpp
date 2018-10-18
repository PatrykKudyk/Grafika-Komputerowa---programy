/*************************************************************************************/

// Najprostszy program wykorzystuj¹cy funkcje biblioteki OpenGL

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <ctime>

typedef float point[2];

const float x = -50.0;
const float y = 50.0;
//wspolrzedne wierzcholka startowego

const point p = {-0.5, 0.31};

const int maxLevel = 3;
//maksymalny poziom dywanu

const float starterDistortion = 70.0;
//startowe znieksztalcenie

const float starterSideLength = 100.0;
//startowa dlugosc boku kwadratu

/*************************************************************************************/

// Funkcaja okreœlaj¹ca, co ma byæ rysowane 
// (zawsze wywo³ywana, gdy trzeba przerysowaæ scenê)

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

void DrawFractal(float x, float y, float pX, float pY, int level)
{
	if(level <= 40)	
		DrawFractal(((x*x - y*y) + pX),( (2 * x*y) + pY), pX, pY, level + 1);
	else
	{
		if (sqrt(x*x + y*y) < 4)
			glColor3f(0.0f, 0.0f, 0.0f);
		else
			glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POINTS);
				glPointSize(0.0001);
		glVertex2f(x*50, y*50);
		glEnd();
	}
}

void RenderScene(void)

{

	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym


//	DrawCarpet(x, y, starterSideLength, 0, starterDistortion);
	//Funkcja rysuj¹ca kwadrat

	//for (int i = -25; i <= 50; i++)
		//for (int j = -25; j <= 50; j++)
		//	DrawFractal((float)i, (float)j, 0);

	for (float i = -3.0 ; i < 3.0; i += 0.005)
		for (float j = -3.0 ; j < 3.0; j += 0.005)
			DrawFractal(0,0,i,j,0);
			
//	DrawFractal(0, 0, 0);

	
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

}


/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania



void MyInit(void)

{

	glClearColor(0.5f,0.3f,0.8f,1.0f);
	// Kolor okna wnêtrza okna- ustawiono na lekko jaœniejszy czarny

}

/*************************************************************************************/

// Funkcja s³u¿¹ca do kontroli zachowania proporcji rysowanych obiektów
// niezale¿nie od rozmiarów okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokoœæ i wysokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem, gdy zmieni siê rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)


	glMatrixMode(GL_PROJECTION);
	// Okreœlenie uk³adu wspó³rzêdnych obserwatora

	glLoadIdentity();
	// Okreœlenie przestrzeni ograniczaj¹cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okreœlenie okna obserwatora. 
	// Pozwala to zachowaæ w³aœciwe proporcje rysowanego obiektu
	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okreœlenie uk³adu wspó³rzêdnych    

	glLoadIdentity();

}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli



void main(void)

{
	srand(time(NULL));

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyœwietlania
	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
	// GLUT_RGBA - model kolorów RGB



	glutCreateWindow("Dywan Sierpiñskiego z perturbacjami");
	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna


	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
	// trzeba bêdzie przerysowaæ okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst¹pieniem do renderowania


	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/
