/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi  
//  uk�adu wsp�rz�dnych dla rzutowania perspektywicznego

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

#define M_PI  3.14159265358979323846

typedef float point3[3];

//static GLfloat theta1[] = { 0.0, 0.0, 0.0 }; // trzy k�ty obrotu

struct Point
{
	float x;
	float y;
	float z;
	float xu;
	float xv;
	float yu;
	float yv;
	float zu;
	float zv;
	float nx;
	float ny;
	float nz;
};

static int N = 40;			//wielkosc tablicy

Point **tablica;		//dynamiczna tablica struktur punktowych

Point **kolory;			//dynamiczna tablica kolor�w

GLfloat promien = 20.0;

float y = 1.0f;

bool kierunek = true;  //true - dodawanie, false - odejmowanie

GLfloat PHI = 0.0, THETA = 0.0;
GLfloat PHI1 = 0.0, THETA1 = 0.0, PHI2 = 0.0, THETA2 = 0.0;
//GLfloat cosPhi = 0.5, sinPhi = 0.5, cosTheta = 0.5, sinTheta = 0.5;

static GLfloat viewer[] = { 0.1, 0.1, 10.0 };

static GLfloat light1[] = { 0.0, 0.0, 10.0 , 1.0 };

static GLfloat light2[] = { 10.0, 0.1, 0.1, 1.0 };

// inicjalizacja po�o�enia obserwatora

static GLfloat theta[] = { 0.0, 0.0 };   // k�t obrotu obiektu
static GLfloat pix2angleX;     // przelicznik pikseli na stopnie
static GLfloat pix2angleY;     // przelicznik pikseli na stopnie

static GLint statusL = 0;       // stan klawiszy myszy 
								// 0 - nie naci�ni�to �adnego klawisza
								// 1 - naci�ni�ty zosta� lewy klawisz

static GLint statusP = 0;       // stan klawiszy myszy 
								// 0 - nie naci�ni�to �adnego klawisza
								// 1 - naci�ni�ty zosta� prawy klawisz

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy

static int y_pos_old = 0;       // poprzednia pozycja kursora myszy

static int delta_x = 0;        // r�nica pomi�dzy pozycj� bie��c�
							   // i poprzedni� kursora myszy 

static int delta_y = 0;        // r�nica pomi�dzy pozycj� bie��c�
							   // i poprzedni� kursora myszy 

							   /*************************************************************************************/

							   /*************************************************************************************/
							   // Funkcja "bada" stan myszy i ustawia warto�ci odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora 
							   // jako pozycji poprzedniej
		y_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
		statusL = 1;          // wci�ni�ty zosta� lewy klawisz myszy
	}
	else
		statusL = 0;          // nie zosta� wci�ni�ty �aden klawisz 

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		statusP = 1;          // wci�ni�ty zosta� lewy klawisz myszy
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora 
		y_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
	}
	else
		statusP = 0;          // nie zosta� wci�ni�ty �aden klawisz 

}


/*************************************************************************************/
// Funkcja "monitoruje" po�o�enie kursora myszy i ustawia warto�ci odpowiednich 
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy

	delta_y = y - y_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy

	x_pos_old = x;            // podstawienie bie��cego po�o�enia jako poprzednie

	y_pos_old = y;            // podstawienie bie��cego po�o�enia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}

/*************************************************************************************/


// Funkcja rysuj�ca osie uk�adu wsp�?rz?dnych

