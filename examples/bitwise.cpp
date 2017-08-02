#include <iostream>
#include <inttypes.h>
#include <stdint.h>

using namespace std;

int main() {
  uint16_t number16 = 54233; 			//1101001111011001
  uint8_t highbyte = (number16 & 0xFF00) >> 8;  //11010011     
  uint8_t lowbyte = (number16 & 0x00FF);	//11011001

  cout << "Originalzahl: " << number16 << "\nAuseinandergenommen: \n \t highbyte: " <<(int) highbyte << "\n \t lowbyte: " <<(int) lowbyte << "\n";
  
  //Setzen wir den Wert wieder zusammen :P

  uint16_t number16New;
  number16New = (highbyte <<8) | lowbyte;

  cout << "Wieder zusammen gesetzt: " << number16New << "\n";
}
