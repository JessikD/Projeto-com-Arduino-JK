#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306();

#define DHTTYPE DHT11                      //Definição do sensor utilizado DHT11
#define pinoSensorT 2                     //Pino analógico do sensor DHT11
const int botaoPassar = 3;              
const int botaoOk = 4;
const int valor_maximo = 1023;
const int valor_minimo = 220;

int estadoOk;                 //Selecionar no menu principal
int estadoBotaoPassar;        //Passar as opções no menu principal 
int cont;                     //Variável do menu principal
int ok = 0;                   //Variável do menu principal

DHT_Unified dht(pinoSensorT, DHTTYPE);    //Configuração do sensor (pino, tipo)



void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                      //Inicializa o display
  dht.begin();
  pinMode(A0, INPUT);                                             //Pino do sensor de umidade do solo
  pinMode(botaoPassar, INPUT_PULLUP);
  pinMode(botaoOk, INPUT_PULLUP);
  cont = 1;
  ok = 0;

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  
}

float temperatura(){
  sensors_event_t event;                  //Inicialização do evento da temperatura
  dht.temperature().getEvent(&event);
  
  float valorTemp;
  float erro;

  if(isnan(event.temperature) ){
    erro = -999;
    return erro;
  }else{
    valorTemp = event.temperature;

    return valorTemp;
  }
  
}

void umidadeAr(){
  sensors_event_t event;
  dht.humidity().getEvent(&event);

  if(isnan(event.relative_humidity) ){
    display.setTextSize(1);  
    display.setCursor(1, 1);
    display.println("Erro na leitura (U)");
    display.display();
    delay(1000);
    display.clearDisplay();      
  }
  else{
    display.setTextSize(1);
    display.setCursor(1,1);
    display.println("Umidade do ar: ");
    display.print(event.relative_humidity);
    display.println("%");
    display.display();
    delay(1000);
    display.clearDisplay();
  }
  
}

float umidadeSolo(){
  int solo;
  solo = analogRead(A0);
  float porcentagemSolo;

  porcentagemSolo = map(solo, valor_minimo, valor_maximo,100,0);

  //seco (solo >= 400)
  //umido (solo < 400) & (solo > 240))
  return porcentagemSolo;
  
}

void subMenu(int contSubOp, int okSubOp){
  //Sub menu 1 tomate
      if((contSubOp == 1) & (okSubOp == 0) ){
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(1,1);
        display.println("Tomateiro (x)");
        display.println("Maracujazeiro");
        display.display();
        delay(1000);
        display.clearDisplay();
      }

      //Sub menu 2 Maracujá
      if((contSubOp == 2) & (okSubOp == 0)){
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(1,1);
        display.println("Tomateiro");
        display.println("Maracujazeiro (x)");
        display.display();
        delay(1000);
        display.clearDisplay();
      }
      if((contSubOp == 2) & (okSubOp == 1)){
        planta(contSubOp);
      }
}

