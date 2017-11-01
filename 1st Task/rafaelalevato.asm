;--------------------------------------------------------------------------------
;Disciplina de projeto nivel 1 em area basica
;Professor Hari Mohr
;Tarefa 1 - 2017-2
;Nome: Rafael Pintar Alevato
;
;Fazer um programa que rotacione um led aceso na porta b do kit.
;Enquanto a chave 1 estiver pressionada ele deve inverter o sentido de rota�ao.
;A chave 2 deve aumentar a velocidade de rota�ao.
;A chave 3 deve diminuir a velocidade de rota�ao.
;A chave 4 alterna o sentido de deslocamento a cada vez que for pressionada;
;--------------------------------------------------------------------------------


;-------------------------------- Rotaciona Led ---------------------------------

	ORG		00					;Origem na mem�ria do programa
	GOTO 	INITCONFIG			;Desvio para come�o do programa
	RADIX	DEC 				;Todos os n�meros ser�o considerados decimais se n�o dito nada
	INCLUDE "p16f628a.inc"		;Carrega defini��es do 16f628a


;----------------------------- Bits de Configura��o -----------------------------
 __CONFIG _CP_OFF &_PWRTE_ON &_WDT_OFF &_LVP_OFF &DATA_CP_OFF &_MCLRE_ON &_XT_OSC
;-------------------------------------------------------------------------------- 


;-------------------------- Declara��o de Equivalentes --------------------------
DELAY1		EQU		0x70    ;Para uso no delay
DELAY2		EQU		0x71    ;Para uso no delay
DELAY3		EQU		0x72    ;Para uso no delay
SPEED		EQU 	0x73	;Para uso da velocidade
DIRECTION	EQU 	0x74	;Para uso da dire��o de rota��o


#DEFINE 	KEY1	PORTA,1		;0 --> Pressionado	;1 --> Liberado
#DEFINE 	KEY2	PORTA,2		;0 --> Pressionado	;1 --> Liberado
#DEFINE 	KEY3	PORTA,3		;0 --> Pressionado	;1 --> Liberado
#DEFINE 	KEY4	PORTA,4		;0 --> Pressionado	;1 --> Liberado
;--------------------------------------------------------------------------------


;------------------------------------ Macros ------------------------------------
;Defini��o de comandos de usu�rio para altera��o da p�gina de mem�ria
BANK0 MACRO 			;Macro para acessar o banco 0 de registradores
	BCF 	STATUS,RP0
	BCF 	STATUS,RP1
	ENDM

BANK1 MACRO 			;Macro para acessar o banco 1 de registradores
	BSF 	STATUS,RP0
	BCF 	STATUS,RP1
	ENDM

BANK2 MACRO 			;Macro para acessar o banco 2 de registradores
	BCF 	STATUS,RP0
	BSF 	STATUS,RP1
	ENDM

BANK3 MACRO 			;Macro para acessar o banco 3 de registradores
	BSF 	STATUS,RP0
	BSF 	STATUS,RP1
	ENDM
;--------------------------------------------------------------------------------


;----------------------------- Configura��o Inicial -----------------------------
INITCONFIG 	BANK1			 		;Usando banco 1
			CLRF	TRISB 			;Define todas as portas de portb como sa�da
			MOVLW	B'11111111'
			MOVWF	TRISA			;Define todas as portas de portb como entrada
			MOVLW	B'10000000' 
			MOVWF	OPTION_REG 		;Habilitado portb pull-up enable bit
			MOVLW	B'00000000' 
			MOVWF	INTCON 			;Desabilitado todas as interrup��es
			BANK0 					;Usando banco 0
;--------------------------------------------------------------------------------

;------------------------------ Programa Principal ------------------------------
			MOVLW	B'00000001'
			MOVWF	PORTB 			;Liga 1 LED
			MOVLW	20
			MOVWF	SPEED 			;Seta velocidade inicial 20
			CLRF	DIRECTION