/*void spinTeapot()
{
theta1[0] += 0.15;
theta1[1] -= 0.25;
theta1[2] += 0.05;
glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
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
					//glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
					glColor3f(1.0, 1.0, 0.0);
					glNormal3f(tablica[i][j].nx, tablica[i][j].ny, tablica[i][j].nz);
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
					//glColor3f(kolory[i + 1][j + 1].x, kolory[i + 1][j + 1].y, kolory[i + 1][j + 1].z);
					glColor3f(1.0, 1.0, 0.0);
					glNormal3f(tablica[i + 1][j + 1].nx, tablica[i + 1][j + 1].ny, tablica[i + 1][j + 1].nz);
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);
					//glColor3f(kolory[i][j + 1].x, kolory[i][j + 1].y, kolory[i][j + 1].z);
					glColor3f(1.0, 1.0, 0.0);
					glNormal3f(tablica[i][j + 1].nx, tablica[i][j + 1].ny, tablica[i][j + 1].nz);
					glVertex3f(tablica[i][j + 1].x, tablica[i][j + 1].y - 5.0f, tablica[i][j + 1].z);
					glEnd();
					glBegin(GL_TRIANGLES);
					//glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
					glColor3f(1.0, 1.0, 0.0);
					glNormal3f(tablica[i][j].nx, tablica[i][j].ny, tablica[i][j].nz);
					glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
					//glColor3f(kolory[i + 1][j].x, kolory[i + 1][j].y, kolory[i + 1][j].z);
					glColor3f(1.0, 1.0, 0.0);
					glNormal3f(tablica[i + 1][j].nx, tablica[i + 1][j].ny, tablica[i + 1][j].nz);
					glVertex3f(tablica[i + 1][j].x, tablica[i + 1][j].y - 5.0f, tablica[i + 1][j].z);
					//glColor3f(kolory[i + 1][j + 1].x, kolory[i + 1][j + 1].y, kolory[i + 1][j + 1].z);
					glColor3f(1.0, 1.0, 0.0);
					glNormal3f(tablica[i + 1][j + 1].nx, tablica[i + 1][j + 1].ny, tablica[i + 1][j + 1].nz);
					glVertex3f(tablica[i + 1][j + 1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);
					glEnd();
				}
			}
			else
			{
				glBegin(GL_TRIANGLES);
				//glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
				glColor3f(1.0, 1.0, 0.0);
				glNormal3f(tablica[i][j].nx, tablica[i][j].ny, tablica[i][j].nz);
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
				//glColor3f(kolory[0][0].x, kolory[0][0].y, kolory[0][0].z);
				glColor3f(1.0, 1.0, 0.0);
				glNormal3f(tablica[0][0].nx, tablica[0][0].ny, tablica[0][0].nz);
				glVertex3f(tablica[0][0].x, tablica[0][0].y - 5.0f, tablica[0][0].z);
				//glColor3f(kolory[i][0].x, kolory[i][0].y, kolory[i][0].z);
				glColor3f(1.0, 1.0, 0.0);
				glNormal3f(tablica[i][0].nx, tablica[i][0].ny, tablica[i][0].nz);
				glVertex3f(tablica[i][0].x, tablica[i][0].y - 5.0f, tablica[i][0].z);
				glEnd();

				glBegin(GL_TRIANGLES);
				//glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
				glColor3f(1.0, 1.0, 0.0);
				glNormal3f(tablica[i][j].nx, tablica[i][j].ny, tablica[i][j].nz);
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
				//glColor3f(kolory[0][j].x, kolory[0][j].y, kolory[0][j].z);
				glColor3f(1.0, 1.0, 0.0);
				glNormal3f(tablica[0][j].nx, tablica[0][j].ny, tablica[0][j].nz);
				glVertex3f(tablica[0][j].x, tablica[0][j].y - 5.0f, tablica[0][j].z);
				//glColor3f(kolory[0][0].x, kolory[0][0].y, kolory[0][0].z);
				glColor3f(1.0, 1.0, 0.0);
				glNormal3f(tablica[0][0].nx, tablica[0][0].ny, tablica[0][0].nz);
				glVertex3f(tablica[0][0].x, tablica[0][0].y - 5.0f, tablica[0][0].z);
				glEnd();
			}
		}
}

void GeneratingColors()
{
	kolory = new Point*[N + 1];
	for (int i = 0; i <= N; i++)
		kolory[i] = new Point[N + 1];

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{

			//	else {
			kolory[i][j].x = (float)(rand() % 1000 / 1000.0);
			kolory[i][j].y = (float)(rand() % 1000 / 1000.0);
			kolory[i][j].z = (float)(rand() % 1000 / 1000.0);
			//	}
		}

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			if (j == N - 1)
			{
				kolory[i][j].x = kolory[i][0].x;
				kolory[i][j].y = kolory[i][0].y;
				kolory[i][j].z = kolory[i][0].z;
			}
		}



	/*
	for (int i = 0; i <= N; i++)
	{
	for(int j = 0 ; j <= N; j++)
	std::cout << "X = " << kolory[i][j].x << "\t";
	std::cout << std::endl;
	for (int j = 0; j <= N; j++)
	std::cout << "Y = " << kolory[i][j].y << "\t";
	std::cout << std::endl;
	for (int j = 0; j <= N; j++)
	std::cout << "Z = " << kolory[i][j].z << "\t";
	std::cout << std::endl << std::endl;
	}
	std::cin.get();
	std::cin.get();*/
	tablica = new Point*[N + 1];
	for (int i = 0; i <= N; i++)
		tablica[i] = new Point[N + 1];

}

