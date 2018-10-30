/*************************************************************************************/

// Najprostszy program wykorzystuj�cy funkcje biblioteki OpenGL

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <ctime>

//--------------------------------------------------------------------//
//-------------ZMIENNE GLOBALNE DLA ZBIORU MANDELBROT'A---------------//

const int zoom = 70;
//zmienna okreslajaca przyblizenie obrazu

const int N = 255;
//zmienna okreslajaca maksymalna ilosc iteracji

const float krok = 0.001;
//zmienna okreslajaca dokladnosc obrazu



//----------------------------------------------------------------------//
//----------ZMIENNE GLOBALNE DLA DYWANU SIERPINSKIEGO-------------------//

const float x = -50.0;
const float y = 50.0;
//wspolrzedne wierzcholka startowego

const int maxLevel = 3;
//maksymalny poziom dywanu

const float starterDistortion = 70.0;
//startowe znieksztalcenie

const float starterSideLength = 100.0;
//startowa dlugosc boku kwadratu

/*************************************************************************************/

// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)

void DrawCarpet(float x, float y, float sideLength, int level, float distortion)
{
	if (level > maxLevel)
	{
		//--------------LOSOWANIE ZNIEKSZTALCENIA----------------------//
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
		//-------------LOSOWANIE ZNIEKSZTALCENIA--------------------//



		glBegin(GL_POLYGON);
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);	//ustawienie losowego koloru dla wierzcholka
		glVertex2f(x, y);							//ustawienie odpowiednich wpolrzednych dla wierzcholka
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);	//ustawienie losowego koloru dla wierzcholka
		glVertex2f(x, y - sideLength);				//ustawienie odpowiednich wpolrzednych dla wierzcholka
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);	//ustawienie losowego koloru dla wierzcholka
		glVertex2f(x + sideLength, y - sideLength);	//ustawienie odpowiednich wpolrzednych dla wierzcholka
		glColor3f((rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1, (rand() % 89 / 100.0) + 0.1);	//ustawienie losowego koloru dla wierzcholka
		glVertex2f(x + sideLength, y);				//ustawienie odpowiednich wpolrzednych dla wierzcholka
		glEnd();
	}
	else
	{
		sideLength = sideLength / 3.0;
		//ustawienie odpowiedniej dlugosci boku

		distortion = distortion / 9.0;
		//ustawienie odpowiedniego znieksztalcenia

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

int iteracje(float x, float y, float rzecz, float uroj)
{
	float temp;
	//zmienna, ktora przechowuje wartosc x, zeby mozna bylo obliczyc y

	for (int i = 0; i <= N; i++)	//petla wykona sie tyle razy ile wynosi dokladnosc
	{
		temp = x;					//przypisanie wartosci x do zmiennej temp
		x = ((x*x - y*y) + rzecz);	//obliczenie wartosci x ze wzoru na potegowanie liczb zespolonych
		y = ((2 * y*temp) + uroj);	//obliczenie wartosci y ze wzoru na potegowanie liczb zespolonych
		if (sqrt(x*x + y*y) > 4)	//sprawdzenie czy punkt o wspolrzednych x i y jest zbiezny - czyli sprawdzanie czy modul liczby zespolonej = (x + yi) jest <= 2
			return i;				// zwracana jest ilosc iteracji		
	}
	temp = x;					//przypisanie wartosci x do zmiennej temp
	x = (x*x - y*y + rzecz);	//obliczenie wartosci x ze wzoru na potegowanie liczb zespolonych
	y = ((2 * y*temp) + uroj);	//obliczenie wartosci y ze wzoru na potegowanie liczb zespolonych
	if (sqrt(x*x + y*y) > 4)	//sprawdzenie czy punkt o wspolrzednych x i y jest zbiezny - czyli sprawdzanie czy modul liczby zespolonej = (x + yi) jest <= 2
		return N + 1;			// zwracana jest ilosc iteracji		
	else
		return N + 2;			//zwracana jest ilosc iteracji, ktora poinformuje program, zeby uzyc koloru czarnego do pomalowania piksela
}

void DrawFractal()
{
	for (float i = -2.5; i < 1; i += krok)
		for (float j = -1.5; j < 1.5; j += krok)	//(i,j) symbolizuje piksel - dla kazdego z osobna jest wiec sprawdzana zbieznosc
		{
			int	iter = iteracje(0, 0, i, j);		//sprawdzenie poziomu zbieznosci dla liczby zespolonej = (i, jI)
			if (iter != ( N + 2))					//na podstawie liczby iteracji dobierany jest kolor punktu
			{
				float color = float((float)iter / N) + 0.05;	//obliczanie koloru punktu na podstawie liczby iteracji
				float color2 = float((float)iter / (2*N)) + 0.05;	//obliczanie koloru punktu na podstawie liczby iteracji
				glBegin(GL_POINTS);					//start rysowania punktu
				glColor3f(color2, 0.0f, color);		//ustawienie koloru punktu
				glVertex2f(i * zoom, j * zoom);		//narysowanie punktu w odpowiednich wspolrzednych pomnozonych przez zoom - czyli przyblizenie
				glEnd();							//koniec funkcji rysowania
			}
			else if (iter == N + 2)					//jesli ilosc iteracji byla rowna maksymalnej, to malujemy piksel na czarno
			{
				glBegin(GL_POINTS);					//start rysowania punktu
				glColor3f(0.0f, 0.0f, 0.0f);		//ustawienie koloru punktu
				glVertex2f(i * zoom, j * zoom);		//narysowanie punktu w odpowiednich wspolrzednych pomnozonych przez zoom - czyli przyblizenie
				glEnd();							//koniec funkcji rysowania
			}
		}
}


int mandelbrot(float x, float y, float c_re, float c_im)
{
	int iterations = 0;
	while (x*x + y * y <= 4 && iterations < 50)
	{
		float x_new = x * x - y * y + c_re;
		y = 2 * x*y + c_im;
		x = x_new;
		iterations++;
	}
	if (iterations < 50) return 255;
	else return 0;
}

void draw()
{
	float x_min = -2.0;
	float x_max = 1.1;
	float y_max = 1.1;
	float y_min = -1.25;

	for (float i = x_min; i < x_max; i += 0.0025)
	{
		for (float j = y_min; j < y_max; j += 0.0025)
		{
			float value = mandelbrot(0, 0, i, j);
			if (value == 0)
			{
				glBegin(GL_POINTS);
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(i*50, j*50);
				glEnd();
			}
			else
			{
				glBegin(GL_POINTS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2f(i*50, j*50);
				glEnd();
			}
		}
	}
}



void RenderScene(void)

{

	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym


//	DrawCarpet(x, y, starterSideLength, 0, starterDistortion);
	//Funkcja rysuj�ca dywan Sierpinskiego

//	DrawFractal();
	//Funkcja rysuj�ca zbi�r Mandelbrot'a

	draw();

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania

}


/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)

{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
