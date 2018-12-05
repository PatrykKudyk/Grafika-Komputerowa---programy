/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi  
//  uk³adu wspó³rzêdnych dla rzutowania perspektywicznego

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>

#define M_PI  3.14159265358979323846

typedef float point3[3];

//static GLfloat theta1[] = { 0.0, 0.0, 0.0 }; // trzy k¹ty obrotu

struct Point
{
	float x;
	float y;
	float z;
};

static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k¹ty obrotu

float wartosc = -0.015;
//------------ZMIENNE GLOBALNE ------------------------//

int maxLevel = 0;		//maksymalny poziom algorytmu

int spin = 0;			//okresla kierunek obrotu piramidy
int stop = 0;

static float startSideLength = 10.0; //dlugosc boku pierwszego ostroslupa

Point startPoint = { { -5.0f } ,{ -2.5f },{ -5.0f } };
//Point startPoint = { {((-N)/2.0)}, {(-sqrt(startSideLength*(startSideLength / 2.0)))} , {((-N)/2.0)}};

float viewerCamera = 1.0;

int model = 1;  // 1- czerwony, 2- niebieski, 3 - zielony, 4 - fioletowy

static int N = 40;			//wielkosc tablicy

Point **tablica;		//dynamiczna tablica struktur punktowych

Point **kolory;			//dynamiczna tablica kolorów

GLfloat promien = 20.0;

bool kierunek = true;  //true - dodawanie, false - odejmowanie

GLfloat PHI = 0.0, THETA = 0.0;
//GLfloat cosPhi = 0.5, sinPhi = 0.5, cosTheta = 0.5, sinTheta = 0.5;

static GLfloat viewer[] = { 0.1f, 0.1f, 10.0f };
// inicjalizacja po³o¿enia obserwatora

//static GLfloat viewingPoint[] = { 0.0, 0.0, 0.0 };

//static GLfloat theta[] = { 0.0, 0.0 };   // k¹t obrotu obiektu
static GLfloat pix2angleX;     // przelicznik pikseli na stopnie
static GLfloat pix2angleY;     // przelicznik pikseli na stopnie

static GLint statusL = 0;       // stan klawiszy myszy 
								// 0 - nie naciœniêto ¿adnego klawisza
								// 1 - naciœniêty zosta³ lewy klawisz

static GLint statusP = 0;       // stan klawiszy myszy 
								// 0 - nie naciœniêto ¿adnego klawisza
								// 1 - naciœniêty zosta³ prawy klawisz

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy

static int y_pos_old = 0;       // poprzednia pozycja kursora myszy

static int delta_x = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
							   // i poprzedni¹ kursora myszy 

static int delta_y = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
							   // i poprzedni¹ kursora myszy 

							   /*************************************************************************************/

							   /*************************************************************************************/
							   // Funkcja "bada" stan myszy i ustawia wartoœci odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora 
							   // jako pozycji poprzedniej
		y_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
		statusL = 1;          // wciêniêty zosta³ lewy klawisz myszy
	}
	else
		statusL = 0;          // nie zosta³ wciêniêty ¿aden klawisz 

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		statusP = 1;          // wciêniêty zosta³ lewy klawisz myszy
		y_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
	}
	else
		statusP = 0;          // nie zosta³ wciêniêty ¿aden klawisz 

}


/*************************************************************************************/
// Funkcja "monitoruje" po³o¿enie kursora myszy i ustawia wartoœci odpowiednich 
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy

	delta_y = y - y_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy

	x_pos_old = x;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie

	y_pos_old = y;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}

/*************************************************************************************/


// Funkcja rysuj¹ca osie uk³adu wspó?rz?dnych

/*void spinTeapot()
{
theta1[0] += 0.15;
theta1[1] -= 0.25;
theta1[2] += 0.05;
glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}
*/

