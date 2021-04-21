// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "matrix.hh"
#include "rectangle.hh"
#include "../include/lacze_do_gnuplota.hh"

/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

#define DL_KROTKI_BOK  100
#define DL_DLUGI_BOK   150

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void PrzykladZapisuWspolrzednychDoStrumienia( std::ostream&     StrmWy, 
                                              double       Przesuniecie
                                            )
{
   //---------------------------------------------------------------
   // To tylko przyklad !!!
   // W programie nalezy uzywać pojęcia wektora, a nie oddzielnych 
   // zmiennych do reprezentowania wspolrzednych!
   //
  double  x1, y1, x2, y2, x3, y3, x4, y4; 

  x1 = y1 = 10;
  x2 = x1 + DL_DLUGI_BOK;  y2 = y1;
  x3 = x2;  y3 = y2 + DL_KROTKI_BOK;
  x4 = x3 - DL_DLUGI_BOK; y4 = y3;


  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << x1+Przesuniecie 
         << std::setw(16) << std::fixed << std::setprecision(10) << y1+Przesuniecie << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << x2+Przesuniecie 
         << std::setw(16) << std::fixed << std::setprecision(10) << y2+Przesuniecie << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << x3+Przesuniecie 
         << std::setw(16) << std::fixed << std::setprecision(10) << y3+Przesuniecie << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << x4+Przesuniecie 
         << std::setw(16) << std::fixed << std::setprecision(10) << y4+Przesuniecie << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << x1+Przesuniecie 
         << std::setw(16) << std::fixed << std::setprecision(10) << y1+Przesuniecie << std::endl; 
                             // Jeszcze raz zapisujemy pierwszy punkt,
                             // aby gnuplot narysowal zamkniętą linię.
}



/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool PrzykladZapisuWspolrzednychDoPliku( const char  *sNazwaPliku,Rectangle rec)
{
  std::ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << ":(  nie powiodla sie." << std::endl;
    return false;
  }
std::cout<<rec;
  StrmPlikowy<<rec;

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

int main() {
  std::cout << "Project Rotation 2D based on C++ Boiler Plate v"
            << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
            << "."
            << PROJECT_VERSION_MINOR /* istotne zmiany */
            << "."
            << PROJECT_VERSION_PATCH /* naprawianie bugów */
            << "."
            << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
            << std::endl;
  // std::system("cat ../LICENSE");
  // do zadania Rotacja 2D

    PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  Lacze.DodajNazwePliku("prostokat.dat",PzG::RR_Ciagly,2);
   //
   //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
   //      których połowa długości boku wynosi 2.
   //
  Lacze.DodajNazwePliku("prostokat.dat",PzG::RR_Punktowy,2);
   //
   //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy tylko x,y.
   //
  Lacze.ZmienTrybRys(PzG::TR_2D);
  double wec3[]={20,20};
  Vector argumentsV(wec3);
Rectangle rec(argumentsV,DL_KROTKI_BOK,DL_DLUGI_BOK);
 
  

  // Z bazy projektu-wydmuszki Boiler Plate C++:
  // Bring in the dummy class from the example source,
  // just to show that it is accessible from main.cpp.
  char opcja;
int ile;//ile razy ma sie powturzyc obrut
double kat;
double wek[2];
std::cout<<"o"<<std::endl;
std::cout<<"p"<<std::endl;
std::cout<<"w"<<std::endl;
std::cout<<"m"<<std::endl;
std::cout<<"k"<<std::endl;   

while (opcja != 'k')
{
   if (!PrzykladZapisuWspolrzednychDoPliku("../datasets/prostokat.dat",rec)) return 1;
  Lacze.Rysuj();
    std::cin>>opcja;
    switch(opcja)
    {
        case 'o':
        {
            std::cin>>kat;
            std::cin>>ile;
            for(int i=0; i<ile; i++)
            {
               Matrix tmpM1;
               tmpM1.obr(kat,rec);
            }
        }break;
        case 'p':
        {
          double x,y;
            std::cin>>x>>y;
             wek[0]=x;
             wek[1]=y;
              Vector tmpV1 (wek);
            rec.move(tmpV1);
        }break;
        case 'w':
        {
            std::cout<<rec;
        }break;
         case 'm':
        {
            std::cout<<"o"<<std::endl;
std::cout<<"p"<<std::endl;
std::cout<<"w"<<std::endl;
std::cout<<"m"<<std::endl;
std::cout<<"k"<<std::endl;        }break;
    }
    //kod rysujacy w gnuplocie
    
}
  Dummy d = Dummy();
  return d.doSomething() ? 0 : -1;

}
