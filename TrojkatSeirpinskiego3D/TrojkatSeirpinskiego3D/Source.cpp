/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi  
//  uk³adu wspó³rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>
#include <iostream>

/*************************************************************************************/
typedef float point3[3];
// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych

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

Point startPoint = { { -5.0 } ,{ -2.5 },{ -5.0 } };
//Point startPoint = { {((-N)/2.0)}, {(-sqrt(startSideLength*(startSideLength / 2.0)))} , {((-N)/2.0)}};

int model = 1;  // 1- czerwony, 2- niebieski, 3 - zielony, 4 - fioletowy



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

void RysowanieCzerwony(Point A, float sideLength)
{
	glBegin(GL_POLYGON);		//rysowanie wielok¹ta (czworok¹t) - Podstawa ostros³upa
	glColor3f(1.0f, 0.0f, 0.0f);	//ustawienie koloru na czerwony

	//rysowanie kolejnych punktów podaj¹c odpowiednie wspó³rzêdne
	glVertex3f(A.x, A.y, A.z);		
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();		//zakoñczenie rysowania wielok¹ta


	glBegin(GL_TRIANGLES);	//rysowanie jednego z czterech trójk¹tów
	glColor3f(0.9f, 0.0f, 0.0f);	//ustawienie koloru na lekko mniej czerwony

	//rysowanie kolejnych punktów podaj¹c odpowiednie wspó³rzêdne
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z);
	glEnd();	//zakoñczenie rysowania trójk¹ta


	glBegin(GL_TRIANGLES);	//rysowanie kolejnego z czterech trójk¹tów
	glColor3f(0.8f, 0.0f, 0.0f);	//ustawienie koloru na lekko mniej czerwony

	//rysowanie kolejnych punktów podaj¹c odpowiednie wspó³rzêdne
	glVertex3f(A.x + sideLength, A.y, A.z);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glEnd();	//zakoñczenie rysowania trójk¹ta


	glBegin(GL_TRIANGLES);	//rysowanie kolejnego z czterech trójk¹tów
	glColor3f(0.7f, 0.0f, 0.0f);	//ustawienie koloru na lekko mniej czerwony

	//rysowanie kolejnych punktów podaj¹c odpowiednie wspó³rzêdne
	glVertex3f(A.x + sideLength, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z + sideLength);
	glEnd();	//zakoñczenie rysowania trójk¹ta


	glBegin(GL_TRIANGLES);	//rysowanie kolejnego z czterech trójk¹tów
	glColor3f(0.6f, 0.0f, 0.0f);	//ustawienie koloru na lekko mniej czerwony

	//rysowanie kolejnych punktów podaj¹c odpowiednie wspó³rzêdne
	glVertex3f(A.x, A.y, A.z + sideLength);
	glVertex3f(A.x + (sideLength / 2.0), A.y + sqrt(sideLength*(sideLength / 2.0)), A.z + (sideLength / 2.0));
	glVertex3f(A.x, A.y, A.z);
	glEnd();	//zakoñczenie rysowania trójk¹ta

	//Rysowanie lini na rogach trójk¹tów i podstawy. Kolor jest niebieski
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
	if (level >= maxLevel)	//sprawdzenie, czy algorytm zszed³ ju¿ tak nisko jak jest to wymagane
	{
		switch (model)		//sprawdzenie który kolor ostros³upa zosta³ wybrany przez u¿ytkownika
		{
		case 1:
			RysowanieCzerwony(A, sideLength);	//Wywo³anie metody rysuj¹cej czerwony ostros³up
			break;
		case 2:
			RysowanieNiebieski(A, sideLength);	//Wywo³anie metody rysuj¹cej niebieski ostros³up
			break;
		case 3:
			RysowanieZielony(A, sideLength);	//Wywo³anie metody rysuj¹cej zielony ostros³up
			break;
		case 4:
			RysowanieFioletowy(A, sideLength);	//Wywo³anie metody rysuj¹cej fioletowy ostros³up
			break;
		default:
			break;
		}
	}
	else
	{
		sideLength = sideLength / 2.0;			//podzia³ d³ugoœci boku
		level += 1;								//zwiêkszenie poziomu algorytmu
		DrawSierpinski(A, sideLength, level);	//rekurencyjne wywo³anie funkcji dla pierwszego punktu
		A.x += sideLength;			//odpowiednie ustawienie punktu do przekazania dalej
		DrawSierpinski(A, sideLength, level);	//rekurencyjne wywo³anie funkcji dla drugiego punktu
		A.x -= sideLength;			//odpowiednie ustawienie punktu 
		A.z += sideLength;			//do przekazania dalej
		DrawSierpinski(A, sideLength, level);	//rekurencyjne wywo³anie funkcji dla trzeciego punktu
		A.x += sideLength;			//odpowiednie ustawienie punktu do przekazania dalej
		DrawSierpinski(A, sideLength, level);	//rekurencyjne wywo³anie funkcji dla czwartego punktu
		A.x -= sideLength;			//odpowiednie ustawienie punktu 
		A.z -= sideLength;			//do przekazania dalej
		A.y += sqrt(sideLength*(sideLength / 2.0));
		A.x += (sideLength / 2.0);	//odpowiednie ustawienie punktu
		A.z += (sideLength / 2.0);	//do przekazania dalej
		DrawSierpinski(A, sideLength, level);	//rekurencyjne wywo³anie funkcji dla pi¹tego punktu
	}

}


