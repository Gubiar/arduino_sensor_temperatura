#include <DallasTemperature.h>
#include <OneWire.h>
#include <time.h>

#define ONE_WIRE_BUS 9

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long previousMillis;
unsigned long interval=1;
int timer_segments;
int timer_contagem;
int Estado_segments;
int temp_uni;
int temp_dez;
int erro;
int valorresis;


float temperatura;



void setup() {
  // put your setup code here, to run once:
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  
}

void base_tempo (){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (timer_segments!=0){
      timer_segments--;
    }
    if (timer_contagem!=0){
      timer_contagem--;
    }
  }
}

int disp_seg[10][7]={
//{1,0,6,4,5,2,3}  
//{a,b,c,d,e,f,g}
  {1,1,1,1,1,1,0}, 
  {0,1,1,0,0,0,0}, 
  {1,1,0,1,1,0,1}, 
  {1,1,1,1,0,0,1}, 
  {0,1,1,0,0,1,1}, 
  {1,0,1,1,0,1,1}, 
  {0,0,1,1,1,1,1}, 
  {1,1,1,0,0,0,0}, 
  {1,1,1,1,1,1,1}, 
  {1,1,1,1,0,1,1} 
};

void tic_display(){
  switch(Estado_segments){
    case 0:
      Estado_segments=1;
      break;
    case 1:
      if (timer_segments==0){
        timer_segments=5;
        digitalWrite(14,disp_seg[temp_dez][1]);
        digitalWrite(15,disp_seg[temp_dez][0]);
        digitalWrite(2,disp_seg[temp_dez][5]);
        digitalWrite(3,disp_seg[temp_dez][6]);
        digitalWrite(4,disp_seg[temp_dez][3]);
        digitalWrite(5,disp_seg[temp_dez][4]);
        digitalWrite(6,disp_seg[temp_dez][2]);
        //PORTA DE CONTROLE 
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        Estado_segments=2;
      }
      break;
    case 2:
      if (timer_segments==0){
        timer_segments=5;
        digitalWrite(14,disp_seg[temp_uni][1]);
        digitalWrite(15,disp_seg[temp_uni][0]);
        digitalWrite(2,disp_seg[temp_uni][5]);
        digitalWrite(3,disp_seg[temp_uni][6]);
        digitalWrite(4,disp_seg[temp_uni][3]);
        digitalWrite(5,disp_seg[temp_uni][4]);
        digitalWrite(6,disp_seg[temp_uni][2]);
        //PORTA DE CONTROLE 
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        Estado_segments=1;
      }
    }
  }

void tic_contagem(){
  
  temperatura = sensors.getTempCByIndex(0);

  temp_dez = (int)temperatura/10;
  temp_uni = (int)temperatura%10;

 
  erro = 80 - temperatura;
  valorresis = 10*erro;

  if (valorresis > 255){
    valorresis = 255;
  }else if (valorresis <0){
    valorresis = 0;;
  }

  analogWrite(12,valorresis);

  
  
////  if(timer_contagem==0){
////    timer_contagem=1000;
////    temp_uni++;
////    if(temp_uni==10){
////      temp_dez++;
//      temp_uni=7;
////      if(temp_dez==10){
//        temp_dez=0;
////      }
////    }
////  }
}
  

void loop() {
  sensors.requestTemperatures(); 
  base_tempo();
  tic_display();
  tic_contagem();
  Serial.print("temperatura:");  
  Serial.print(temperatura);
  Serial.print(" valorresis:");
  Serial.println(valorresis);
//  Serial.println(";");

}