void Egg()
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			float u = (float)i / (float)N;
			float v = (float)j / (float)N;
			tablica[i][j].x = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*cosf((float)M_PI*v));
			tablica[i][j].y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * u*u);
			tablica[i][j].z = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*sinf((float)M_PI*v));
			tablica[i][j].xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * u*u + 360 * u - 45)*cosf((float)M_PI*v);
			tablica[i][j].xv = (float)M_PI*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u*u + 45 * u)*sinf(M_PI*v);
			tablica[i][j].yu = (640 * pow(u, 3) - 960 * u*u + 320 * u);
			tablica[i][j].yv = 0.0;
			tablica[i][j].zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * u*u + 360 * u - 45)*sinf((float)M_PI*v);
			tablica[i][j].zv = (-1 * (float)M_PI)*(90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u*u + 45 * u)*cosf((float)M_PI*v);

		

			tablica[i][j].nx = tablica[i][j].yu*tablica[i][j].zv - tablica[i][j].zu*tablica[i][j].yv;
			tablica[i][j].ny = tablica[i][j].zu*tablica[i][j].xv - tablica[i][j].xu*tablica[i][j].zv;
			tablica[i][j].nz = tablica[i][j].xu*tablica[i][j].yv - tablica[i][j].yu*tablica[i][j].xv;

			if (i > N / 2)
			{
				tablica[i][j].nx = -1.0*tablica[i][j].nx;
				tablica[i][j].ny = -1.0*tablica[i][j].ny;
				tablica[i][j].nz = -1.0*tablica[i][j].nz;
			}


			if (i == N / 2) 
			{
				tablica[i][j].nx = 0.0;
				tablica[i][j].ny = 1.0;
				tablica[i][j].nz = 0.0;
			}

			if (i == 0 || i == N)
			{
				tablica[i][j].nx = 0.0;
				tablica[i][j].ny = -1.0;
				tablica[i][j].nz = 0.0;
			}

		

			
			//	cout << "Przed: " << sqrtf(tablica[i][j].nx*tablica[i][j].nx + tablica[i][j].ny*tablica[i][j].ny + tablica[i][j].nz*tablica[i][j].nz);
			float pierwiastek = sqrtf(tablica[i][j].nx*tablica[i][j].nx + tablica[i][j].ny*tablica[i][j].ny + tablica[i][j].nz*tablica[i][j].nz);
		
				//	if ()
				//	{
				tablica[i][j].nx = tablica[i][j].nx / pierwiastek;
				tablica[i][j].ny = tablica[i][j].ny / pierwiastek;
				tablica[i][j].nz = tablica[i][j].nz / pierwiastek;
				//	cout << "  po: " << sqrtf(tablica[i][j].nx*tablica[i][j].nx + tablica[i][j].ny*tablica[i][j].ny + tablica[i][j].nz*tablica[i][j].nz);
		//	}
			
			//cout << "  po: " << sqrtf(tablica[i][j].nx*tablica[i][j].nx + tablica[i][j].ny*tablica[i][j].ny + tablica[i][j].nz*tablica[i][j].nz) << endl;
		}

	/*for(int i = 0; i <= N; i++)
	{
	for (int j = 0; j <= N; j++)
	std::cout << tablica[i][j].x << ", " << tablica[i][j].y << ", " << tablica[i][j].z << "\t";

	std::cout << std::endl;
	}

	std::cin.get();
	std::cin.get();
	*/

	DrawEggTriangle();


}

