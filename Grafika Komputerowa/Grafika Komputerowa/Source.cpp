/*************************************************************************************/

// Najprostszy program wykorzystuj¹cy funkcje biblioteki OpenGL

/*************************************************************************************/ 

#include <windows.h>

#include <gl/gl.h>

#include <gl/glut.h>

/*************************************************************************************/

// Funkcaja okreœlaj¹ca, co ma byæ rysowane 
// (zawsze wywo³ywana, gdy trzeba przerysowaæ scenê)


void RenderScene(void)

{

    glClear(GL_COLOR_BUFFER_BIT); 
   // Czyszczenie okna aktualnym kolorem czyszcz¹cym


    glFlush();
   // Przekazanie poleceñ rysuj¹cych do wykonania

}

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania



void MyInit(void)

{

   glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
   // Kolor okna wnêtrza okna - ustawiono na szary

}

 

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli

 

void main(void)

{

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   // Ustawienie trybu wyœwietlania
   // GLUT_SINGLE - pojedynczy bufor wyœwietlania
   // GLUT_RGBA - model kolorów RGB


   glutCreateWindow("Pierwszy program w OpenGL");
   // Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna

   
   glutDisplayFunc(RenderScene);
   // Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
   // Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
   // trzeba bêdzie przerysowaæ okno

   MyInit(); 
   // Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie 
   // inicjalizacje konieczne przed przyst¹pieniem do renderowania
  
   glutMainLoop();
   // Funkcja uruchamia szkielet biblioteki GLUT

}

/**************************************************************************************/