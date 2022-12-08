//LCD_PUTC(c);// Muestra el caracter "C" en la próxima posición del LCD.
//LCD_PUTC("/f");//Borra todo lo que haya en el display.
//LCD_PUTC("/n");// Va al inicio de la segunda línea.
//LCD_PUTC("/b"); //Se mueve una posición hacia atrás.
//LCD_GOTOXY(x,y); //Ubica el cursor en la posición indicada por "X" y "Y". (1,1)
//LCD_GETC(x,y); //Retorna el carácter ubicado en la posición X,Y del LCD.
//frecuencia de pwm 3kh

#INCLUDE <16F887.H>
#USE DELAY(CLOCK=4000000)
#INCLUDE <LCD.C>
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP
#BYTE PORTC=7
#BYTE PORTB=6
#BYTE PORTA=8

int temperatura;
int luz;
int prendido;

void interrupcion(){
   DELAY_MS(200);
   If(input(PIN_B0)){
      PORTA=0;
   }
}
int calculaTem(int corriente){
   int temperatura;
   return temperatura;
}

int calculaLuz(int corriente){
   int luz;
   return luz;
}

void apagarLuz(int luz){
   
}

void encenderLuz(int luz){
   if(luz<30 && prendido==0){
      
   }
}

void MAIN()
{
   setup_adc(ADC_CLOCK_INTERNAL); //CONFIGURAMOS RELOG INTERNO
   setup_adc_ports(sAn10); 
   setup_adc_ports(sAn8); 
      
   LCD_INIT();       //Inicializa el LCD
   LCD_PUTC("\f"); 
   
   int torch;     //corriente correspondiente al sensor de luz
   int term;      //corriente correspondiente al termometro
   WHILE(TRUE)
   {  
      set_adc_channel(10);
      torch=read_adc(); 
      luz=calculaLuz(torch);
      
      set_adc_channel(8);
      term=read_adc();
      temperatura=calculaTem(term);
      
      LCD_GOTOXY(3,1);       
      LCD_PUTC("Laboratorio Micros");    
      LCD_GOTOXY(6,2);       
      LCD_PUTC("Iluminacion: "+luz);
      LCD_GOTOXY(9,2);       
      LCD_PUTC("temperadura: "+temperatura);    
   } 
}