void LightsMaking()
{
	glLightfv(GL_LIGHT0, GL_POSITION, light1);
	glLightfv(GL_LIGHT1, GL_POSITION, light2);
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

/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana, gdy trzeba 
// przerysowa� scen�)

void viewerPlacing()
{
	viewer[0] = promien*cos(THETA)*cos(PHI);
	viewer[1] = promien*sin(PHI);
	viewer[2] = promien*sin(THETA)*cos(PHI);
}

void light1Placing()
{
	light1[0] = promien*cos(THETA1)*cos(PHI1);
	light1[1] = promien*sin(PHI1);
	light1[2] = promien*sin(THETA1)*cos(PHI1);
}

void light2Placing()
{
	light2[0] = promien*cos(THETA2)*cos(PHI2);
	light2[1] = promien*sin(PHI2);
	light2[2] = promien*sin(THETA2)*cos(PHI2);
}

void AnglesCounting()
{
	PHI += delta_y*pix2angleY;
	THETA += delta_x*pix2angleX;

	if (cosf(PHI) >= 0.0f)
		y = 1.0f;
	else
		y = -1.0f;

}

void AnglesCountingLight1()
{
	PHI1 += delta_y*pix2angleY;
	THETA1 += delta_x*pix2angleX;

	if (cosf(PHI1) >= 0.0f)
		y = 1.0f;
	else
		y = -1.0f;
}

void AnglesCountingLight2()
{
	PHI2 += delta_y*pix2angleY;
	THETA2 += delta_x*pix2angleX;

	if (cosf(PHI2) >= 0.0f)
		y = 1.0f;
	else
		y = -1.0f;
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie??cej



	//gluLookAt(5.0, 2.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// Zdefiniowanie po�o�enia obserwatora
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej powy�ej


	if (statusL == 1)                     // je�li lewy klawisz myszy wci�ni�ty
	{
		AnglesCountingLight1();
	}                                  // do r�nicy po�o�e� kursora myszy

	if (statusP == 1)                     // je�li prawy klawisz myszy wci�ni�ty
	{
		AnglesCountingLight2();
	}

	light1Placing();
	light2Placing();


	LightsMaking();

	Egg();
	// Narysowanie czajnika
	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania
	glutSwapBuffers();
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
	GLfloat light_position[2][4] = { { -10.0, -10.0, -10.0, 1.0 },{ -10.0, -10.0, -10.0, 1.0 } };
	// po�o�enie �r�d�a

	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[2][4] = { { 1.0, 0.0, 0.0, 0.0 },{ 0.0, 0.0, 1.0, 1.0 } };
	// sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[2][4] = { { 1.0, 1.0, 0.0, 1.0 },{ 0.7, 0.7, 1.0, 1.0 } };
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
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse[0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular[0]);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position[0]);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse[1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular[1]);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position[1]);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);

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



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	pix2angleX = 2 * M_PI / (float)horizontal;  // przeliczenie pikseli na stopnie
	pix2angleY = 2 * M_PI / (float)vertical;  // przeliczenie pikseli na stopnie

	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie��cej 

	gluPerspective(70, 1.0, 1.0, 30.0);
	// Ustawienie parametr�w dla rzutu perspektywicznego


	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielko�ci okna okna widoku (viewport) w zale�no�ci
	// relacji pomi�dzy wysoko�ci� i szeroko�ci� okna

	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej 

}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



void main(void)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Oswietlenie 3D - 2 Zadanie");

	GeneratingColors();

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  B�dzie ona wywo�ywana za ka�dym razem 
	// gdy zajdzie potrzeba przerysowania okna

	glutMouseFunc(Mouse);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie ruchu myszy

	//glutIdleFunc(spinTeapot);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// za zmiany rozmiaru okna                       


	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania niewidocznych element�w sceny

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

/*************************************************************************************/