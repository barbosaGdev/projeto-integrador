#include <Keypad.h> //INCLUSÃO DE BIBLIOTECA

//Programa: Teste de Display LCD 16 x 2
//Autor: FILIPEFLOP
 
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
 
 
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 4; //QUANTIDADE DE COLUNAS DO TECLADO
 
//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
 
byte PinosqtdLinhas[qtdLinhas] = {5, 4, 3, 2}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {11, 10, 9,8}; //PINOS UTILIZADOS PELAS COLUNAS
 
//INICIALIZAÇÃO DO TECLADO
Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas); 
String senha;
boolean status = false;

void setup() 
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  
  //Sensor PIR
  pinMode(12, INPUT);
  //Alarme
  pinMode(7, OUTPUT);
  //Colocamos o pino 1 do Arduino como OUTPUT (saída)
  pinMode(1, OUTPUT);
}

// Este código é chamado automáticamente pelo Arduino, ficará em
// loop até que seu Arduino seja desligado
void loop(){
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("'#' criar senha");
  lcd.setCursor(0, 1);
  lcd.print("'A' para ativar");
  //delay(5000);
   
  //Rolagem para a esquerda
  //for (int posicao = 0; posicao < 3; posicao++)
  //{
    //lcd.scrollDisplayLeft();
    //delay(300);
  //}
  
  char tecla_pressionada = meuteclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA

   
 if (tecla_pressionada == '#'){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Crie a chave: ");
      senha = "";
      while(true) {
        char digito = meuteclado.getKey();
        if (digito){
          lcd.setCursor(senha.length(),1);
          lcd.print("*");
          senha += digito;
        }
        if (senha.length() >= 6) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Feito!");
          break;
        }
     if (digito == '#') {
         senha = "";
          break;
        }
      }
    }

     if (tecla_pressionada == 'A') {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Digite a senha:");
      String temp;
      while (true) {
        char digito = meuteclado.getKey();
     if (digito) {
          lcd.setCursor(temp.length(),1);
          lcd.print("*");
          temp += digito;
       }
       if (temp.length() >= 6) {
        if (temp == senha) {
          bool sensorPIR = digitalRead(12);
          bool detectou;
          if (sensorPIR) {
              digitalWrite(1, HIGH);
              tone(7, 200); 
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Desativar alarme:");
                String temp2;
                 while(true){
                char digito = meuteclado.getKey();
                  if (digito) {
                   lcd.setCursor(temp2.length(),1);
                   lcd.print("*");
                    temp2 += digito;
                  }
                  if (temp2.length() >= 6) {
                      if (temp2 == senha) {
                   digitalWrite(1,LOW);
                   noTone(7);
                   break;
              }
               else {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Senha incorreta!");
                break;
               }
              }
  
          delay(10);
          
        }
       }
          }
       
       if (temp.length() >= 6) {
        if (temp == senha) {
                      
        } else {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Senha incorreta!");
                break;
               }
        if (digito = '*'){
          break;
        }
       }
      }
    }

      }
}
