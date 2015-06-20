void main(){
  // Configurações do Buzzy
  TRISC.RC1 = 0; // Configura como Saída
  PORTC.RC1 = 1; // Inicia Buzzy Desligado
  // Configurações do Led
  TRISB = 0b00000000; // Configura como Saída
  PORTB = 0b00000000; // Inicia todos os Leds Desligado
}