void DrawEggTriangle()
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			if (i <= (N - 1))
			{
				if (j <= (N - 1))
				{
					glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
					glColor3f(kolory[i + 1][j + 1].x, kolory[i + 1][j + 1].y, kolory[i + 1][j + 1].z);
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);
					glColor3f(kolory[i][j + 1].x, kolory[i][j + 1].y, kolory[i][j + 1].z);
					glVertex3f(tablica[i][j + 1].x, tablica[i][j + 1].y - 5.0f, tablica[i][j + 1].z);
					glEnd();
					glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
					glColor3f(kolory[i + 1][j].x, kolory[i + 1][j].y, kolory[i + 1][j].z);
					glVertex3f(tablica[i + 1][j].x, tablica[i + 1][j].y - 5.0f, tablica[i + 1][j].z);
					glColor3f(kolory[i + 1][j + 1].x, kolory[i + 1][j + 1].y, kolory[i + 1][j + 1].z);
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);
					glEnd();
				}
			}
			else
			{
				glBegin(GL_TRIANGLES);
				glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
				glColor3f(kolory[0][0].x, kolory[0][0].y, kolory[0][0].z);
				glVertex3f(tablica[0][0].x, tablica[0][0].y - 5.0f, tablica[0][0].z);
				glColor3f(kolory[i][0].x, kolory[i][0].y, kolory[i][0].z);
				glVertex3f(tablica[i][0].x, tablica[i][0].y - 5.0f, tablica[i][0].z);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
				glColor3f(kolory[0][j].x, kolory[0][j].y, kolory[0][j].z);
				glVertex3f(tablica[0][j].x, tablica[0][j].y - 5.0f, tablica[0][j].z);
				glColor3f(kolory[0][0].x, kolory[0][0].y, kolory[0][0].z);
				glVertex3f(tablica[0][0].x, tablica[0][0].y - 5.0f, tablica[0][0].z);
				glEnd();
			}
		}
}

void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz?tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz?tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz?tek i koniec obrazu osi y
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

Point ObliczenieWektoraNormalnego( Point wektor1, Point wektor2)
{
	Point wektorNormalny;
	wektorNormalny.x = wektor1.y*wektor2.z - wektor1.z*wektor2.y;
	wektorNormalny.y = wektor1.z*wektor2.x - wektor1.x*wektor2.z;
	wektorNormalny.z = wektor1.x*wektor2.y - wektor1.y*wektor2.x;
	//wektor normalny, na poczatku ustawiony na podstawe;
	float pierwiastek = sqrtf(wektorNormalny.x*wektorNormalny.x + wektorNormalny.y*wektorNormalny.y + wektorNormalny.z*wektorNormalny.z);

	wektorNormalny.x = wektorNormalny.x / pierwiastek;
	wektorNormalny.y = wektorNormalny.y / pierwiastek;
	wektorNormalny.z = wektorNormalny.z / pierwiastek;

	return wektorNormalny;
}
/*************************************************************************************/

