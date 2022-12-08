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
char mensage;
int Timer2, Poscaler;

#INT_EXT //interrupcion externa
void interrupcion(){
   output_toggle(pin_a0);
   DELAY_MS(200);
   output_toggle(pin_a0);
}

int calculaTem(int corriente){
   int temperatura;
   temperatura = corriente*(5/100);
   return temperatura;
}

int calculaLuz(int corriente){
   int luz;
   luz = corriente*(5/100);
   return luz;
}

void apagarLuz(int luz){
   if(luz<30 && prendido==1){
      prendido=0;
      output_toggle(pin_a1);
   }
}

void encenderLuz(int luz){
   if(luz<30 && prendido==0){
      prendido=1;
      output_toggle(pin_a1);
   }
}

void MAIN()
{
   int torch;     //corriente correspondiente al sensor de luz
   int term;      //corriente correspondiente al termometro
   
   SET_TRIS_A(0);    //Configura PUERTO A como salida
   SET_TRIS_B(0XFF);    //Configura PUERTO B como entrada
   
   
   //configuracion entradas analogicas
   setup_adc(ADC_CLOCK_INTERNAL); //CONFIGURAMOS RELOG INTERNO
   setup_adc_ports(sAn10); 
   setup_adc_ports(sAn8); 
      
   LCD_INIT();       //Inicializa el LCD
   LCD_PUTC("\f"); 
   
   //PWM del motor
   //generamos una se�al cuadrada de 3Khz
    timer2=187; //se carga el timer 2 187
    poscaler=1;
    setup_timer_2(t2_div_by_16, Timer2, Poscaler);
    setup_ccp1(ccp_pwm);
   
   //interrupciones
   ENABLE_INTERRUPTS(GLOBAL); //Habilita todas las interrupciones
   ENABLE_INTERRUPTS(INT_EXT); //Habilita la interrupci�n externa
   
   WHILE(TRUE)
   {  
      //capturamos la entrada del sensor de luz
      set_adc_channel(10);
      torch=read_adc(); 
      luz=calculaLuz(torch);
      
      //desidimmos si apagar la luz , encenderla o ninguna
      apagarLuz(luz);
      encenderLuz(luz);
      
      //capturamos la entrada del censor de temperatura
      set_adc_channel(8);
      term=read_adc();
      temperatura=calculaTem(term);
      
      //desidimos si ensender el ventilador
      if(temperatura>30){
         set_pwm1_duty(term);
      
      LCD_GOTOXY(3,1);       
      LCD_PUTC("INVERNADERO LAB DE MICROS");    
      LCD_GOTOXY(6,2);       
      LCD_PUTC("Iluminacion: "+luz);
      LCD_GOTOXY(9,2);       
      LCD_PUTC("temperadura: "+temperatura);  
      }
   } 
}
