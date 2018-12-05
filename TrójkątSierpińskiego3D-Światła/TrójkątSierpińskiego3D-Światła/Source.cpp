/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi  
//  uk�adu wsp�rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>
#include <iostream>
//using namespace std;
/*************************************************************************************/
typedef float point3[3];
// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych

struct Point
{
	float x;
	float y;
	float z;
};

static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k�ty obrotu

float wartosc = -0.015;
//------------ZMIENNE GLOBALNE ------------------------//

int maxLevel = 0;		//maksymalny poziom algorytmu

int spin = 0;			//okresla kierunek obrotu piramidy
int stop = 0;

static float startSideLength = 10.0; //dlugosc boku pierwszego ostroslupa

Point startPoint = { { -5.0f } ,{ -2.5f },{ -5.0f } };
//Point startPoint = { {((-N)/2.0)}, {(-sqrt(startSideLength*(startSideLength / 2.0)))} , {((-N)/2.0)}};

int model = 1;  // 1- czerwony, 2- niebieski, 3 - zielony, 4 - fioletowy



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

void RysowanieCzerwony(Point A, float sideLength)
{
	/*cout << "Punkt A = {" << A.x << " ; " << A.y << " ; " << A.z << "}" << endl;
	cout << "Punkt B = {" << A.x + sideLength << " ; " << A.y << " ; " << A.z << "}" << endl;
	cout << "Punkt C = {" << A.x + sideLength << " ; " << A.y << " ; " << A.z + sideLength << "}" << endl;
	cout << "Punkt D = {" << A.x << " ; " << A.y << " ; " << A.z + sideLength << "}" << endl;
	cout << "Punkt E = {" << A.x + (sideLength / 2.0) << " ; " << A.y + sqrt(sideLength*(sideLength / 2.0)) << " ; " << A.z + (sideLength / 2.0) << "}" << endl;
	cin.get();
	cin.get();*/
	Point wektor1 = { 0.0f, 0.0f, sideLength }, wektor2 = { sideLength, 0.0f, 0.0f };
	//Startowe wektory to AD i AB
	//wektor1 = AD, wektor2 = AB
	Point wektorNormalny;
	wektorNormalny.x = -1 * (wektor1.y*wektor2.z - wektor1.z*wektor2.y);
	wektorNormalny.y = -1 * (wektor1.z*wektor2.x - wektor1.x*wektor2.z);
	wektorNormalny.z = -1 * (wektor1.x*wektor2.y - wektor1.y*wektor2.x);
	//wektor normalny, na poczatku ustawiony na podstawe;
	float pierwiastek = sqrtf(wektorNormalny.x*wektorNormalny.x + wektorNormalny.y*wektorNormalny.y + wektorNormalny.z*wektorNormalny.z);

	wektorNormalny.x = wektorNormalny.x / pierwiastek;
	wektorNormalny.y = wektorNormalny.y / pierwiastek;
	wektorNormalny.z = wektorNormalny.z / pierwiastek;


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



	glBegin(GL_TRIANGLES);
	glColor3f(0.9f, 0.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.0f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.0f, 0.0f);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f, 0.0f, 0.0f);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
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


	/*
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-5.0, 0.0,-5.0);
	glVertex3f(5.0, 0.0, -5.0);
	glVertex3f(5.0, 0.0, 5.0);
	glVertex3f(-5.0, 0.0, 5.0);
	glVertex3f(-5.0, 0.0, -5.0);

	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-5.0, 0.0, -5.0);
	glVertex3f(0.0,5.0,0.0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.0, 0.0, -5.0);
	glVertex3f(0.0, 5.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.0, 0.0, 5.0);
	glVertex3f(0.0, 5.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-5.0, 0.0, 5.0);
	glVertex3f(0.0, 5.0, 0.0);
	glEnd();

	*/





}


void spinPyramid()
{
	if (stop)
	{
		if (spin == 0)
		{
			theta[0] += wartosc;
			if (theta[0] < -40.0)  wartosc = 0.015;
			if (theta[0] > 40.0) wartosc = -0.015;
			theta[1] -= 0.25;
		}
		else
		{
			theta[0] += wartosc;
			if (theta[0] < -40.0)  wartosc = 0.015;
			if (theta[0] > 40.0) wartosc = -0.015;
			theta[1] += 0.25;
		}
		glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
	}
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
	//	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej

	//glRotated(-30.0, 1.0, 1.0, 1.0);  // Obr�t o 60 stopni

	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);


	DrawSierpinski(startPoint, startSideLength, 0);

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania


	glutSwapBuffers();
	//
}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

	// Definicja materia�u z jakiego zrobiony jest przedmiot
	//-------------------------------------------------------
	GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	// wsp�czynniki ka =[kar,kag,kab] dla �wiat�a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wsp�czynniki kd =[kdr,kdg,kdb] �wiat�a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wsp�czynniki ks =[ksr,ksg,ksb] dla �wiat�a odbitego                

	GLfloat mat_shininess = { 100.0 };
	// wsp�czynnik n opisuj�cy po�ysk powierzchni


	// Definicja �r�d�a �wiat�a
	//-------------------------------------------------------
	GLfloat light_position[] = { -10.0, -10.0, -10.0, 1.0 };
	// po�o�enie �r�d�a

	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 0.0 };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 0.0, 1.0 };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0 };
	// sk�adowa sta�a ds dla modelu zmian o�wietlenia w funkcji 
	// odleg�o�ci od �r�d�a

	GLfloat att_linear = { 0.001f };
	// sk�adowa liniowa dl dla modelu zmian o�wietlenia w funkcji 
	// odleg�o�ci od �r�d�a

	GLfloat att_quadratic = { 0.001f };
	// sk�adowa kwadratowa dq dla modelu zmian o�wietlenia w funkcji
	// odleg�o�ci od �r�d�a

	// Ustawienie patrametr�w materia�u 
	//-------------------------------------------------------
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	// Ustawienie parametr�w �r�d�a �wiat�a
	//-------------------------------------------------------
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	// Ustawienie opcji systemu o�wietlania sceny 
	//-------------------------------------------------------
	glShadeModel(GL_SMOOTH); // w�aczenie �agodnego cieniowania
	glEnable(GL_LIGHTING);   // w�aczenie systemu o�wietlenia sceny 
	glEnable(GL_LIGHT0);     // w��czenie �r�d�a o numerze 0
	glEnable(GL_LIGHT1);     // w��czenie �r�d�a o numerze 1
	glEnable(GL_DEPTH_TEST); // w��czenie mechanizmu z-bufora 


}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych 
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s� 
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.

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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Trojkat sierpinskiego w 3-D - O�wietlony");

	glutKeyboardFunc(keys);

	glutIdleFunc(spinPyramid);

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
}

/*************************************************************************************/