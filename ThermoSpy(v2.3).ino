/***********************************************************************************************************************************************************************************
**                                                                                 -THERMOSPY-                                                                                    **
**                                                                                                                                                                                **
**   SENCILLO CODIGO PARA MOSTRAR VALORES AMBIENTALES EN PANTALLAS OLED (0,96" EN V1.0):                                                                                          **
**          -V1.0(HASTA 12/08/2025): SE MUESTRAN VALORES DE NIVEL DE BATERIA (%), TIEMPO EN USO Y TEMPERATURA AMBIENTE MEDIANTE SENSOR DS18B20                                    **
**          -V2.0(DESDE 12/08/2025): SE SUSTITUYE EL SENSOR DS18B20 POR UN BME280 PARA PODER MOSTRAR POR PANTALLA TEMPERATURA, HUMEDAD Y ALTITUD.                                 **
**                                   SE AÑADE TAMBIEN LA FECHA DE COMPILACION DEL CODIGO EN EL ARRANQUE                                                                           **
**          -V2.1(DESDE 15/08/2025): SE MEJORA EL CODIGO PUDIENDO ELEGIR ENTRE DOS TIPOS DE PANTALLA, HAY QUE DEFINIR LA QUE SE UTILIZA EN LAS LINEAS 29 Y/O 30                   **
**          -V2.2(DESDE 24/08/2025): SE VUELVE A MEJORAR EL CODIGO PUDIENDO ELEGIR ENTRE LAS DOS PANTALLAS(SSD1306 Y SSH1106) Y ENTRE LOS DOS SENSORES (DS18B20 Y BME280)         **
**          -V2.3(DESDE 27/08/2025): SE MEJORA EL CODIGO UNA VEZ MAS, SE HABILITAN "MENUS" CON DISTINTAS FUNCIONALIDADES > VISUALIZACION DEL ESTADO DEL DISPOSITIVO; VISUALIZACION **
**                                   DE TEMPERATURA ACTUAL, MAXIMA Y MINIMA; Y CREACION DE GRAFICAS DE TEMPERATURA CON DURACIONES DE 2', 15' Y 60', QUE AL FINALIZAR MUESTRAN     **
**                                   TEMPERATURA MINIMA, MAXIMA Y PROMEDIO DURANTE EL TEST                                                                                        **
**                                                                                                                                                                                **
**                                                                                                                                                                                **
**        Autor: Héctor Monroy Fuertes                                                                                                                                            **
**
*********************************************************************************************************************************************************************************/
#include <Adafruit_GFX.h>
#include <TimeLib.h>
//#include "Menus.h"
#include "Iconos.h"




#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define estadoBateria 0
#define boton_lh 4
#define boton_rh 3
#define boton_select 5

int contador;
int selector;
int columna;



//Seleccion segun pantalla a utilizar
//#define SSD1306  //Descomentar para pantallas 0,96" con controlador SSD1306
#define SH1106     //Descomentar para pantallas 1,3" con controlador SH1106

//Seleccion sensor temperatura
#define bme280
//#define ds18b20

#ifdef bme280
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BME280.h>
  Adafruit_BME280 bme;
  #define PresionNivelMar_HPA (1013.25)
  float temp;
  float tempMinima = 100; //lineas 243 a 253
  float tempMaxima;
  int humedad;
  int humedadMinima = 100;
  int humedadMaxima;
  int presion;
  int presionMinima = 1500;
  int presionMaxima;
  int altura;
  int alturaMinima = 3000;
  int alturaMaxima;
  //Variables para crear las graficas
  //Grafica temperatura
  float tempGraf; //Para almacenar las lecturas del sensor
  int mapTempGraf; //Para mapear los valores en la grafica
  float tempMinGraf = 100;
  float tempMaxGraf;
  //Grafica humedad
  int humGraf;
  int minHumGraf = 101;
  int maxHumGraf;
  int mapHumGraf;
  //Grafica presion atmosferica
  int presGraf;
  int minPresGraf = 2000;
  int maxPresGraf;
  int mapPresGraf;
  //Grafica altitud
  int altGraf;
  int minAltGraf = 3500;
  int maxAltGraf;
  int mapAltGraf;


#endif

#ifdef ds18b20
  #include <OneWire.h>
  #include <DallasTemperature.h>
  #define oneWirePin 1
  OneWire oneWireBus(oneWirePin);
  DallasTemperature sensors(&oneWireBus);
  float temp;
  float minima = 100; //lineas 243 a 253
  float maxima;
  float tempGraficas; //Para almacenar las lecturas del sensor
  int tempGrafica; //Para mapear los valores en la grafica
  float minimaGraficas = 100;
  float maximaGraficas;
    
#endif

#ifdef SSD1306
  #include <Adafruit_SSD1306.h>
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#else
  #include <Adafruit_SH110X.h>
  Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif

//Actualizar version de codigo para ambas pantallas
String versionCodigo = "v2.3";




