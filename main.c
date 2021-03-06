int vagas;
int max_vagas = 9;
int processoCompleto = 1; // 0 - Processo incompleto 1 - Processo completo
int i = 0;

// LCD module connections
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module connections

unsigned short NumberToChar(unsigned short num) {
  switch (num) {
    case 0: return '0'; break;
    case 1: return '1'; break;
    case 2: return '2'; break;
    case 3: return '3'; break;
    case 4: return '4'; break;
    case 5: return '5'; break;
    case 6: return '6'; break;
    case 7: return '7'; break;
    case 8: return '8'; break;
    case 9: return '9'; break;
    default: return '9'; break;
  }
}

void WaitForSec(unsigned int t){
  int count = 0;
  T2CON = 0b01111100;
  TMR2 = 0; // Inicia Temporizador 2
  PR2 = 0xFF;

  while (1){
    while (! PIR1.TMR2IF); // Flag de Interrupção do Temporizador 2

    PIR1.TMR2IF = 0;  // Limpa flag de Interrupção do Temporizador 2
    count ++;
    if (count == 488 * t){
      count = 0;
      break;
    }
  }
}

void interrupt(void) {
  INTCON.INTF = 0; // Limpa a Flag da Interrupção para 0
  processoCompleto = 1; // Processo completo
}

void LigaLed(){
  PORTD = 0xF0;
}

void AlternaLed(){
  PORTD = ~PORTD;
}

void AlternaBuzzer(){
  PORTC.RC1 = !PORTC.RC1;
}

void DesligaLed(){
  PORTD = 0b00000000;
}

void LigaTodosLed(){
  PORTD = 0b11111111;
}

void DesligaBuzzer(){
  PORTC.RC1 = 1;
}

void LimpaTodoLCD(){
  Lcd_Cmd(_LCD_CLEAR);
}

void AbreCancela(int numero_cancela){
  if (numero_cancela == 1) {
     PORTC.RC0 = 1;
  } else {
     PORTE.RE0 = 1;
  }
}

void FechaCancela(int numero_cancela){
  if (numero_cancela == 1) {
     PORTC.RC0 = 0;
  } else {
     PORTE.RE0 = 0;
  }
}

void DesligaAlerta(){
  DesligaLed();
  DesligaBuzzer();
  LimpaTodoLCD();
}

void LigaAlerta(){
  LigaLed();
  i = 0;
  do {
    WaitForSec(1);
    AlternaLed();

    for (i; i < 30; i++){
      if (processoCompleto == 0) {
        AlternaLed();
        AlternaBuzzer();
        WaitForSec(1);
      }
    }

    DesligaBuzzer();
  } while (processoCompleto < 1);
}

void main (){
  ADCON1 = 0x06; // Configura todas portas como Digital

  // Configurações do LED 1
  TRISD = 0x00; // Configura registrador como Saída

  // Configurações do Buzzy
  TRISC.RC1 = 0; // Configura como Saída
  PORTC.RC1 = 1; // Inicia Buzzy Desligado

  // Configurações da Interrupção
  TRISB.RB0 = 1;         // Configura como Entrada
  INTCON.GIE = 1;        // Habilita Interruptor global
  INTCON.INTE = 1;       // Habilita RB0/INT Interrupção externa
  INTCON.PEIE = 0;       // Desabilita todas interrupções periférica desmascarado
  OPTION_REG.INTEDG = 0; // Interrupção com borda de descida

  Lcd_Init();               // Inicia LCD
  Lcd_Cmd(_LCD_CLEAR);      // Limpar Display
  Lcd_Cmd(_LCD_CURSOR_OFF); // Desliga cursor
  
  // ++ Configurações do Relé 1 => Carro entrando
  TRISC.RC0 = 0; // Configura como Saída
  PORTC.RC0 = 0; // Inicia desligado => Cancela fechada
  // ++ Configurações do Relé 2 => Carro Saindo
  TRISE.RE0 = 0; // Configura como Saída
  PORTE.RE0 = 0; // Inicia desligado => Cancela fechada

  vagas = max_vagas;

  DesligaBuzzer();
  LigaTodosLed();

  while (1){
    if (vagas == 0) {
      Lcd_out(1,1,"**** LOTADO *****");
    } else {
      Lcd_out(1,1,"Vagas: ");
      Lcd_Chr(1,8, NumberToChar(vagas));
    }
    LigaTodosLed();

    // Carro entrando
    if (PORTB.RB1 == 0 && vagas > 0) {
      processoCompleto = 0;

      AbreCancela(1);
      Lcd_out(2,1,"Veiculo entrando");

      LigaAlerta();
      
      vagas = vagas - 1;
      DesligaAlerta();
      FechaCancela(1);
    }

    // Carro saindo
    if (PORTB.RB2 == 0 && vagas < max_vagas){
      processoCompleto = 0;

      AbreCancela(2);
      Lcd_out(2,1,"Veiculo saindo");

      LigaAlerta();

      vagas = vagas + 1;
      DesligaAlerta();
      FechaCancela(2);
    }
  }
}
