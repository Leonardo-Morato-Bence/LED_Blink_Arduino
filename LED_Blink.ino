/*  Este codigo visa demonstrar um metodo de piscar um LED utilizando os registradores para controlar os GPIOs 
 * e o timer 1, assim como regular ele para o uso desejado e tratar a interrupção gerada pelo estouro dele. 
 *  Este codigo foi feito para ser utilizado no microcontrolador ATmega328P (Arduino Nano) na IDE Arduino.
 *  
 *  Informações a serem considerados: 
 *    período do clock - 62,5nS
 *    espaço de armazenamento de programas previsto - 530 bytes
 *    memória dinâmica prevista - 9 bytes
 */

void setup() {

  DDRB |= (1<<DDB5); //Define a porta D5 como saída (pino 13)
  PORTB &= (0<<PORTB5); //Inicia a porta D5 em nivel logico 0

  noInterrupts(); //Desabilita interrupções
  TCCR1A = 0x00; //Operar o timer no modo normal
  TCCR1B = 0x05; //Define o prescaler (atraso) do timer em 1024 ciclos de clock
  TCNT1 = 49911; //Valor inicial do Timer1
  
  //Tempo de contagem = 62,5nS x 1024 x (65536-49911) = 1S
 
  TIMSK1 = 0x01; //Interrupção do estouro do timer habilitada
  interrupts(); //Habilita interrupções globais
}

ISR(TIMER1_OVF_vect) //Quando o timer estourar o seguinte será executado
{
  TCNT1 = 49911; //Carrega novamente o valor inicial no timer
  PORTB ^= (1<<PORTB5); //Inverte o nivel lógico da porta (pino 13)
}

void loop() {

}
