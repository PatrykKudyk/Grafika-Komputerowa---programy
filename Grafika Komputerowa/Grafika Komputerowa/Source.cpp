/*************************************************************************************/

// Najprostszy program wykorzystuj�cy funkcje biblioteki OpenGL

/*************************************************************************************/ 

#include <windows.h>

#include <gl/gl.h>

#include <gl/glut.h>

/*************************************************************************************/

// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)


void RenderScene(void)

{

    glClear(GL_COLOR_BUFFER_BIT); 
   // Czyszczenie okna aktualnym kolorem czyszcz�cym


    glFlush();
   // Przekazanie polece� rysuj�cych do wykonania

}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)

{

   glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
   // Kolor okna wn�trza okna - ustawiono na szary

}

 

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli

 

void main(void)

{

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   // Ustawienie trybu wy�wietlania
   // GLUT_SINGLE - pojedynczy bufor wy�wietlania
   // GLUT_RGBA - model kolor�w RGB


   glutCreateWindow("Pierwszy program w OpenGL");
   // Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

   
   glutDisplayFunc(RenderScene);
   // Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
   // Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
   // trzeba b�dzie przerysowa� okno

   MyInit(); 
   // Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie 
   // inicjalizacje konieczne przed przyst�pieniem do renderowania
  
   glutMainLoop();
   // Funkcja uruchamia szkielet biblioteki GLUT

}

/**************************************************************************************/