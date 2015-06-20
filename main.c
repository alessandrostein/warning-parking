void main(){
  ADCON1 = 0x07; // Configura todas portas como Digital

  // Configurações do Buzzy
  TRISC.RC1 = 0; // Configura como Saída
  PORTC.RC1 = 1; // Inicia Buzzy Desligado

  // Configurações do Led
  TRISB = 0b00000000; // Configura como Saída
  PORTB = 0b00000000; // Inicia todos os Leds Desligado

  // Configurações do 7 segmentos
  TRISA.RA2 = 0; // Configura como Saída
  TRISA.RA3 = 0; // Configura como Saída
  TRISA.RA4 = 0; // Configura como Saída
  TRISA.RA5 = 0; // Configura como Saída

  TRISD = 0X00; // Configura como Saída

  PORTA.RA2 = 1; // Módulo Display Ligado
  PORTA.RA3 = 1; // Módulo Display Ligado
  PORTA.RA4 = 1; // Módulo Display Ligado
  PORTA.RA5 = 1; // Módulo Display Ligado
}