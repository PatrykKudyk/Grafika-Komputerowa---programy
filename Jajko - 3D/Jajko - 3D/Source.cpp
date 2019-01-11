/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi  
//  uk�adu wsp�rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>

#define M_PI  3.14159265358979323846

typedef float point3[3];

/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych

struct Point	//struktura do obs�ugi wsp�rz�dnych punkt�w
{
	float x;	//wsp�rz�dna x
	float y;	//wsp�rz�dna y
	float z;	//wsp�rz�dna z
};


//------------ZMIENNE GLOBALNE ------------------------//
static int N = 70;			//wielkosc tablicy

Point **tablica;		//dynamiczna tablica struktur punktowych

Point **kolory;			//dynamiczna tablica kolor�w

int model = 1;  // 1- punkty, 2- siatka, 3 - wype�nione tr�jk�ty

static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k�ty obrotu



void DrawEggPoints()
{
	glBegin(GL_POINTS);	//rozpocz�cie rysowania punkt�w
	glColor3f(1.0f, 1.0f, 1.0f); //ustawiam kolor punkt�w na bia�y
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z); //w podw�jnej p�tli wypisuje kolejne punkty z macierzy "tablica" przechowuj�cej wsp�rz�dne punkt�w
	glEnd();
}

void DrawEggLines()
{

	for (int i = 0; i <= N; i++)
	{
		glBegin(GL_LINE_STRIP);	//rozpocz�cie rysowania lini poziomych
		glColor3f(1.0f, 1.0f, 1.0f);	//ustawienie koloru linii na bia�y
		for (int j = 0; j <= N; j++)
			glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
		glEnd();
		
		glBegin(GL_LINE_STRIP);	//rozpocz�cie rysowania lini pionowych
		glColor3f(1.0f, 1.0f, 1.0f);	//ustawienie koloru linii na bia�y
		for (int j = 0; j <= N; j++)
			glVertex3f(tablica[j][i].x, tablica[j][i].y - 5.0f, tablica[j][i].z);
		glEnd();
		
	}
}

void DrawEggTriangle()
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			if (i <= (N - 1))	//p�tla nie uwzgl�dniaj�ca kraw�dzi macierzy, tak �eby unikn�� luki w rysowaniu
			{
				if (j <= (N - 1))
				{
					glBegin(GL_TRIANGLES);	//rozpocz�cie rysowania tr�jk�ta
					glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);	//dobranie odpowiedniego koloru
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
					glColor3f(kolory[i + 1][j + 1].x, kolory[i + 1][j + 1].y, kolory[i + 1][j + 1].z);	//dobranie odpowiedniego koloru
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
					glColor3f(kolory[i][j + 1].x, kolory[i][j + 1].y, kolory[i][j + 1].z);	//dobranie odpowiedniego koloru
					glVertex3f(tablica[i][j + 1].x, tablica[i][j + 1].y - 5.0f, tablica[i][j + 1].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
					glEnd();
					glBegin(GL_TRIANGLES);	//rozpocz�cie rysowania tr�jk�ta
					glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);	//dobranie odpowiedniego koloru
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
					glColor3f(kolory[i + 1][j].x, kolory[i + 1][j].y, kolory[i + 1][j].z);	//dobranie odpowiedniego koloru
					glVertex3f(tablica[i + 1][j].x, tablica[i + 1][j].y - 5.0f, tablica[i + 1][j].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
					glColor3f(kolory[i + 1][j + 1].x, kolory[i + 1][j + 1].y, kolory[i + 1][j + 1].z);	//dobranie odpowiedniego koloru
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
					glEnd();
				}
			}
			else
			{
				glBegin(GL_TRIANGLES);	//rozpocz�cie rysowania tr�jk�ta
				glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);	//dobranie odpowiedniego koloru
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
				glColor3f(kolory[0][0].x, kolory[0][0].y, kolory[0][0].z);	//dobranie odpowiedniego koloru
				glVertex3f(tablica[0][0].x, tablica[0][0].y - 5.0f, tablica[0][0].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
				glColor3f(kolory[i][0].x, kolory[i][0].y, kolory[i][0].z);	//dobranie odpowiedniego koloru
				glVertex3f(tablica[i][0].x, tablica[i][0].y - 5.0f, tablica[i][0].z);	//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
				glEnd();

				glBegin(GL_TRIANGLES);	//rozpocz�cie rysowania tr�jk�ta
				glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);	//dobranie odpowiedniego koloru
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
				glColor3f(kolory[0][j].x, kolory[0][j].y, kolory[0][j].z);	//dobranie odpowiedniego koloru
				glVertex3f(tablica[0][j].x, tablica[0][j].y - 5.0f, tablica[0][j].z);//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
				glColor3f(kolory[0][0].x, kolory[0][0].y, kolory[0][0].z);	//dobranie odpowiedniego koloru
				glVertex3f(tablica[0][0].x, tablica[0][0].y - 5.0f, tablica[0][0].z);//wczytanie wspo�rz�dnych punktu dla wierzcho�ka tr�jk�ta
				glEnd();
			}
		}
}