void setup(){
  
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  pinMode(boton_lh, INPUT_PULLUP);
  pinMode(boton_rh, INPUT_PULLUP);
  pinMode(boton_select, INPUT_PULLUP);
  
  
  #ifdef bme280
  bool status;
  status = bme.begin(0x76); 
  if (!status) {
  Serial.println("Could not find a valid BME280 sensor, check wiring!");
  while (1);
  }
  #else
  sensors.begin(); //DS18B20
  #endif

  #ifdef SSD1306

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();  
  display.setTextColor(WHITE);
  display.setCursor(20, 2);
  display.setTextSize(1);
  display.print("COMPILADO EL: ");
  display.setCursor(25, 12);
  display.print(__DATE__);
  display.setCursor(40, 22);
  display.print("A LAS:");
  display.setCursor(35, 32);
  display.print(__TIME__);
  display.display();
  delay(3500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(12, 20);
  display.println("HectorCRM");
  display.setTextSize(1);
  display.setCursor(15, 36);
  display.print("ThermoSpy ");
  display.println(versionCodigo);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
  #else 
  display.begin(0x3c, true); // Address 0x3C default
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 2);
  display.setTextSize(1);
  display.print("COMPILADO EL: ");
  display.setCursor(25, 12);
  display.print(__DATE__);
  display.setCursor(40, 22);
  display.print("A LAS:");
  display.setCursor(35, 32);
  display.print(__TIME__);
  display.display();
  delay(3500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(12, 20);
  display.println("HectorCRM");
  display.setTextSize(1);
  display.setCursor(15, 36);
  display.print("ThermoSpy ");
  display.println(versionCodigo);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
  #endif
}

//Se incluyen las pestañas que hacen referencia a los sensores una vez han sido inicializados en el setup
#include "lectura_sensores.h"
#include "lectura_graficas.h"
#include "graficas.h"

void lecturaBotones() {
  bool estado_boton_lh;  
  bool estado_boton_rh;
  bool estado_boton_select;

  estado_boton_lh = digitalRead(boton_lh);
  estado_boton_rh = digitalRead(boton_rh);
  estado_boton_select = digitalRead(boton_select);
  if (estado_boton_rh == HIGH){
    contador ++;
    delay(10);
  }
  if (estado_boton_lh == HIGH){
    contador --;
    delay(10);
  }
  if (estado_boton_select == HIGH){
    selector ++;
    delay(10);
  }
}



void menuPpl(){

     int valor = analogRead(estadoBateria); // lee el valor del pin 0 del esp32
    int voltaje = map(valor, 0, 4095, 0, 1500); //Lee la tension de la batería, a 5v leería el maximo de 2,5V. Las baterias LiPo marcan 4,2V a carga completa(un 16% menos del total)
    int porcentajeCarga = map(voltaje, 1500, 1775, 0, 100);
    int horas = hour();
    int minutos = minute();
    int segundos = second();
  #ifdef SSD1306
    delay(150);
    lecturaBotones();
    Serial.print("contador: ");
    Serial.println(contador);
    Serial.print("columna: ");
    Serial.println(columna);
    display.clearDisplay();
    display.fillRoundRect(0, 0, 128, 10, 2, WHITE);
    display.setCursor(12, 1);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print("ESTADO ESP32"); //V2.2
    display.setCursor(2, 13);
    display.setTextColor(WHITE);
    display.print("NIVEL BATERIA: ");
    display.print(porcentajeCarga); //V2.2
    display.println("%");
    display.setCursor(2, 23);
    display.print("TIEMPO USO: ");
    display.print(horas);
    display.print("h");    
    display.print(minutos);
    display.print("m");
    display.print(segundos);
    display.print("s");
    display.setCursor(2, 33);
    display.print("TEMP. CPU: ");
    display.print(temperatureRead());
    display.print((char)247); //Codigo ASCII para º
    display.println("C");
    display.fillRoundRect(1, 48, 128, 12, 2, WHITE);
    display.setCursor(2, 50);
    display.setTextColor(BLACK);
    display.print("PULSA 'OK' PARA SALIR");
    display.display();
  #else
    delay(150);
    lecturaBotones();
    Serial.print("contador: ");
    Serial.println(contador);
    Serial.print("columna: ");
    Serial.println(columna);
    display.clearDisplay();
    display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
    display.setCursor(30, 1);
    display.setTextSize(1);
    display.setTextColor(SH110X_BLACK);
    display.print("ESTADO ESP32"); //V2.2
    display.setCursor(2, 13);
    display.setTextColor(SH110X_WHITE);
    display.print("NIVEL BATERIA: ");
    display.print(porcentajeCarga); //V2.2
    display.println("%");
    display.setCursor(2, 23);
    display.print("TIEMPO USO: ");
    display.print(horas);
    display.print("h");    
    display.print(minutos);
    display.print("m");
    display.print(segundos);
    display.print("s");
    display.setCursor(2, 33);
    display.print("TEMP. CPU: ");
    display.print(temperatureRead());
    display.print((char)247); //Codigo ASCII para º
    display.println("C");
    display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
    display.setCursor(2, 50);
    display.setTextColor(SH110X_BLACK);
    display.print("PULSA 'OK' PARA SALIR");
    display.display();
  #endif
  
            if (selector == 2){
              selector =0;
              delay(250);
            }
}

void menuHome(){
  #ifdef SSD1306
  display.clearDisplay();
  display.drawBitmap(22, 25, home, 16, 16, 1);
  display.setTextColor(WHITE);
  display.setCursor(40, 30);
  display.print("ESTADO ESP32");
  display.drawRoundRect(1, 23, 127, 20, 3, WHITE);
  display.display();
  delay(150);
  #else
  display.clearDisplay();
  display.drawBitmap(22, 20, home, 16, 16, SH110X_WHITE);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(40, 25);
  display.print("ESTADO ESP32");
  display.drawRoundRect(1, 17, 127, 21, 3, SH110X_WHITE);
  display.drawBitmap(1, 45, flecha_izquierda, 16, 16, SH110X_WHITE);
  display.drawBitmap(112, 45, flecha_derecha, 16, 16, SH110X_WHITE);
  display.display();
  delay(150);
  #endif
}

void menuTemp(){
  #ifdef SSD1306
    display.clearDisplay();
    display.drawBitmap(22, 25, termometro, 16, 16, 1);
    display.setTextColor(WHITE);
    display.setCursor(40, 30);
    display.print("TEMPERATURA");
    display.drawRoundRect(1, 23, 127, 20, 3, WHITE);
    display.display();
    delay(150);
  #else
    display.clearDisplay();
    display.drawBitmap(22, 20, termometro, 16, 16, SH110X_WHITE);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(40, 25);
    display.print("TEMPERATURA");
    display.drawRoundRect(1, 17, 127, 21, 3, SH110X_WHITE);
    display.drawBitmap(1, 45, flecha_izquierda, 16, 16, SH110X_WHITE);
    display.drawBitmap(112, 45, flecha_derecha, 16, 16, SH110X_WHITE);
    display.display();
    delay(150);
  #endif

}
void tempLive(){
  #ifdef SH1106
      delay(150);
      lecturaBotones();
      lecturaBME280();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setCursor(12, 1);
      display.setTextSize(1);
      display.setTextColor(SH110X_BLACK);
      display.print("MENU TEMPERATURA"); //V2.2
      display.drawBitmap(2, 15, termometro, 16, 16, 1);
      display.setCursor(25, 15);
      display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.print(temp);
      display.print((char)247); //Codigo ASCII para º
      display.println("C");
      display.setTextSize(1);
      display.fillRoundRect(1, 53, 128, 12, 2, SH110X_WHITE);
      display.setCursor(2, 55);
      display.setTextColor(SH110X_BLACK);
      display.print("PULSA 'OK' PARA SALIR");
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 35);
      display.print("MIN: ");
      display.print(tempMinima);
      display.print((char)247);
      display.println("C");
      display.setCursor(1, 45);
      display.setTextSize(1);
      display.print("MAX: ");
      display.print(tempMaxima);
      display.print((char)247);
      display.println("C");
      display.display();
        if(selector == 2){
          Serial.println("he entrado al bucle");
          //delay(150);
          contador =10;
          selector =0;
          Serial.println(selector);
          Serial.println(contador);   
        }
    #endif
}
void humLive(){
  #ifdef SH1106
      delay(150);
      lecturaBotones();
      lecturaBME280();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setCursor(12, 1);
      display.setTextSize(1);
      display.setTextColor(SH110X_BLACK);
      display.print("MENU HUMEDAD"); //V2.2
      display.drawBitmap(2, 15, gota, 16, 16, 1);
      display.setCursor(25, 15);
      display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.print(humedad);
      display.println("%");
      display.setTextSize(1);
      display.fillRoundRect(1, 53, 128, 12, 2, SH110X_WHITE);
      display.setCursor(2, 55);
      display.setTextColor(SH110X_BLACK);
      display.print("PULSA 'OK' PARA SALIR");
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 35);
      display.print("MIN: ");
      display.print(humedadMinima);
      display.println("%");
      display.setCursor(1, 45);
      display.setTextSize(1);
      display.print("MAX: ");
      display.print(humedadMaxima);
      display.println("%");
      display.display();
        if(selector == 2){
          Serial.println("he entrado al bucle");
          //delay(150);
          contador =10;
          selector =0;
          Serial.println(selector);
          Serial.println(contador);   
        }
    #endif
}
void presLive(){
  #ifdef SH1106
      
      lecturaBotones();
      delay(150);
      lecturaBME280();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setCursor(12, 1);
      display.setTextSize(1);
      display.setTextColor(SH110X_BLACK);
      display.print("MENU PRES. ATM."); //V2.2
      display.drawBitmap(2, 15, gota, 16, 16, 1);
      display.setCursor(25, 15);
      display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.print(presion);
      display.println("hPA");
      display.setTextSize(1);
      display.fillRoundRect(1, 53, 128, 12, 2, SH110X_WHITE);
      display.setCursor(2, 55);
      display.setTextColor(SH110X_BLACK);
      display.print("PULSA 'OK' PARA SALIR");
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 35);
      display.print("MIN: ");
      display.print(presionMinima);
      display.println("hPA");
      display.setCursor(1, 45);
      display.setTextSize(1);
      display.print("MAX: ");
      display.print(presionMaxima);
      display.println("hPA");
      display.display();
        if(selector == 2){
          Serial.println("he entrado al bucle");
          //delay(150);
          contador =10;
          selector =0;
          Serial.println(selector);
          Serial.println(contador);   
        }
    #endif
}
void altLive(){
  #ifdef SH1106
      delay(150);
      lecturaBotones();
      lecturaBME280();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setCursor(12, 1);
      display.setTextSize(1);
      display.setTextColor(SH110X_BLACK);
      display.print("MENU ALTITUD"); //V2.2
      display.drawBitmap(2, 15, gota, 16, 16, 1);
      display.setCursor(25, 15);
      display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.print(altura);
      display.println("mts");
      display.setTextSize(1);
      display.fillRoundRect(1, 53, 128, 12, 2, SH110X_WHITE);
      display.setCursor(2, 55);
      display.setTextColor(SH110X_BLACK);
      display.print("PULSA 'OK' PARA SALIR");
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 35);
      display.print("MIN: ");
      display.print(alturaMinima);
      display.println("mts");
      display.setCursor(1, 45);
      display.setTextSize(1);
      display.print("MAX: ");
      display.print(alturaMaxima);
      display.println("mts");
      display.display();
        if(selector == 2){
          Serial.println("he entrado al bucle");
          //delay(150);
          contador =10;
          selector =0;
          Serial.println(selector);
          Serial.println(contador);   
        }
    #endif
}
void tempTest(){
    #ifdef SH1106
    while (contador >= 11){
      selector =0;
      lecturaBotones();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
      display.setCursor(18, 2);
      display.setTextColor(SH110X_BLACK);
      display.print("GENERAR GRAFICA");
      display.setCursor(3, 15);
      display.setTextColor(SH110X_WHITE);
      display.print("2 MINUTOS");
      display.setCursor(3, 28);
      display.print("15 MINUTOS");
      display.setCursor(3, 41);
      display.print("60 MINUTOS");
      display.setCursor(3, 54);
      display.print("VOLVER");
      display.display();
      lecturaBotones();
      delay(500);

      while (contador == 11){ //Opcion 2 minutos
       lecturaBotones();
       delay(150);
       Serial.println(contador);
       Serial.println(selector);
       display.drawRoundRect(0, 12, 75, 12, 2, SH110X_WHITE);
       display.display();
       columna = 14;

         while (contador == 11 && selector == 1){
          Serial.println("estoy dentro");
          grafTemp2();
          }       

          if (contador == 12){
            display.drawRoundRect(0, 12, 75, 12, 2, SH110X_BLACK);       
            display.display();       
            delay(150);       
          }
          if (selector >= 2){
            selector =0;
          }
                
      }
      while (contador == 12){ //Opcion 15 minutos
        lecturaBotones();
        delay(150);
        Serial.println(contador);
        display.drawRoundRect(0, 25, 75, 12, 2, SH110X_WHITE);
        display.display();
        columna = 14;        
        while (contador == 12 && selector == 1){
          grafTemp15();
        }        
        if (contador == 13){        
          display.drawRoundRect(0, 25, 75, 12, 2, SH110X_BLACK);
          display.display();       
          delay(150);        
        }
                
      }

     while (contador == 13){ //Opcion 60 minutos
        lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 38, 75, 12, 2, SH110X_WHITE);
                display.display();
                columna = 14;          
                while (contador == 13 && selector == 1){
                  grafTemp60();
                }
                if (contador == 14){
                  display.drawRoundRect(0, 38, 75, 12, 2, SH110X_BLACK);
                  display.display();
                  delay(150);
                }
                
              }

              while (contador == 14){ //Opcion salir
                lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 52, 60, 12, 2, SH110X_WHITE);
                display.display();
                if (contador == 14 && selector == 1){
                  contador = 10;
                  selector= 0;
                  display.clearDisplay();
                  
                }
                if (contador == 15){
                  contador = 11;
                  display.drawRoundRect(0, 52, 60, 12, 2, SH110X_BLACK);
                  display.display();
                  delay(150);
                }
              }
    }
    #endif
}
void humTest(){
  #ifdef SH1106
  while (contador >= 11){
      selector =0;
      lecturaBotones();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
      display.setCursor(18, 2);
      display.setTextColor(SH110X_BLACK);
      display.print("GENERAR GRAFICA");
      display.setCursor(3, 15);
      display.setTextColor(SH110X_WHITE);
      display.print("2 MINUTOS");
      display.setCursor(3, 28);
      display.print("15 MINUTOS");
      display.setCursor(3, 41);
      display.print("60 MINUTOS");
      display.setCursor(3, 54);
      display.print("VOLVER");
      display.display();
      lecturaBotones();
      delay(500);

      while (contador == 11){ //Opcion 2 minutos
       lecturaBotones();
       delay(150);
       Serial.println(contador);
       Serial.println(selector);
       display.drawRoundRect(0, 12, 75, 12, 2, SH110X_WHITE);
       display.display();
       columna = 14;

         while (contador == 11 && selector == 1){
          Serial.println("estoy dentro");
          grafHum2();
          }       

          if (contador == 12){
            display.drawRoundRect(0, 12, 75, 12, 2, SH110X_BLACK);       
            display.display();       
            delay(150);       
          }
          if (selector >= 2){
            selector =0;
          }
                
      }
      while (contador == 12){ //Opcion 15 minutos
        lecturaBotones();
        delay(150);
        Serial.println(contador);
        display.drawRoundRect(0, 25, 75, 12, 2, SH110X_WHITE);
        display.display();
        columna = 14;        
        while (contador == 12 && selector == 1){
          grafHum15();
        }        
        if (contador == 13){        
          display.drawRoundRect(0, 25, 75, 12, 2, SH110X_BLACK);
          display.display();       
          delay(150);        
        }
                
      }

     while (contador == 13){ //Opcion 60 minutos
        lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 38, 75, 12, 2, SH110X_WHITE);
                display.display();
                columna = 14;          
                while (contador == 13 && selector == 1){
                  grafHum60();
                }
                if (contador == 14){
                  display.drawRoundRect(0, 38, 75, 12, 2, SH110X_BLACK);
                  display.display();
                  delay(150);
                }
                
              }

              while (contador == 14){ //Opcion salir
                lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 52, 60, 12, 2, SH110X_WHITE);
                display.display();
                if (contador == 14 && selector == 1){
                  contador = 10;
                  selector= 0;
                  display.clearDisplay();
                  
                }
                if (contador == 15){
                  contador = 11;
                  display.drawRoundRect(0, 52, 60, 12, 2, SH110X_BLACK);
                  display.display();
                  delay(150);
                }
              }
  }
    #endif
}
void presTest(){
  #ifdef SH1106
      
      while (contador >= 11){

      selector =0;
      lecturaBotones();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
      display.setCursor(18, 2);
      display.setTextColor(SH110X_BLACK);
      display.print("GENERAR GRAFICA");
      display.setCursor(3, 15);
      display.setTextColor(SH110X_WHITE);
      display.print("15 MINUTOS");
      display.setCursor(3, 28);
      display.print("60 MINUTOS");
      display.setCursor(3, 41);
      display.print("120 MINUTOS");
      display.setCursor(3, 54);
      display.print("VOLVER");
      display.display();
      lecturaBotones();
      delay(500);

      while (contador == 11){ //Opcion 2 minutos
       lecturaBotones();
       delay(150);
       Serial.println(contador);
       Serial.println(selector);
       display.drawRoundRect(0, 12, 75, 12, 2, SH110X_WHITE);
       display.display();
       columna = 14;

         while (contador == 11 && selector == 1){
          Serial.println("estoy dentro");
          grafPres15();
          }       

          if (contador == 12){
            display.drawRoundRect(0, 12, 75, 12, 2, SH110X_BLACK);       
            display.display();       
            delay(150);       
          }
          if (selector >= 2){
            selector =0;
          }
                
      }
      while (contador == 12){ //Opcion 15 minutos
        lecturaBotones();
        delay(150);
        Serial.println(contador);
        display.drawRoundRect(0, 25, 75, 12, 2, SH110X_WHITE);
        display.display();
        columna = 14;        
        while (contador == 12 && selector == 1){
          grafPres60();
        }        
        if (contador == 13){        
          display.drawRoundRect(0, 25, 75, 12, 2, SH110X_BLACK);
          display.display();       
          delay(150);        
        }
                
      }

     while (contador == 13){ //Opcion 60 minutos
        lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 38, 75, 12, 2, SH110X_WHITE);
                display.display();
                columna = 14;          
                while (contador == 13 && selector == 1){
                  grafPres120();
                }
                if (contador == 14){
                  display.drawRoundRect(0, 38, 75, 12, 2, SH110X_BLACK);
                  display.display();
                  delay(150);
                }
                
              }

              while (contador == 14){ //Opcion salir
                lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 52, 60, 12, 2, SH110X_WHITE);
                display.display();
                if (contador == 14 && selector == 1){
                  contador = 10;
                  selector= 0;
                  display.clearDisplay();
                  
                }
                if (contador == 15){
                  display.drawRoundRect(0, 52, 60, 12, 2, SH110X_BLACK);
                  display.display();
                  contador = 11;
                  delay(150);
                }
              }
      }
    #endif
}
void altTest(){
  #ifdef SH1106
  while (contador >= 11){
      selector =0;
      lecturaBotones();
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
      display.setCursor(18, 2);
      display.setTextColor(SH110X_BLACK);
      display.print("GENERAR GRAFICA");
      display.setCursor(3, 15);
      display.setTextColor(SH110X_WHITE);
      display.print("15 MINUTOS");
      display.setCursor(3, 28);
      display.print("60 MINUTOS");
      display.setCursor(3, 41);
      display.print("120 MINUTOS");
      display.setCursor(3, 54);
      display.print("VOLVER");
      display.display();
      lecturaBotones();
      delay(500);

      while (contador == 11){ //Opcion 2 minutos
       lecturaBotones();
       delay(150);
       Serial.println(contador);
       Serial.println(selector);
       display.drawRoundRect(0, 12, 75, 12, 2, SH110X_WHITE);
       display.display();
       columna = 14;

         while (contador == 11 && selector == 1){
          Serial.println("estoy dentro");
          grafAlt15();
          }       

          if (contador == 12){
            display.drawRoundRect(0, 12, 75, 12, 2, SH110X_BLACK);       
            display.display();       
            delay(150);       
          }
          if (selector >= 2){
            selector =0;
          }
                
      }
      while (contador == 12){ //Opcion 15 minutos
        lecturaBotones();
        delay(150);
        Serial.println(contador);
        display.drawRoundRect(0, 25, 75, 12, 2, SH110X_WHITE);
        display.display();
        columna = 14;        
        while (contador == 12 && selector == 1){
          grafAlt60();
        }        
        if (contador == 13){        
          display.drawRoundRect(0, 25, 75, 12, 2, SH110X_BLACK);
          display.display();       
          delay(150);        
        }
                
      }

     while (contador == 13){ //Opcion 60 minutos
        lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 38, 75, 12, 2, SH110X_WHITE);
                display.display();
                columna = 14;          
                while (contador == 13 && selector == 1){
                  grafAlt120();
                }
                if (contador == 14){
                  display.drawRoundRect(0, 38, 75, 12, 2, SH110X_BLACK);
                  display.display();
                  delay(150);
                }
                
              }

              while (contador == 14){ //Opcion salir
                lecturaBotones();
                delay(150);
                Serial.println(contador);
                display.drawRoundRect(0, 52, 60, 12, 2, SH110X_WHITE);
                display.display();
                if (contador == 14 && selector == 1){
                  contador = 10;
                  selector= 0;
                  display.clearDisplay();
                  
                }
                if (contador == 15){
                  contador = 11;
                  display.drawRoundRect(0, 52, 75, 12, 2, SH110X_BLACK);
                  display.display();
                  delay(150);
                }
              }
  }
  
    #endif
}
void menuAltitud(){
  #ifdef SSD1306
    display.clearDisplay();
    display.drawBitmap(22, 25, cara, 16, 16, 1);
    display.setTextColor(WHITE);
    display.setCursor(40, 30);
    display.print("ALTITUD");
    display.drawRoundRect(1, 23, 127, 20, 3, WHITE);
    display.display();
    delay(150);
  #else
    display.clearDisplay();
    display.drawBitmap(22, 20, cara, 16, 16, SH110X_WHITE);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(40, 25);
    display.print("ALTITUD");
    display.drawRoundRect(1, 17, 127, 21, 3, SH110X_WHITE);
    display.drawBitmap(1, 45, flecha_izquierda, 16, 16, SH110X_WHITE);
    display.drawBitmap(112, 45, flecha_derecha, 16, 16, SH110X_WHITE);
    display.display();
    delay(150);
  #endif
}
void menuHumedad(){
  #ifdef SSD1306
    display.clearDisplay();
    display.drawBitmap(22, 25, gota, 16, 16, 1);
    display.setTextColor(WHITE);
    display.setCursor(40, 30);
    display.print("HUMEDAD");
    display.drawRoundRect(1, 23, 127, 20, 3, WHITE);
    display.display();
    delay(150);
  #else
    display.clearDisplay();
    display.drawBitmap(22, 20, gota, 16, 16, SH110X_WHITE);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(40, 25);
    display.print("HUMEDAD");
    display.drawRoundRect(1, 17, 127, 21, 3, SH110X_WHITE);
    display.drawBitmap(1, 45, flecha_izquierda, 16, 16, SH110X_WHITE);
    display.drawBitmap(112, 45, flecha_derecha, 16, 16, SH110X_WHITE);
    display.display();
    delay(150);
  #endif
}
void menuPresAtmos(){
  #ifdef SSD1306
    display.clearDisplay();
    display.drawBitmap(2, 25, reloj, 16, 16, 1);
    display.setTextColor(WHITE);
    display.setCursor(20, 30);
    display.print("Pres. Atmosferica");
    display.drawRoundRect(1, 23, 127, 20, 3, WHITE);
    display.display();
    delay(150);
  #else
    display.clearDisplay();
    display.drawBitmap(2, 20, reloj, 16, 16, SH110X_WHITE);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(20, 25);
    display.print("Pres. Atmosferica");
    display.drawRoundRect(1, 17, 127, 21, 3, SH110X_WHITE);
    display.drawBitmap(1, 45, flecha_izquierda, 16, 16, SH110X_WHITE);
    display.drawBitmap(112, 45, flecha_derecha, 16, 16, SH110X_WHITE);
    display.display();
    delay(150);
  #endif
}

