// Código V2.1.0 por Cássio K. Ferreira 

#include <SPI.h>
#include <Ethernet.h>
#include <DS1307.h>

DS1307 rtc(A4, A5); //Pinos do modulo de tempo
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 15 };
 
#define BUFFER 10
EthernetServer servidorArduino(3200); //Porta

//#define lumino 400  //Valor de luminosidade máximo que o sensor de presença vai funcionar
 
int estadosw1;
int estadosw2;
int estadosw3;
int estadosw4;
int estadosw5;

float temperature;

const int psw1 = 7;  //
const int psw2 = 6;  //
const int psw3 = 5;  // Nomeando as Portas de saida para rele, pino switch x
const int psw4 = 3;  //
const int psw5 = 2;  //
const int ros = 44;  // switch para desligar todas as lampadas ao resetar

//const int pqc = 47;  // Pino indicador conectado do quadro

const int pL1 = 34;  //
const int pL2 = 32;  //
const int pL3 = 30;  // Nomeando as entradas Lx
const int pL4 = 28;  //
const int pL5 = 26;  //
 
//const int PIR = 22;  // Sensor de Presença
// const int LDR = A0;  // Sensor de luminosidade
const int LM35 = A1; // Sensor de temperatura

void setup(){

  rtc.halt(false);

  //rtc.setDOW(MONDAY);      //Define o dia da semana
  //rtc.setTime(20, 56, 0);     //Define o horario
  //rtc.setDate(7, 12, 2015);   //Define o dia, mes e ano

  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  
  Serial.begin(9600);
  delay(10000);
  Ethernet.begin(mac, ip);
  servidorArduino.begin();

  pinMode(53, OUTPUT); // isso é pro ethernet shield funfa no Mega NÃO REMOVER!!
  pinMode(psw1, OUTPUT);  //sw1
  pinMode(psw2, OUTPUT);  //sw2
  pinMode(psw3, OUTPUT);  //sw3
  pinMode(psw4, OUTPUT);  //sw4
  pinMode(psw5, OUTPUT);  //sw5
  //pinMode(pqc, OUTPUT);
  pinMode(ros, INPUT);  // desligar Lx no reset
  pinMode(pL1, INPUT);  //L1
  pinMode(pL2, INPUT);  //L2
  pinMode(pL3, INPUT);  //L3
  pinMode(pL4, INPUT);  //L4
  pinMode(pL5, INPUT);  //L5
  pinMode(LM35, INPUT); //Sensor temp   
  //pinMode(PIR, INPUT);  //Sensor Presença PIR
 // pinMode(LDR, INPUT);  //Sendor Luminosidade LDR

  //digitalWrite(pqc, LOW);  // Indicador de conectado do quadro
 
    if (digitalRead(ros) == HIGH) {   //
                                      //
  if (digitalRead(pL1) == HIGH) {     //
    if (digitalRead(psw1) == HIGH){   //
      digitalWrite(psw1, LOW);}       //
    else{                             //
      digitalWrite(psw1, HIGH);}      //
  }                                   //
  if (digitalRead(pL2) == HIGH) {     //
    if (digitalRead(psw2) == HIGH){   //
      digitalWrite(psw2, LOW);}       //
    else{                             //
      digitalWrite(psw2, HIGH);}      //
  }                                   //   Segurança para não deichar acesa
  if (digitalRead(pL3) == HIGH) {     // a luz quando acabar a energia ou o arduino
    if (digitalRead(psw3) == HIGH){   // resetar
      digitalWrite(psw3, LOW);}       //
    else{                             //
      digitalWrite(psw3, HIGH);}      //
  }                                   //
  if (digitalRead(pL4) == HIGH) {     //
    if (digitalRead(psw4) == HIGH){   //
      digitalWrite(psw4, LOW);}       //
    else{                             //
      digitalWrite(psw4, HIGH);}      //
  }                                   //
  if (digitalRead(pL5) == HIGH) {     //
    if (digitalRead(psw5) == HIGH){   //
      digitalWrite(psw5, LOW);}       //
    else{                             //
      digitalWrite(psw5, HIGH);}      //
  }                                   //
 }                                    //
    
}