void GeneratingColors()
{
	kolory = new Point*[N + 1];	//tworzenie dynamicznej tablicy kolor�w o zadanej wielko�ci
	for (int i = 0; i <= N; i++)
		kolory[i] = new Point[N + 1];	//tworzenie dynamicznych tablic w dynamicznej tablicy (kolumny w wierszach)

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			kolory[i][j].x = (float)(rand() % 1000 / 1000.0);	//losowanie pseudolosowego koloru z zakresu (0.0 do 0.999)
			kolory[i][j].y = (float)(rand() % 1000 / 1000.0);	//losowanie pseudolosowego koloru z zakresu (0.0 do 0.999)
			kolory[i][j].z = (float)(rand() % 1000 / 1000.0);	//losowanie pseudolosowego koloru z zakresu (0.0 do 0.999)
		}
}

void Egg()
{

	tablica = new Point*[N + 1]; //tworzenie tablicy dynamicznej przy u�yciu zadeklarowanego globalnie wska�nika struktury Punkt
	for (int i = 0; i <= N; i++)
		tablica[i] = new Point[N + 1]; //w p�tli nast�puje dynamiczne tworzenie tablicy tablic 

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			float u = (float)i / (float)N; //przypisywanie u odpowiednia wartosc
			float v = (float)j / (float)N; //przypisywanie v odpowiednia wartosc
			tablica[i][j].x = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*cos((float)M_PI*v)); //obliczanie wspolrzednej x dla punktu przy wykorzystaniu podanego przez prowadzacego wzoru
			tablica[i][j].y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * u*u); //obliczanie wspolrzednej y dla punktu przy wykorzystaniu podanego przez prowadzacego wzoru
			tablica[i][j].z = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*sin((float)M_PI*v)); //obliczanie wspolrzednej z dla punktu przy wykorzystaniu podanego przez prowadzacego wzoru
		}

	switch (model) //zmienna "model" odpowiada za wyswietlanie jajka /1-punkty, 2-siatka, 3-trojkaty
	{
	case 1:
		DrawEggPoints();
		break;
	case 2:
		DrawEggLines();
		break;
	case 3:
		DrawEggTriangle();
		break;
	default:
		break;
	}
}

void spinEgg()
{
	theta[0] -= 0.25;	//obr�t wzgl�dem osi OX
	if (theta[0] > 360.0) theta[0] -= 360.0;	//je�li przekroczymy warto�� 360 stopni, to jest ustawiana zn�w na 0 

	theta[1] -= 0.25;	//obr�t wzgl�dem osi OY
	if (theta[1] > 360.0) theta[1] -= 360.0;	//je�li przekroczymy warto�� 360 stopni, to jest ustawiana zn�w na 0 

	theta[2] -= 0.25;	//obr�t wzgl�dem osi OZ
	if (theta[2] > 360.0) theta[2] -= 360.0;	//je�li przekroczymy warto�� 360 stopni, to jest ustawiana zn�w na 0 

	glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}


void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz�tek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();

}

/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba 
// przerysowa� scen�)



void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej

	glRotatef(theta[0], 1.0, 0.0, 0.0);	//obr�t jajka wzgl�dem osi OX
	glRotatef(theta[1], 0.0, 1.0, 0.0);	//obr�t jajka wzgl�dem osi OY
	glRotatef(theta[2], 0.0, 0.0, 1.0);	//obr�t jajka wzgl�dem osi OZ

	Egg();	//metoda rysuj�ca odpowiednie jajko

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania

	glutSwapBuffers();	
}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;	//w przypadku naci�ni�cia "p" jajko b�dzie rysowane jako punkty
	if (key == 'w') model = 2;	//w przypadku naci�ni�cia "w" jajko b�dzie rysowane jako siatka
	if (key == 's') model = 3;	//w przypadku naci�ni�cia "s" jajko b�dzie rysowane jako tr�jk�ty

	RenderScene(); // przerysowanie obrazu sceny
}

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych 
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s� 
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie��cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie��cej
}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



void main(void)
{
	srand(time(NULL));

	GeneratingColors();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Jajko 3-D");

	glutKeyboardFunc(keys);

	glutIdleFunc(spinEgg);

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem 
	// gdy zajdzie potrzba przeryswania okna 
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna      
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

	for (int i = 0; i < N; i++)
		delete[] tablica[i];
	delete[] tablica;

	for (int i = 0; i < N; i++)
		delete[] kolory[i];
	delete[] kolory;
}

/*************************************************************************************/