void loop(){

  lecturaBotones();

  #ifdef ds18b20
    lecturaDS18B20();
    #endif

  #ifdef SSD1306
    #ifdef bme280
    delay(1000);
    display.clearDisplay();
    display.fillRoundRect(0, 0, 128, 20, 2, WHITE);
    display.setCursor(2, 1);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print("BATERIA: ");
    display.print(porcentajeCarga);
    display.println("%");
    display.setCursor(2, 10);
    display.print("TIEMPO USO: ");
    display.print(horas);
    display.print("h");    
    display.print(minutos);
    display.print("m");
    display.print(segundos);
    display.print("s");
    display.setCursor(2, 24);
    display.setTextColor(WHITE);
    display.print("TEMPERATURA: ");
    dispslay.print(bme.readTemperature());
    display.print((char)247); //Codigo ASCII para º
    display.println("C");
    display.setCursor(2, 38);
    display.print("HUMEDAD: ");
    display.print(bme.readHumidity());
    display.println("%");
    display.setCursor(2, 52);
    display.print("ALTITUD: ");
    display.print(bme.readAltitude(PresionNivelMar_HPA));
    display.println("mts");
    display.display();
  #endif
    #ifdef ds18b20 //OJO, PARTE EN MODIFICACION PARA SUBIR A V2.3
    
    switch (contador){
      case 1:
        menuTemp();

        if (selector == 1){
          monitorTemp();
        }
        selector =0;
        break;
      case 2:
        menuHumedad();
          if (selector == 1){
            display.fillRoundRect(1, 23, 127, 20, 3, WHITE);
            display.drawBitmap(22, 25, gota, 16, 16, BLACK);
            display.setTextColor(BLACK);
            display.setCursor(40, 30);
            display.print("HUMEDAD");
            display.display();
            delay(150);
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setCursor(10, 20);
            display.println("MENU NO DISPONIBLE");
            display.setCursor(35, 30);
            display.println("CON ESTA");
            display.setCursor(20, 40);
            display.println("CONFIGURACION");
            display.display();
            delay(4000);
            selector = 0;
          }
        break;
      case 3:
        menuPresAtmos();
          if (selector == 1){
            display.fillRoundRect(1, 23, 127, 20, 3, WHITE);
            display.drawBitmap(2, 25, reloj, 16, 16, BLACK);
            display.setTextColor(BLACK);
            display.setCursor(20, 30);
            display.print("Pres. Atmosferica");
            display.display();
            delay(150);
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setCursor(10, 20);
            display.println("MENU NO DISPONIBLE");
            display.setCursor(35, 30);
            display.println("CON ESTA");
            display.setCursor(20, 40);
            display.println("CONFIGURACION");
            display.display();
            delay(4000);
            selector = 0;
          }
        break;
      default:
        menuHome();
        while (selector == 1){
          menuPpl();
          
        }
        if (contador == 4 || contador < 0){
          contador = 0;
        }
        
      break;
      
    }

    #endif
#endif

  #ifdef SH1106
    #ifdef bme280

      switch (contador){  //////////////////////////////////////////////////MENU SH1106
        case 1:
          menuTemp();
              
              if (selector == 1){
              display.fillRoundRect(1, 23, 127, 20, 3, SH110X_WHITE);
              display.drawBitmap(22, 25, termometro, 16, 16, SH110X_BLACK);
              display.setTextColor(SH110X_BLACK);
              display.setCursor(40, 30);
              display.print("TEMPERATURA");
              display.display();
              delay(150);
              display.clearDisplay();
              contador = 10;
            }
            
            while (contador >= 10){
              selector =0;
              lecturaBotones();
              switch (contador){  ////////////////////////////////////////////////SUBMENU TEMPERATURA
                case 11:
                  while (contador == 11){
                    lecturaBotones();
                    display.drawRoundRect(1, 18, 127, 15, 3, SH110X_WHITE);
                    display.display();
                    delay(150);
                  while (contador ==11 && selector == 1){
                    Serial.println(selector);
                    Serial.println(contador);
                    tempLive();
                    }
                  }
                break;
                

                case 12:
                  display.drawRoundRect(1, 18, 127, 15, 3, SH110X_BLACK);
                  display.drawRoundRect(1, 33, 127, 15, 3, SH110X_WHITE);
                  display.display();
                  delay(150);
                  while (selector == 1){
                    contador =11;
                    tempTest();
                  }
                  break;

                case 13:
                display.drawRoundRect(1, 33, 127, 15, 3, SH110X_BLACK);
                display.drawRoundRect(1, 48, 127, 15, 3, SH110X_WHITE);
                display.display();
                delay(150);
                  
                break;

                default:
                  Serial.println("estoy en el menu temperatura");
                  display.clearDisplay();
                  display.setTextColor(SH110X_WHITE);
                  display.drawBitmap(1, 1, termometro, 16, 16, SH110X_WHITE);
                  display.setCursor(18, 5);
                  display.print("MENU TEMPERATURA");
                  display.drawRoundRect(18, 13, 126, 1, 0, SH110X_WHITE);

                  display.setCursor(4, 23);
                  display.print("TEMPERATURA LIVE");
                  
                  display.setCursor(4, 38);
                  display.print("TEST TEMPERATURA");

                  display.setCursor(4, 53);
                  display.print("VOLVER");
                  
                  
                  display.display();
                  delay(150);
                  break;
              }
              if (contador > 13 || contador < 10){
                contador =11;
              }
              if (contador ==13 && selector == 1){
                    contador =1;
                    selector =0;
                    display.drawRoundRect(1, 48, 127, 15, 3, SH110X_BLACK);
                    delay(150);
                  }
            }
          break;
        case 2:
          menuHumedad();
            if (selector == 1){
              
              display.fillRoundRect(1, 23, 127, 20, 3, SH110X_WHITE);
              display.drawBitmap(22, 25, gota, 16, 16, SH110X_BLACK);
              display.setTextColor(SH110X_BLACK);
              display.setCursor(40, 30);
              display.print("HUMEDAD");
              display.display();
              delay(150);
              display.clearDisplay();
              contador = 10;
              
            }
            
            while (contador >= 10){
              selector =0;
              lecturaBotones();
              switch (contador){  ////////////////////////////////////////////////SUBMENU HUMEDAD
    
                case 11:
                  while (contador == 11){
                    lecturaBotones();
                    display.drawRoundRect(1, 18, 127, 15, 3, SH110X_WHITE);
                    display.display();
                    delay(150);
                  while (contador ==11 && selector == 1){
                    Serial.println(selector);
                    Serial.println(contador);
                    humLive();
                    }
                  }
                  break;

                case 12:
                  display.drawRoundRect(1, 18, 127, 15, 3, SH110X_BLACK);
                  display.drawRoundRect(1, 33, 127, 15, 3, SH110X_WHITE);
                  display.display();
                  delay(150);
                  while (selector == 1){
                    contador =11;
                    humTest();
                  }
                  break;

                case 13:
                display.drawRoundRect(1, 33, 127, 15, 3, SH110X_BLACK);
                display.drawRoundRect(1, 48, 127, 15, 3, SH110X_WHITE);
                display.display();
                delay(150);
                break;

                default:
                  display.clearDisplay();
                  display.setTextColor(SH110X_WHITE);
                  display.drawBitmap(1, 1, gota, 16, 16, SH110X_WHITE);
                  display.setCursor(18, 5);
                  display.print("MENU HUMEDAD");
                  display.drawRoundRect(18, 13, 126, 1, 0, SH110X_WHITE);

                  display.setCursor(4, 23);
                  display.print("HUMEDAD LIVE");
                  
                  display.setCursor(4, 38);
                  display.print("TEST HUMEDAD");

                  display.setCursor(4, 53);
                  display.print("VOLVER");
                  
                  
                  display.display();
                  delay(150);
                  break;
                
                
                }
                if (contador > 13 || contador < 10){
                contador =11;
              }
              if (contador ==13 && selector == 1){
                    contador =2;
                    selector =0;
                    display.drawRoundRect(1, 48, 127, 15, 3, SH110X_BLACK);
                    delay(150);
                  }
            }
              
              //selector = 0;
              //contador =2;
            
          break;
        case 3:
          menuPresAtmos();
            if (selector == 1){
              
              display.fillRoundRect(1, 23, 127, 20, 3, SH110X_WHITE);
              display.drawBitmap(22, 25, reloj, 16, 16, SH110X_BLACK);
              display.setTextColor(SH110X_BLACK);
              display.setCursor(20, 30);
              display.print("Pres. Atmosferica");
              display.display();
              delay(150);
              display.clearDisplay();
              contador = 10;
            }
            
            while (contador >= 10){
              selector =0;
              lecturaBotones();
              switch (contador){    //////////////////////////////////////////SUBMENU PRESION ATMOSFERICA
    
                case 11:
                  while (contador == 11){
                    lecturaBotones();
                    display.drawRoundRect(1, 18, 127, 15, 3, SH110X_WHITE);
                    display.display();
                    delay(150);
                  while (contador ==11 && selector == 1){
                    Serial.println(selector);
                    Serial.println(contador);
                    presLive();
                    }
                  }
                  break;

                case 12:
                  display.drawRoundRect(1, 18, 127, 15, 3, SH110X_BLACK);
                  display.drawRoundRect(1, 33, 127, 15, 3, SH110X_WHITE);
                  display.display();
                  delay(150);
                  while (selector == 1){
                    contador =11;
                    presTest();
                  }
                  break;

                case 13:
                display.drawRoundRect(1, 33, 127, 15, 3, SH110X_BLACK);
                display.drawRoundRect(1, 48, 127, 15, 3, SH110X_WHITE);
                display.display();
                delay(150);
                break;

                default:
                  display.clearDisplay();
                  display.setTextColor(SH110X_WHITE);
                  display.drawBitmap(1, 1, reloj, 16, 16, SH110X_WHITE);
                  display.setCursor(18, 5);
                  display.print("MENU PRES. ATMOS.");
                  display.drawRoundRect(18, 13, 126, 1, 0, SH110X_WHITE);

                  display.setCursor(4, 23);
                  display.print("PRESION LIVE");
                  
                  display.setCursor(4, 38);
                  display.print("TEST PRESION");

                  display.setCursor(4, 53);
                  display.print("VOLVER");
                  
                  
                  display.display();
                  delay(150);
                  break;
                
                
                }
                if (contador > 13 || contador < 10){
                contador =11;
              }
              if (contador ==13 && selector == 1){
                    contador =3;
                    selector =0;
                    display.drawRoundRect(1, 48, 127, 15, 3, SH110X_BLACK);
                    delay(150);
                  }
            }
              
              //selector = 0;
              //contador =2;
            
          break;
        case 4: 
        menuAltitud();
            if (selector == 1){
              
              display.fillRoundRect(1, 23, 127, 20, 3, SH110X_WHITE);
              display.drawBitmap(22, 25, reloj, 16, 16, SH110X_BLACK);
              display.setTextColor(SH110X_BLACK);
              display.setCursor(20, 30);
              display.print("ALTITUD");
              display.display();
              delay(150);
              display.clearDisplay();
              contador = 10;
            }
            
            while (contador >= 10){
              selector =0;
              lecturaBotones();
              switch (contador){    //////////////////////////////////////////SUBMENU ALTITUD
    
                case 11:
                  while (contador == 11){
                    lecturaBotones();
                    display.drawRoundRect(1, 18, 127, 15, 3, SH110X_WHITE);
                    display.display();
                    delay(150);
                  while (contador ==11 && selector == 1){
                    Serial.println(selector);
                    Serial.println(contador);
                    altLive();
                    }
                  }
                  break;

                case 12:
                  display.drawRoundRect(1, 18, 127, 15, 3, SH110X_BLACK);
                  display.drawRoundRect(1, 33, 127, 15, 3, SH110X_WHITE);
                  display.display();
                  delay(150);
                  while (selector == 1){
                    contador =11;
                    altTest();
                  }
                  break;

                case 13:
                display.drawRoundRect(1, 33, 127, 15, 3, SH110X_BLACK);
                display.drawRoundRect(1, 48, 127, 15, 3, SH110X_WHITE);
                display.display();
                delay(150);
                break;

                default:
                  display.clearDisplay();
                  display.setTextColor(SH110X_WHITE);
                  display.drawBitmap(1, 1, reloj, 16, 16, SH110X_WHITE);
                  display.setCursor(18, 5);
                  display.print("MENU ALTITUD");
                  display.drawRoundRect(18, 13, 126, 1, 0, SH110X_WHITE);

                  display.setCursor(4, 23);
                  display.print("ALTITUD LIVE");
                  
                  display.setCursor(4, 38);
                  display.print("TEST ALTITUD");

                  display.setCursor(4, 53);
                  display.print("VOLVER");
                  
                  
                  display.display();
                  delay(150);
                  break;
                
                
                }
                if (contador > 13 || contador < 10){
                contador =11;
                }
                if (contador ==13 && selector == 1){
                    contador =4;
                    selector =0;
                    display.drawRoundRect(1, 48, 127, 15, 3, SH110X_BLACK);
                    delay(150);
                  }
            }
          break;
        default:
          menuHome();
          
          while (selector == 1){
            menuPpl();
            
          }
          if (contador == 5){
            contador = 0;
          }
          if (contador < 0){
            contador = 4;
          }
          
        break;
        
      }
      
    #endif

    #ifdef ds18b20
      delay(1000);
      display.clearDisplay();
      display.fillRoundRect(0, 0, 128, 20, 2, SH110X_WHITE);
      display.setCursor(2, 1);
      display.setTextSize(1);
      display.setTextColor(SH110X_BLACK);
      display.print("BATERIA: ");
      display.print(porcentajeCarga);
      display.println("%");
      display.setCursor(2, 10);
      display.print("TIEMPO USO: ");
      display.print(horas);
      display.print("h");    
      display.print(minutos);
      display.print("m");
      display.print(segundos);
      display.print("s");
      display.drawBitmap(2, 25, termometro, 16, 16, 1);
      display.setCursor(25, 25);
      display.setTextColor(SH110X_WHITE);
      display.setTextSize(2);
      display.print(temp);
      display.print((char)247); //Codigo ASCII para º
      display.println("C");

      display.setCursor(2, 45);
      display.setTextSize(1);
      display.print("MIN: ");
      display.print(minima);
      display.println((char)247);

      display.setCursor(2, 55);
      display.setTextSize(1);
      display.print("MAX: ");
      display.print(maxima);
      display.println((char)247);
      display.display();
    #endif

  #endif
  
}
