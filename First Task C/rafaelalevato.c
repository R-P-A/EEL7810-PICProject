//Programa : Pisca LED com PIC16F628A
//Autor : FILIPEFLOP

//Carrega a biblioteca para o microcontrolador PIC16F628A
#include <16F628A.h>

//Configuracao FUSES
#FUSES NOWDT
#FUSES INTRC_IO
#FUSES NOPUT
#FUSES NOPROTECT
#FUSES NOBROWNOUT
#FUSES NOMCLR
#FUSES NOLVP
#FUSES NOCPD

//Define a utilização do clock interno de 4 Mhz
#use delay(clock=4000000)

#define PINOLED PIN_B2 //Pino ao qual o led esta ligado

void main()
{
while (1)
 {
  output_bit(PINOLED, TRUE); // Liga o Led
  delay_ms(5000); // Aguarda 3 segundos
  output_bit(PINOLED, FALSE); // Desliga o Led
  delay_ms(2000); // Aguarda 2 segundos
 }
}