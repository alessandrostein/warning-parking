unsigned short mask(unsigned short num) {
  switch (num) {
    case 0: return 0x3F; break;
    case 1: return 0x06; break;
    case 2: return 0x5B; break;
    case 3: return 0x4F; break;
    case 4: return 0x66; break;
    case 5: return 0x6D; break;
    case 6: return 0x7D; break;
    case 7: return 0x07; break;
    case 8: return 0x7F; break;
    case 9: return 0x6F; break;
    default: return 0x00; break;
  }
}

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