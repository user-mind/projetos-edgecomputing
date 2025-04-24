const int LDR = A0;
const int buzzer = 2;
const int green = 5;
const int yellow = 6;
const int red = 7;

const int lumOK = 800;
const int lumMIN = 600;
const int lumALERT = 450;

int luminosidade;

bool alarme = false;
bool buzzerAmareloAtivo = false;
bool buzzerVermelhoAtivo = false;

unsigned long tempoUltimoBuzzer = 0;
unsigned long tempoInicioBuzzerAmarelo = 0;
unsigned long tempoInicioBuzzerVermelho = 0;
unsigned long tempoUltimaLeitura = 0;  // Variável para controlar a leitura do LDR

const unsigned long duracaoBuzzerAmarelo = 3000; 
const unsigned long duracaoBuzzerVermelho = 1000; 
const unsigned long intervaloBuzzerAmarelo = 1000; 
const unsigned long intervaloBuzzerVermelho = 500; 
const unsigned long intervaloLeituraLDR = 1000; 

void setup() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  Serial.println("Monitoramento de luminosidade");
}

void loop() {
  unsigned long agora = millis();

  // Ler o LDR a cada 1 segundo
  if (agora - tempoUltimaLeitura >= intervaloLeituraLDR) {
    tempoUltimaLeitura = agora;  // Atualiza o tempo da última leitura
    luminosidade = analogRead(LDR);
    Serial.print("Luminosidade: ");
    Serial.println(luminosidade);
  }

  if (luminosidade >= lumOK) {
    digitalWrite(green, 1);
    digitalWrite(yellow, 0);
    digitalWrite(red, 0);
    alarme = false;
    noTone(buzzer);  // Para o buzzer
    buzzerAmareloAtivo = false;
    buzzerVermelhoAtivo = false;
    tempoUltimoBuzzer = 0;

  } else if (luminosidade >= lumMIN && luminosidade < lumOK) {
    digitalWrite(green, 0);
    digitalWrite(yellow, 1);
    digitalWrite(red, 0);
    alarme = true;
    buzzerVermelhoAtivo = false;  // Não ativa o buzzer vermelho

    if (!buzzerAmareloAtivo && (agora - tempoUltimoBuzzer >= intervaloBuzzerAmarelo || tempoUltimoBuzzer == 0)) {
      tone(buzzer, 550);  // Toca o buzzer com frequência menor para o amarelo
      tempoInicioBuzzerAmarelo = agora;
      buzzerAmareloAtivo = true;
    }

    if (buzzerAmareloAtivo && (agora - tempoInicioBuzzerAmarelo >= duracaoBuzzerAmarelo)) {
      noTone(buzzer);  // Para o som após a duração do buzzer
      buzzerAmareloAtivo = false;
      tempoUltimoBuzzer = agora;  // Atualiza o tempo do último toque
    }

  } else {
    digitalWrite(green, 0);
    digitalWrite(yellow, 0);
    digitalWrite(red, 1);
    alarme = true;
    buzzerAmareloAtivo = false;  // Não ativa o buzzer amarelo

    if (!buzzerVermelhoAtivo && (agora - tempoUltimoBuzzer >= intervaloBuzzerVermelho || tempoUltimoBuzzer == 0)) {
      tone(buzzer, 1000);  // Toca o buzzer com frequência maior para o vermelho
      tempoInicioBuzzerVermelho = agora;
      buzzerVermelhoAtivo = true;
    }

    if (buzzerVermelhoAtivo && (agora - tempoInicioBuzzerVermelho >= duracaoBuzzerVermelho)) {
      noTone(buzzer);  // Para o som após a duração do buzzer
      buzzerVermelhoAtivo = false;
      tempoUltimoBuzzer = agora;  // Atualiza o tempo do último toque
    }
  }
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

//O operador de negação lógico (!) inverte o significado do respectivo operando. O operando deve ser do tipo aritmético ou ponteiro (ou uma expressão que é avaliada para o tipo aritmético ou ponteiro). O operando é convertido implicitamente no tipo bool. O resultado será true se o operando convertido for false; o resultado será false se o operando convertido for true. O resultado é do tipo bool.

   