/*************************************************************************************/

// Najprostszy program wykorzystuj�cy funkcje biblioteki OpenGL

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

// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)


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
   // Czyszczenie okna aktualnym kolorem czyszcz�cym

	Drawing(x, y, starterSideLength, 0);
	//Funkcja rysuj�ca kwadrat

    glFlush();
   // Przekazanie polece� rysuj�cych do wykonania

}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)

{

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