LOOP		BTFSS	KEY4 			;Testa se bot�o 4 pressionado
			GOTO	KEY4PRESS
			
IFROT		BTFSS	DIRECTION,0		;Testa a dire��o padr�o de rota��o
			GOTO	STDLEFT			;Se direction = 0
			GOTO	STDRIGHT		;Se direction = 1

STDLEFT		BTFSS	KEY1 			;Testa se bot�o 1 pressionado
			GOTO	ROTATER			;Se sim, rotaciona direita
			GOTO	ROTATEL			;Se n�o, rotaciona esquerda

STDRIGHT	BTFSS	KEY1 			;Testa se bot�o 1 pressionado
			GOTO	ROTATEL			;Se sim, rotaciona esquerda
			GOTO	ROTATER			;Se n�o, rotaciona direita

IFSPD1		BTFSS	KEY2			;Testa se bot�o 2 pressionado
			GOTO	DECSPD			;Se sim, decrementa velocidade

IFSPD2		BTFSS	KEY3			;Se n�o, teste se bot�o 3 pressionado
			GOTO 	INCSPD			;Se sim, incrementa velocidade

SETSPD		MOVF 	SPEED,W 		;Se n�o, coloca a velocidade no delay
			MOVWF	DELAY3

MDELAY		GOTO	DELAY 			;enquanto delay3 n�o for 0, continua neste loop
RETD		DECFSZ	DELAY3,F
			GOTO 	MDELAY
			GOTO	LOOP 			;Loop principal do programa
;--------------------------------------------------------------------------------

;--------------------------------- Main Delay -----------------------------------
;Executa um n�mero de instru��es NxM vezes
DELAY 		MOVLW	100
			MOVWF	DELAY2
RESET1		MOVLW	100
			MOVWF	DELAY1
DEC1		DECFSZ	DELAY1,F		;Loop iterno executado N vezes
			GOTO 	DEC1
			DECFSZ	DELAY2,F		;Decrementa um e volta no loop anterior executando NxM vezes
			GOTO 	RESET1
			GOTO	RETD 			;Retorna pra fun��o principal
;--------------------------------------------------------------------------------

;--------------------------------- Rotate Left ----------------------------------
ROTATEL		RLF		PORTB, 1
			BTFSC	STATUS,0
			BSF 	PORTB,0
			BCF		STATUS,0
			GOTO	IFSPD1
;--------------------------------------------------------------------------------

;-------------------------------- Rotate Right ----------------------------------
ROTATER		RRF		PORTB, 1
			BTFSC	STATUS,0
			BSF 	PORTB,7
			BCF		STATUS,0
			GOTO	IFSPD1
;--------------------------------------------------------------------------------

;------------------------------- Decrement Speed --------------------------------
;Decrementa a velocidade
;Depois testa se velocidade � zero, se for, coloca 1 em velocidade
DECSPD		DECFSZ 	SPEED
			GOTO	IFSPD2
			MOVLW	1
			MOVWF	SPEED
			GOTO	IFSPD2
;--------------------------------------------------------------------------------

;------------------------------- Increment Speed --------------------------------
;Incrementa a velocidade
;Depois testa se velocidade � zero, se for, coloca 255 em velocidade
INCSPD		INCFSZ 	SPEED
			GOTO	SETSPD
			MOVLW	0xFF
			MOVWF	SPEED
			GOTO	SETSPD
;--------------------------------------------------------------------------------

;--------------------------------- KEY4 Press -----------------------------------
;Se pressionou KEY4, espera sotlar o bot�o e complementa o bit de dire��o
KEY4PRESS	BTFSS	KEY4
			GOTO	KEY4PRESS
			BTFSC	DIRECTION,0
			GOTO	SETDIR0
			GOTO	SETDIR1
SETDIR0		BCF		DIRECTION,0
			GOTO	IFROT
SETDIR1		BSF 	DIRECTION,0
			GOTO	IFROT
;--------------------------------------------------------------------------------
			END