void RysowanieCzerwony(Point A, float sideLength)
{

	Point wektor1 = { 0.0f, 0.0f, sideLength }, wektor2 = { sideLength, 0.0f, 0.0f };
	//Startowe wektory to AD i AB
	//wektor1 = AD, wektor2 = AB
	Point wektorNormalny = ObliczenieWektoraNormalnego(wektor1, wektor2);
	wektorNormalny.x = -1 * (wektorNormalny.x);
	wektorNormalny.y = -1 * (wektorNormalny.y);
	wektorNormalny.z = -1 * (wektorNormalny.z);
	

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x, A.y, A.z);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();

	wektor1.x = sideLength / 2.0;
	wektor1.y = sqrt(sideLength*(sideLength / 2.0));
	wektor1.z = sideLength / 2.0;
	wektor2.x = sideLength;
	wektor2.y = 0.0f;
	wektor2.z = 0.0f;
	wektorNormalny = ObliczenieWektoraNormalnego(wektor1, wektor2);

	glBegin(GL_TRIANGLES);
	glColor3f(0.9f, 0.0f, 0.0f);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x, A.y, A.z);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glEnd();

	wektor1.x = (sideLength / 2.0 - sideLength);
	wektor1.y = sqrt(sideLength*(sideLength / 2.0));
	wektor1.z = (sideLength / 2.0);
	wektor2.x = 0.0f;
	wektor2.y = 0.0f;
	wektor2.z = sideLength;
	wektorNormalny = ObliczenieWektoraNormalnego(wektor1, wektor2);

	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.0f, 0.0f);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glEnd();

	wektor1.x = sideLength / 2.0 - sideLength;
	wektor1.y = sqrt(sideLength*(sideLength / 2.0));
	wektor1.z = sideLength / 2.0 - sideLength;
	wektor2.x = -1 * sideLength;
	wektor2.y = 0.0f;
	wektor2.z = 0.0f;
	wektorNormalny = ObliczenieWektoraNormalnego(wektor1, wektor2);

	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.0f, 0.0f);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();

	wektor1.x = sideLength / 2.0;
	wektor1.y = sqrt(sideLength*(sideLength / 2.0));
	wektor1.z = sideLength / 2.0 - sideLength;
	wektor2.x = 0.0f;
	wektor2.y = 0.0f;
	wektor2.z = -1 * sideLength;
	wektorNormalny = ObliczenieWektoraNormalnego(wektor1, wektor2);

	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.0f, 0.0f);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glNormal3f(wektorNormalny.x, wektorNormalny.y, wektorNormalny.z);
	glVertex3f(A.x, A.y, A.z);
	glEnd();


	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();

}

void RysowanieZielony(Point A, float sideLength)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.9f, 0.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.8f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.7f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.6f, 0.0f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z);
	glEnd();


	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
}

void RysowanieNiebieski(Point A, float sideLength)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.9f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.8f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.7f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.6f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z);
	glEnd();


	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
}

void RysowanieFioletowy(Point A, float sideLength)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.9f, 0.0f, 0.9f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.0f, 0.8f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.0f, 0.7f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.0f, 0.6f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z);
	glEnd();


	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glEnd();
}

void DrawSierpinski(Point A, float sideLength, int level)
{
	if (level >= maxLevel)
	{
		switch (model)
		{
		case 1:
			RysowanieCzerwony(A, sideLength);
			break;
		case 2:
			RysowanieNiebieski(A, sideLength);
			break;
		case 3:
			RysowanieZielony(A, sideLength);
			break;
		case 4:
			RysowanieFioletowy(A, sideLength);
			break;
		default:
			break;
		}


	}
	else
	{
		sideLength = sideLength / 2.0;
		level += 1;
		DrawSierpinski(A, sideLength, level);
		A.x += sideLength;
		DrawSierpinski(A, sideLength, level);
		A.x -= sideLength;
		A.z += sideLength;
		DrawSierpinski(A, sideLength, level);
		A.x += sideLength;
		DrawSierpinski(A, sideLength, level);
		A.x -= sideLength;
		A.z -= sideLength;
		A.y += sqrt(sideLength*(sideLength / 2.0));
		A.x += (sideLength / 2.0);
		A.z += (sideLength / 2.0);
		DrawSierpinski(A, sideLength, level);
	}


	



}

void spinPyramid()
{
	if (stop)
	{
		if (spin == 0)
		{
			theta[0] += wartosc;
			if (theta[0] < -30.0)  wartosc = 0.015;
			if (theta[0] > 0.0) wartosc = -0.015;
			theta[1] -= 0.25;
		}
		else
		{
			theta[0] += wartosc;
			if (theta[0] < -30.0)  wartosc = 0.015;
			if (theta[0] > 0.0) wartosc = -0.015;
			theta[1] += 0.25;
		}
		glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
	}
}


// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana, gdy trzeba 
// przerysowaæ scenê)

void viewerPlacing()
{

	viewer[0] = promien*cos(THETA)*cos(PHI);
	viewer[1] = promien*sin(PHI);
	viewer[2] = promien*sin(THETA)*cos(PHI);
}

