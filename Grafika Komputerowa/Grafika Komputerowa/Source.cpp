/*************************************************************************************/

// Najprostszy program wykorzystuj¹cy funkcje biblioteki OpenGL

/*************************************************************************************/ 

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <ctime>


float x = -50.0;
float y = 50.0;
//wspolrzedne wierzcholka startowego

int maxLevel = 5;
//maksymalny poziom dywanu

float distortion = 10.0;
//startowe znieksztalcenie

float starterSideLength = 100.0;
//startowa dlugosc boku kwadratu

/*************************************************************************************/

// Funkcaja okreœlaj¹ca, co ma byæ rysowane 
// (zawsze wywo³ywana, gdy trzeba przerysowaæ scenê)


void Drawing(float x, float y, float sideLength, int level)
{
	if(level > maxLevel)
	{
		distortion = distortion / pow(2.0,level);
		//ustawienie odpowiedniego znieksztalcenia w zaleznosci od poziomu
	
		x += distortion;

		y += distortion;

		glBegin(GL_POLYGON);
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);
		glVertex2f(x,y);
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
		Drawing(x, y, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie w lewym gornym rogu

		Drawing(x + sideLength, y, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie u gory

		Drawing(x + 2*sideLength, y, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie w prawym gornym rogu

		Drawing(x, y - sideLength, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie z lewej

		Drawing(x + 2*sideLength, y - sideLength, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie z prawej

		Drawing(x, y - 2*sideLength, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie w lewym dolnym rogu

		Drawing(x + sideLength, y - 2*sideLength, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie na dole

		Drawing(x + 2*sideLength, y - 2*sideLength, sideLength, level + 1);
		//rysowanie kwadratu znajdujacego sie w prawym dolnym rogu
	}
}


void RenderScene(void)

{

    glClear(GL_COLOR_BUFFER_BIT); 
   // Czyszczenie okna aktualnym kolorem czyszcz¹cym

	Drawing(x, y, starterSideLength, 0);
	//Funkcja rysuj¹ca kwadrat

    glFlush();
   // Przekazanie poleceñ rysuj¹cych do wykonania

}

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania



void MyInit(void)

{

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
