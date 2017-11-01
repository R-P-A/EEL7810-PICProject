// --------------------------------------------------------------------------------
// Disciplina de projeto nivel 1 em area basica
// Professor Hari Mohr
// Tarefa 1 - 2017-2
// Nome: Rafael Pintar Alevato

// Fazer um programa que rotacione um led aceso na porta b do kit.
// Enquanto a chave 1 estiver pressionada ele deve inverter o sentido de rotação.
// A chave 2 deve aumentar a velocidade de rotação.
// A chave 3 deve diminuir a velocidade de rotação.
// A chave 4 alterna o sentido de deslocamento a cada vez que for pressionada.
// --------------------------------------------------------------------------------

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

#define SIZE_PORT_B 8
#define DELAY_INTERVAL 25
#define KEY_1 PIN_A1
#define KEY_2 PIN_A2
#define KEY_3 PIN_A3
#define KEY_4 PIN_A4
#define PRESSED 0
#define RELEASED 1

void rotatePortB (int16* portB, signed int16 direction);

void main() {
	//Declara a PORTB como array. Mais lento, porém utilizado para efeitos didáticos.
	int16 portB[] = {PIN_B7, PIN_B6, PIN_B5, PIN_B4, PIN_B3, PIN_B2, PIN_B1, PIN_B0};
	signed int16 direction = -1;	// 1 para esquerda, -1 para direita
	signed int16 defaultDirection = 1;
	signed int16 delayMultplier = 10;
	int1 isKey4Pressed = false;

	while (true) {
		if (input(KEY_1) == PRESSED)
			direction = defaultDirection*-1;
		else
			direction = defaultDirection;

		if (input(KEY_2) == PRESSED) {
			delayMultplier--;
			if (delayMultplier < 0)
				delayMultplier = 0;
		}

		if (input(KEY_3) == PRESSED) {
			delayMultplier++;
			if (delayMultplier > 200)
				delayMultplier = 200;
		}

		if (input(KEY_4) == PRESSED) {
			isKey4Pressed = true;
		} else if (isKey4Pressed) {
			isKey4Pressed = false;
			defaultDirection *= -1;
		}

		rotatePortB(portB, direction);
		delay_ms(delayMultplier*DELAY_INTERVAL);
	}
	
}

void rotatePortB (int16* portB, signed int16 direction) {
	static signed int16 index = 0;
	output_bit(portB[index], false);
	//Calcula o andar pelo array com a função módulo, já criando o rotate
	index = (SIZE_PORT_B + (index + direction)) % SIZE_PORT_B;
	output_bit(portB[index], true);
}