void planta(int contSubOp){
  float solo;
  float temp;
  temp = temperatura();

  //Sub menu 1
  if(contSubOp == 1){
    solo = umidadeSolo();  
    //solo
    if(solo < 68 & solo > 46){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Umidade do solo");
        display.println("Ideal para tomate");
        display.print(solo);
        display.println(" %");
        display.display();
        delay(1000);
        display.clearDisplay();
    }else{
      if(solo >= 68){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Solo muito umido");
        display.println("para tomate");
        display.print(solo);
        display.println(" %");
        display.display();
        delay(1000);
        display.clearDisplay();
      }else{
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Solo muito seco");
        display.println("para tomate");
        display.print(solo);
        display.println(" %");
        display.display();
        delay(1000);
        display.clearDisplay();
      }
    }
    //temperatura  
    if((temp == -999)){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Erro na leitura (T)");
        display.display();
        delay(1000);
        display.clearDisplay();
    }else{
      if((temp < 29) & (temp > 15) ){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Temperatura");
        display.println("Ideal para tomate");
        display.print(temperatura());
        display.print(" ");
        display.write(9);
        display.println("C");
        display.display();
        delay(1000);
        display.clearDisplay();    
      }else{
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Temperatura");
        display.println("Nao e ideal");
        display.println("para tomate");
        display.print(temperatura());
        display.print(" ");
        display.write(9);
        display.println("C");
        display.display();
        delay(1000);
        display.clearDisplay();
      }
      
    }
    
  }//FIM MENU 1


  //Sub menu 2
  if(contSubOp == 2){
    solo = umidadeSolo();  
    //solo
    if(solo < 65 & solo > 48){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Umidade do solo");
        display.println("Ideal para maracuja");
        display.print(solo);
        display.println(" %");
        display.display();
        delay(1000);
        display.clearDisplay();
    }else{
      if(solo >= 65){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Solo muito umido");
        display.println("para maracuja");
        display.print(solo);
        display.println(" %");
        display.display();
        delay(1000);
        display.clearDisplay();
      }else{
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Solo muito seco");
        display.println("para maracuja");
        display.print(solo);
        display.println(" %");
        display.display();
        delay(1000);
        display.clearDisplay();
      }
    }
    //temperatura  
    if((temp == -999)){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Erro na leitura (T)");
        display.display();
        delay(1000);
        display.clearDisplay();
    }else{
      if((temp < 28) & (temp > 14) ){
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Temperatura");
        display.println("Ideal para maracuja");
        display.print(temperatura());
        display.print(" ");
        display.write(9);
        display.println("C");
        display.display();
        delay(1000);
        display.clearDisplay();    
      }else{
        display.setTextSize(1);
        display.setCursor(1,1);
        display.println("Temperatura");
        display.println("Nao e ideal");
        display.println("para maracuja");
        display.print(temperatura());
        display.print(" ");
        display.write(9);
        display.println("C");
        display.display();
        delay(1000);
        display.clearDisplay();
      }
      
    }
         
  }
    
}//FIM MENU 2


void loop() {
  // put your main code here, to run repeatedly:
  //bool menu = true;
  
  float temp;
  estadoBotaoPassar = digitalRead(botaoPassar);
  estadoOk = digitalRead(botaoOk);

  if(estadoBotaoPassar == LOW ){
    if (cont < 6){
      cont = cont + 1;
    } else{
        cont = 0;
    }
  }
  if(estadoOk == LOW){
    if(ok < 2){
      ok = ok + 1;
    }else{
      ok = 0;
    }
  }
    
    //MENU 1 Umidade do solo
    if(cont == 1 & ok == 0){
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(1,1);
      display.println("Umidade do solo (x)");
      display.println("Temperatura");
      display.println("Umidade do ar");
      display.display();
      delay(800);
      display.clearDisplay();
    }
    if (cont == 1 & ok == 1){          //chamar função
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(1,1);
        display.println("Umidade do solo de ");
        display.print(umidadeSolo());
        display.println(" %");
        display.display();
        delay(1000);
        display.clearDisplay();
    }//FIM menu 1
      

    //MENU 2 Temperatura
    if(cont == 2 & ok == 0){
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(1,1);
      display.println("Umidade do solo");
      display.println("Temperatura (x)");
      display.println("Umidade do ar");
      display.display();
      delay(800);
      display.clearDisplay();
    }
    if (cont == 2 & ok == 1){          //chamar função
        temp = temperatura();
        if(temp == -999 ){
          display.setTextSize(1);
          display.setCursor(1,1);
          display.println("Erro na leitura (T)");
          display.display();
          delay(1000);
          display.clearDisplay();
        }
        else{
          display.setTextSize(1);
          display.setCursor(1,1);
          display.print("Temperatura: ");
          display.print(temp);
          display.print(" ");
          display.write(9);
          display.println("C");
          display.display();
          delay(1000);
          display.clearDisplay();
      
        }
    }//FIM menu 2
      
    
    //MENU 3 Umidade do ar
    if(cont == 3 & ok == 0){
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(1,1);
      display.println("Umidade do solo");
      display.println("Temperatura");
      display.println("Umidade do ar (x)");
      display.display();
      delay(800);
      display.clearDisplay();
    }
    if (cont == 3 & ok == 1){          //chamar função
      umidadeAr();
    }

    if (cont == 4 & ok == 0){
      subMenu(1, 0);
    }
    if (cont == 4 & ok == 1){
      planta(1);
    }
    if (cont == 5 & ok == 0){
      subMenu(2, 0);
    }
    if (cont == 5 & ok == 1){
      subMenu(2, 1);
    }
      
      
}
