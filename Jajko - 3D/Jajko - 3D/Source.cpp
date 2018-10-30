/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi  
//  uk³adu wspó³rzednych

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

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych

struct Point
{
	float x;
	float y;
	float z;
};


//------------ZMIENNE GLOBALNE ------------------------//
static int N = 20;			//wielkosc tablicy

Point **tablica;		//dynamiczna tablica struktur punktowych

Point **kolory;			//dynamiczna tablica kolorów

int model = 1;  // 1- punkty, 2- siatka, 3 - wype³nione trójk¹ty

static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k¹ty obrotu



void DrawEggPoints()
{
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
	glEnd();
}

void DrawEggLines()
{
	
	for (int i = 0; i <= N; i++)
	{
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int j = 0; j <= N; j++)
			glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(1.0f, 1.0f, 1.0f);
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
			if(i <= (N - 1))
				if(j <= (N - 1))
				{
				glBegin(GL_TRIANGLES);
				glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
				glColor3f(kolory[i + 1][j + 1].x, kolory[i + 1][j + 1].y, kolory[i + 1][j + 1].z);
				glVertex3f(tablica[i + 1][j+1].x, tablica[i + 1][j + 1].y - 5.0f, tablica[i + 1][j + 1].z);
				glColor3f(kolory[i][j+1].x, kolory[i][j + 1].y, kolory[i][j + 1].z);
				glVertex3f(tablica[i][j + 1].x, tablica[i][j + 1].y - 5.0f, tablica[i][j + 1].z);
				glEnd();
				glBegin(GL_TRIANGLES);
				glColor3f(kolory[i][j].x, kolory[i][j].y, kolory[i][j].z);
				glVertex3f(tablica[i][j].x, tablica[i][j].y - 5.0f, tablica[i][j].z);
				glColor3f(kolory[i+1][j].x, kolory[i+1][j].y, kolory[i+1][j].z);
				glVertex3f(tablica[i + 1][j].x, tablica[i + 1][j].y - 5.0f, tablica[i + 1][j].z);
				glColor3f(kolory[i+1][j+1].x, kolory[i+1][j+1].y, kolory[i+1][j+1].z);
				glVertex3f(tablica[i+1][j + 1].x, tablica[i+1][j + 1].y - 5.0f, tablica[i+1][j + 1].z);
				glEnd();

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

void GeneratingColors()
{
	kolory = new Point*[N+1];
	for (int i = 0; i <= N; i++)
		kolory[i] = new Point[N+1];

	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
		{
			if (j == N)
			{
				kolory[i][j].x = kolory[i][0].x;
				kolory[i][j].y = kolory[i][0].y;
				kolory[i][j].z = kolory[i][0].z;
			}
			else {
				kolory[i][j].x = (float)(rand() % 1000 / 1000.0);
				kolory[i][j].y = (float)(rand() % 1000 / 1000.0);
				kolory[i][j].z = (float)(rand() % 1000 / 1000.0);
			}
		}
}

void Egg()
{

	tablica = new Point*[N+1];
	for (int i = 0; i <= N; i++)
		tablica[i] = new Point[N+1];
	
	for(int i = 0; i <= N; i++)
		for(int j = 0; j <= N; j++)
		{
			float u = (float)i / (float)N;
			float v = (float)j / (float)N;
			tablica[i][j].x = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*cos((float)M_PI*v));
			tablica[i][j].y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * u*u);
			tablica[i][j].z = ((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*sin((float)M_PI*v));
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

	switch(model)
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

	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}


void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz¹tek i koniec obrazu osi y
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

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba 
// przerysowaæ scenê)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej
/*	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia³y

	glRotated(60.0, 1.0, 1.0, 1.0);  // Obrót o 60 stopni

	glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty
	*/

	//glRotated(35.0, 1.0, 1.0, 1.0);  // Obrót o 60 stopni
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	
	Egg();

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania


	glutSwapBuffers();
	//
}

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene(); // przerysowanie obrazu sceny
}

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych 
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹ 
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej
}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli



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
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bedzie ona wywo³ywana za ka¿dym razem 
	// gdy zajdzie potrzba przeryswania okna 
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna      
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych

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