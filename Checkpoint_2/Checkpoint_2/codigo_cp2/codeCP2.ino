#include <DHT.h>  // Biblioteca para o sensor DHT11

// #include <numeric> // Para usar std::accumulate

#define DHTPIN 3      
#define DHTTYPE DHT11  

// ------Se o Display for com o I2C
#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

DHT dht(DHTPIN, DHTTYPE);  

const int LDR = A0;
const int buzzer = 2;
const int green = 5;
const int yellow = 6;
const int red = 7;


const int lumOK = 350;
const int lumALERT = 800;


const int tempMIN = 10;
const int tempMAX = 15;
const int umidMIN = 50;
const int umidMAX = 70;

// Arrays para armazenar as últimas 5 leituras
int leiturasLDR[5] = {0};
int leiturasTemp[5] = {0};
int leiturasUmid[5] = {0};
int indice = 0;

unsigned long tempoUltimaMensagem = 0;
unsigned long tempoUltimaLeitura = 0;
unsigned long tempoUltimaExibicao = 0;

const unsigned long intervaloMensagem = 1000;
const unsigned long intervaloLeitura = 1000; 
const unsigned long intervaloExibicao = 5000;
const unsigned long duracaoMensagem = 2500;

bool buzzerAtivo = false;

void setup() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600); 
  dht.begin();

  lcd.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear(); // Serve para limpar a tela do display        
}

void loop() {
  unsigned long agora = millis();
  int mediaLDR = 0;
  float mediaTemp = 0;
  int mediaUmid = 0;
  int estado = 0; 
  int leituraLDR = analogRead(LDR);
  leituraLDR = map(leituraLDR, 0, 1023, 140, 970); 
  float temp = dht.readTemperature();
  int umid = dht.readHumidity();

  //Inicia o codigo já tirando as medias dos valores
  if (agora - tempoUltimaLeitura < intervaloLeitura) {
      return;
  }
  tempoUltimaLeitura = agora;
  //Caso tenha algum erro na leitura dos valores
  if (isnan(temp) || isnan(umid)) {
    Serial.println("Erro na leitura do DHT11");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print ("Erro na leitura do DHT11");
    return;
  }

  leiturasLDR[indice] = leituraLDR;
  leiturasTemp[indice] = temp;
  leiturasUmid[indice] = umid;
  indice = (indice + 1) % 5; 

  // Calcular soma e média:
  int somaLDR = 0;
  float somaTemp = 0;
  int somaUmid = 0;
  for (int i = 0; i < 5; i++) {
    somaLDR += leiturasLDR[i];
    somaTemp += leiturasTemp[i];
    somaUmid += leiturasUmid[i];
  }

  mediaLDR = somaLDR / 5;
  mediaTemp = somaTemp / 5.0;  
  mediaUmid = somaUmid / 5;

	
  if ( agora - tempoUltimaExibicao < intervaloExibicao) {
    return;
  }
    
  tempoUltimaExibicao = agora;
  Serial.print("Temperatura: "); Serial.println(mediaTemp);
  Serial.print("Umidade: "); Serial.println(mediaUmid);
  Serial.print("Luminosidade:"); Serial.println(mediaLDR); 


  //Atenção

  if (mediaLDR >= lumALERT) {
    estado = 2;
    escreveNaTela("Ambiente Muito", "Claro");
  } 
  if (mediaUmid < umidMIN) {
    estado = 2;
    escreveNaTela("Umidade Alta", "Umidade ="+String(mediaUmid)+"%");
  }
  if (mediaUmid > umidMAX) {
    estado = 2;
    escreveNaTela("Umidade Alta", "Umidade ="+String(mediaUmid)+"%");
  }

  // Alerta
  if (mediaLDR > lumOK && mediaLDR < lumALERT){
    estado = 1;
    escreveNaTela("Ambiente a meia", "luz");
  }
  if (mediaTemp < tempMIN) {
    estado = 1;
    escreveNaTela("Temp Baixa", "Temp. ="+String(mediaTemp)+"C");
  }
  if (mediaTemp > tempMAX) {
    estado = 1; 
    escreveNaTela("Temp Alta", "Temp. ="+String(mediaTemp)+"C");
  }

  // OK
  else{
    estado = 0;
    
    if((agora - tempoUltimaMensagem) > (intervaloMensagem + duracaoMensagem)){

    //lista de mensagens a serem exibidas quando estiver tudo ok
        String mensagem[] = {"Luminosidade OK", "Temperatura OK", "Umidade OK"};
        String valores[] = {String(mediaLDR), String(mediaTemp) +" C", String(mediaUmid)+"%"};

      for(int i = 0; i < 3; i++ ){
        escreveNaTela(mensagem[i], valores[i]);
        indice = (indice + 1) / 3;
        delay(1000);
      }
    }
    tempoUltimaMensagem = agora;
  }  
  defineEstado(estado);  
}


void escreveNaTela(String linha1, String linha2) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(linha1);
    lcd.setCursor(0,1);
    lcd.print(linha2);
}

void defineEstado(int estado) {
  switch (estado) {
      case 0: // OK
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);
        noTone(buzzer);
        break;
      case 1: // Atenção
        digitalWrite(red, LOW);
        digitalWrite(yellow, HIGH);
        digitalWrite(green, LOW);
        tone(buzzer, 550); 
        buzzerAtivo = true;   
        break;
      
      case 2: // Alerta 
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
        tone(buzzer, 1000);
        buzzerAtivo = true; 
        break;

  }
}