void AnglesCounting()
{

	PHI += delta_y*pix2angleY;// / 40.0;
							  //	PHI = fmod(PHI, M_PI);
	THETA += delta_x*pix2angleX;// / 40.0;
								//	THETA = fmod(THETA, M_PI);

	if (cosf(PHI) >= 0.0f)
		viewerCamera = 1.0f;
	else
		viewerCamera = -1.0f;
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie??cej

	//gluLookAt(5.0, 2.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, viewerCamera, 0.0);
	// Zdefiniowanie po³o¿enia obserwatora
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej powy¿ej


	if (statusL == 1)                     // jeœli lewy klawisz myszy wciêniêty
	{
		AnglesCounting();
	}                                  // do ró¿nicy po³o¿eñ kursora myszy

	if (statusP == 1)                     // jeœli prawy klawisz myszy wciêniêty
	{
		GLfloat temp = promien;
		if (promien >= sqrtf(startPoint.x*startPoint.x + startPoint.y*startPoint.y + startPoint.z*startPoint.z) + 1.0)
			promien += delta_y*pix2angleY;    // modyfikacja k¹ta obrotu o kat proporcjonalny
		if (promien < sqrtf(startPoint.x*startPoint.x + startPoint.y*startPoint.y + startPoint.z*startPoint.z) + 1.0)
			promien = temp;
	}

	viewerPlacing();

	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);


	DrawSierpinski(startPoint, startSideLength, 0);


	// Narysowanie czajnika
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
	glutSwapBuffers();



}
/*************************************************************************************/
// Funkcja ustalaj¹ca stan renderowania

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

	// Definicja materia³u z jakiego zrobiony jest przedmiot
	//-------------------------------------------------------
	GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego                

	GLfloat mat_shininess = { 100.0 };
	// wspó³czynnik n opisuj¹cy po³ysk powierzchni


	// Definicja Ÿród³a œwiat³a
	//-------------------------------------------------------
	GLfloat light_position[] = { 0.0, 10.0, 5.0, 1.0 };
	// po³o¿enie Ÿród³a

	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 0.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 0.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0 };
	// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_linear = { 0.001f };
	// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_quadratic = { 0.001f };
	// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	// Ustawienie patrametrów materia³u 
	//-------------------------------------------------------
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	// Ustawienie parametrów Ÿród³a œwiat³a
	//-------------------------------------------------------
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	// Ustawienie opcji systemu oœwietlania sceny 
	//-------------------------------------------------------
	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny 
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_LIGHT1);     // w³¹czenie Ÿród³a o numerze 1
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora 

}

/*************************************************************************************/
// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych 
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹ 
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.

void keys(unsigned char key, int x, int y)
{
	if (key == 'c') model = 1;
	if (key == 'n') model = 2;
	if (key == 'z') model = 3;
	if (key == 'f') model = 4;
	if (key == '+')
		if (maxLevel<5)
			++maxLevel;
	if (key == '-')
		if (maxLevel > 0)
			--maxLevel;
	if (key == 'q')
		if (spin == 0)
			spin = 1;
		else
			spin = 0;
	if (key == ' ')
		if (stop == 0)
			stop = 1;
		else
			stop = 0;


	RenderScene(); // przerysowanie obrazu sceny
}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	pix2angleX = 2 * M_PI / (float)horizontal;  // przeliczenie pikseli na stopnie
	pix2angleY = 2 * M_PI / (float)vertical;  // przeliczenie pikseli na stopnie

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej 

	gluPerspective(70, 1.0, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej 

}

/*************************************************************************************/
// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli

void main(void)
{
	srand(time(NULL));

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Trojkat sierpinskiego w 3-D z ruchomym obserwatorem");

	glutKeyboardFunc(keys);

	glutIdleFunc(spinPyramid);

	glutDisplayFunc(RenderScene);

	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bêdzie ona wywo³ywana za ka¿dym razem 
	// gdy zajdzie potrzeba przerysowania okna

	glutMouseFunc(Mouse);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie ruchu myszy

	//glutIdleFunc(spinTeapot);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// za zmiany rozmiaru okna                       


	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania niewidocznych elementów sceny

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

/*************************************************************************************/