void spinPyramid()
{
	if (stop)	//sprawdzam czy nie zosta³a nacisnieta spacja
	{
		theta[0] += wartosc;						//	Fragment kodu sprawiaj¹cy, ¿e ostros³up wzgledem osi OX porusza siê bardzo nieznacznie
		if (theta[0] < -30.0)  wartosc = 0.015;		//	w celu pokazania trójwymiarowoœci. 
		if (theta[0] > 0.0) wartosc = -0.015;		//	Ostros³up tak jakby odbija siê od dwóch niewidzialnych œcian na osi OX

		if (spin == 0)	//sprawdzam w ktora strone ma sie krecic ostros³up  (obs³ugiwane przy pomocy klawisza "q")
			theta[1] -= 0.25;			//Obrót ostros³upa wzglêdem osi OY
		
		else
			theta[1] += 0.25;			//Obrót ostros³upa wzglêdem osi OY
		
		glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
	}
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

	glRotatef(theta[0], 1.0, 0.0, 0.0);	//obrót sceny wzglêdem osi OX
	glRotatef(theta[1], 0.0, 1.0, 0.0);	//obrót sceny wzglêdem osi OY
	glRotatef(theta[2], 0.0, 0.0, 1.0);	//obrót sceny wzglêdem osi OZ

	DrawSierpinski(startPoint, startSideLength, 0);

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

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych 
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹ 
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.

void keys(unsigned char key, int x, int y)
{
	if (key == 'c') model = 1;	//je¿eli naciœniête c to kolor trojkata czerwony
	if (key == 'n') model = 2;	//je¿eli naciœniête n to kolor trojkata niebieski
	if (key == 'z') model = 3;	//je¿eli naciœniête z to kolor trojkata zielony
	if (key == 'f') model = 4;	//je¿eli naciœniête f to kolor trojkata fioletowy
	if (key == '+')		//je¿eli naciœniêty + to algorytm wchodzi na poziom wy¿ej
		if (maxLevel<5)
			++maxLevel;
	if (key == '-')		//je¿eli naciœniêty - to algorytm schodzi o poziom ni¿ej
		if (maxLevel > 0)
			--maxLevel;
	if (key == 'q')		//je¿eli naciœniête q to zmiana kierunku obrotu ostros³upa
		if (spin == 0)
			spin = 1;
		else
			spin = 0;
	if (key == ' ')		//je¿eli naciœniête q to zatrzymane obracanie trójk¹ta
		if (stop == 0)
			stop = 1;
		else
			stop = 0;

	RenderScene(); // przerysowanie obrazu sceny
}


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
	srand(time(NULL));		//umo¿liwienie losowania liczb

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);	//startowy rozmiar okienka

	glutCreateWindow("Trojkat sierpinskiego w 3-D");	//Nazwa okienka

	glutKeyboardFunc(keys);		//obs³uga klawiarury

	glutIdleFunc(spinPyramid);	//obs³uga obrotu ostros³upa

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
}

/*************************************************************************************/