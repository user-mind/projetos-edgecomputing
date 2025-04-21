const int LDR= A0;
const int buzzer= 2;
const int green= 5;
const int yellow= 6 ;
const int red= 7;
//luminosidade(mudar valores depois se achar9valores ficticios
const int lumOK= 300;
const int lumMIN= 600;
const int lumALERT= 800;
//armazenar valor LDR
int luminosidade;

//variaveis do buzzer-conseguir definir dps 
//quando ativa e desativa

bool alarme =false; //bool- para definir se é true or false
unsigned long tempoUltimoBuzzer = 0;// tempo do ultimo toque
unsigned long tempbuz = 0; // tempo que o buzzer pode armazenar
const unsigned long duracaobuz= 3000;// som por 3 segundos
const unsigned long intervaloBuzzer = 2000;//tempo para ele tocar novamente



void setup()
{
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Monitoramento de luminosidade");
}

void loop()
{
  luminosidade = analogRead(LDR);
  Serial.print("Luminosidade; ");
  Serial.println(luminosidade);
  
  if (luminosidade < lumOK){
  digitalWrite(green, 1);
  digitalWrite(yellow, 0);
  digitalWrite(red, 0);
 //buzzer nao toca
  alarme =false;
  noTone(buzzer);
  tempbuz= 0;
  }else if(luminosidade >=lumMIN && luminosidade <= lumALERT ){
    digitalWrite(green, 0);
    digitalWrite(yellow, 1);
    digitalWrite(red, 0);
 //buzzer toca
    alarme= true;
    unsigned long tempbuz = millis();
    if (tempbuz - tempoUltimoBuzzer >= duracaobuz + intervaloBuzzer || tempoUltimoBuzzer == 0) {
      tocarBuzzer(duracaobuz);
      tempoUltimoBuzzer = tempbuz;
    }
  }else{
    digitalWrite(green, 0);
    digitalWrite(yellow, 0);
    digitalWrite(red, 1);
//buzzer nao toca
    alarme =false;
    noTone(buzzer);
    tempbuz= 0;
  }
  delay(1000);
}

void tocarBuzzer(unsigned long duracao) {
 //emiti som de 100 Hz(deixei esse valor, pra nao ficar tao agudo
  tone(buzzer, 100); 
  delay(duracao);
  noTone(buzzer);    
}


//Explicação do "bool" e "unsigned long"
//bool:
//Uma variável bool pode ter apenas dois valores: true (1) ou false (0). 
//É usada para representar condições ou estados lógicos. 
//Por exemplo, pode-se usar um bool para indicar 
//se um sensor está ativado ou desativado. 

//unsigned long:
//Adicionado antes de um tipo de dado inteiro (int, long, byte), 
//indica que a variável só pode armazenar valores positivos 
//(0 ou maior). Por exemplo, unsigned long armazenará 
//valores de 0 a 4.294.967.295. void setup() {
  // put your setup code here, to run once:

}


