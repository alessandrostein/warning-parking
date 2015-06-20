void interrupt(void) {
  INTCON.INTF = 0; // Limpa a Flag da Interrupção para 0
}

void WaitForSec(unsigned int t){
  int count = 0;
  TMR0 = 0; // Configura o Timer iniciar em 0
  OPTION_REG.T0CS = 0; // Configura o Timer para usar o Oscilador interno
  OPTION_REG.T0SE = 0; // Configura se a borda é de subida(0) ou descida(1).
  OPTION_REG.PSA = 0; // Configura o Prescaler para usar o Time0 module -> Se for 0 -> Watch Dog Timer
  OPTION_REG.PS0 = 1; // Configura a faixa (escala) de seleção
  OPTION_REG.PS1 = 1; // Configura a faixa (escala) de seleção
  OPTION_REG.PS2 = 1; // Configura a faixa (escala) de seleção

  while (1){
    while (!INTCON.T0IF); // Flag de Interrupção do Temporizador 0
    INTCON.T0IF = 0; // Limpa a Flag da Interrupção do Temporizador para 0
    count ++;
    if (count == 30 * t){
      count = 0;
      break;
    }
  }
}

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
  TRISB.RB2 = 0; // Configura como Saída
  TRISB.RB3 = 0; // Configura como Saída
  PORTB.RB2 = 0; // Inicia Led Desligado
  PORTB.RB3 = 0; // Inicia Led Desligado

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

  // Configurações da Tecla RB1.
  TRISB.RB1 = 1; // Configura como Entrada
  PORTB.RB1 = 0; // Configura estado inicial (Simulação 0 => Carro saindo, 1 => Carro entrando)

  // Configurações do Interruptor Externo
  TRISB.RB0 = 1; // Configura como Entrada
  INTCON.GIE = 1; // Habilita Interruptor global
  INTCON.INTE = 1; // Habilita RB0/INT Interrupção externa
  INTCON.PEIE = 0; // Desabilita todas interrupções periférica desmascarado
  OPTION_REG.INTEDG = 0; // Interrupção com borda de descida

  while(1){
    // That start tests =D
  }
}