void loop() {
    
  estadosw1 = digitalRead(psw1);  //
  estadosw2 = digitalRead(psw2);  //
  estadosw3 = digitalRead(psw3);  //  Para identificar o estado do rele e trocar conforme swx
  estadosw4 = digitalRead(psw4);  //
  estadosw5 = digitalRead(psw5);  //
  
  //int sensorpir = digitalRead(PIR);    // Variaveis
 // int sensorlumino = analogRead(LDR);  //

  int index = 0;
  char comando[BUFFER];
  
  EthernetClient clienteApp = servidorArduino.available();
  if (clienteApp) {
    if (clienteApp.connected()) {
        while (clienteApp.available()) {
          //digitalWrite(pqc, HIGH);
          char caracter = clienteApp.read();
          if (caracter != '\n') {
            comando[index] = caracter;
            index++;
            if (index >= BUFFER) 
              index = BUFFER -1;
            continue;
          }
          comando[index] = '\0';
        }

      //Serial.println(comando);
       //Serial.print("Hora : ");
 	   //Serial.print(rtc.getTimeStr());
       //Serial.print(" ");
	   //Serial.print("Data : ");
       //Serial.print(rtc.getDateStr());
       //Serial.print(" ");
       //Serial.println(rtc.getDOWStr());
       //Serial.print("Temperatura: ");
       //Serial.print(temperature);
       //Serial.println(" °C"); 

      if (strstr(comando, "Conectado")) {
        clienteApp.println("Esta Conectado");
        Serial.println("Controle conectado");
      }

      if (strstr(comando, "temp1")) {
        Serial.println("Recebido temp1");
        temperature = (float(analogRead(LM35))*5/(1023))/0.01;
        clienteApp.println(temperature);
      }

      if (strstr(comando, "time")) {
      	clienteApp.println(rtc.getTimeStr());
      }

      if (strstr(comando, "date")) {
      	clienteApp.println(rtc.getDateStr());
      }

      if (strstr(comando, "week")) {
      	clienteApp.println(rtc.getDOWStr());
      }

      //---------------
      // Começo do sw1
      //---------------
      if (strstr(comando, "sw1")) {
        Serial.println("Recebido sw1");
            if (estadosw1 == LOW){
              digitalWrite(psw1, HIGH);}              
            if (estadosw1 == HIGH){
              digitalWrite(psw1, LOW);}
      }
      if (strstr(comando, "L1")) {
        if (digitalRead(pL1) == HIGH) {   
          clienteApp.println("L1on");} 
        else {
          clienteApp.println("L1off");
        }
      }
      //--------------
      // Fim do sw1
      //--------------

      //---------------
      // Começo do sw2
      //---------------
      if (strstr(comando, "sw2")) {
        Serial.println("Recebido sw2");
            if (estadosw2 == LOW){
              digitalWrite(psw2, HIGH);}              
            if (estadosw2 == HIGH){
              digitalWrite(psw2, LOW);}
      }
      if (strstr(comando, "L2")) {
        if (digitalRead(pL2) == HIGH) {   
          clienteApp.println("L2on");} 
        else {
          clienteApp.println("L2off");
        }
      }
      //--------------
      // Fim do sw2
      //--------------

      //---------------
      // Começo do sw3
      //---------------
      if (strstr(comando, "sw3")) {
        Serial.println("Recebido sw3");
            if (estadosw3 == LOW){
              digitalWrite(psw3, HIGH);}              
            if (estadosw3 == HIGH){
              digitalWrite(psw3, LOW);}
      }
      if (strstr(comando, "L3")) {
        if (digitalRead(pL3) == HIGH) {   
          clienteApp.println("L3on");} 
        else {
          clienteApp.println("L3off");
        }
      }
      //--------------
      // Fim do sw3
      //--------------

      //---------------
      // Começo do sw4
      //---------------
      if (strstr(comando, "sw4")) {
        Serial.println("Recebido sw4");
            if (estadosw4 == LOW){
              digitalWrite(psw4, HIGH);}              
            if (estadosw4 == HIGH){
              digitalWrite(psw4, LOW);}
      }
      if (strstr(comando, "L4")) {
        if (digitalRead(pL4) == HIGH) {   
          clienteApp.println("L4on");} 
        else {
          clienteApp.println("L4off");
        }
      }
      //--------------
      // Fim do sw4
      //--------------

      //---------------------
      // Começo do sw5 Patio
      //---------------------
      if (strstr(comando, "sw5")) {
        Serial.println("Recebido sw5");
        if (estadosw5 == LOW){
            digitalWrite(psw5, HIGH);}
        if (estadosw5 == HIGH){
              digitalWrite(psw5, LOW);}
      }
      //if(sensorlumino < lumino) {
      //  if(sensorpir == HIGH){
      //      digitalWrite(psw5, HIGH);
      //      delay(15000);}
      //}
      if (strstr(comando, "L5")) {
        if (digitalRead(pL5) == HIGH) {   
          clienteApp.println("L5on");} 
        else {
          clienteApp.println("L5off");
        }
      }
      //--------------
      // Fim do sw5
      //--------------

      //else {
        //clienteApp.println("unknown_command");
        //Serial.println("Comando desconhecido");
      //}
    }
  }
}