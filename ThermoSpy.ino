/*********************************************************************************************************************************************************************************
**                                                           -THERMOSPY-                                                                                                        **
**                                                                                                                                                                              **
**   SENCILLO CODIGO PARA MOSTRAR VALORES AMBIENTALES EN PANTALLA OLED DE 0,96":                                                                                                **
**          -V1.0(HASTA 12/08/2025): SE MUESTRAN VALORES DE NIVEL DE BATERIA (%), TIEMPO EN USO Y TEMPERATURA AMBIENTE MEDIANTE SENSOR DS18B20                                  **
**          -V2.0(DESDE 12/08/2025): SE SUSTITUYE EL SENSOR DS18B20 POR UN BME280 PARA PODER MOSTRAR POR PANTALLA TEMPERATURA, HUMEDAD Y ALTITUD.                               **
**                                   SE AÑADE TAMBIEN LA FECHA DE COMPILACION DEL CODIGO EN EL ARRANQUE                                                                         **
**          -V2.1(DESDE 15/08/2025): SE MEJORA EL CODIGO PUDIENDO ELEGIR ENTRE DOS TIPOS DE PANTALLA, HAY QUE DEFINIR LA QUE SE UTILIZA EN LAS LINEAS 29 Y/O 30                 **
**          -V2.2(DESDE 24/08/2025): SE VUELVE A MEJORAR EL CODIGO PUDIENDO ELEGIR ENTRE LAS DOS PANTALLAS(SSD1306 Y SSH1106) Y ENTRE LOS DOS SENSORES (DS18B20 Y BME280)       **
**
**
**
*********************************************************************************************************************************************************************************/
#include <Adafruit_GFX.h>
#include <TimeLib.h>




#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define AOUT_PIN 0



//Seleccion segun pantalla a utilizar
#define SSD1306  //Descomentar para pantallas 0,96" con controlador SSD1306
//#define SH1106     //Descomentar para pantallas 1,3" con controlador SH1106

//Seleccion sensor temperatura
//#define bme280
#define ds18b20

#ifdef bme280
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BME280.h>
  Adafruit_BME280 bme;
  #define PresionNivelMar_HPA (1013.25)
#endif

#ifdef ds18b20
  #include <OneWire.h>
  #include <DallasTemperature.h>
  #define oneWirePin 1
  OneWire oneWireBus(oneWirePin);
  DallasTemperature sensors(&oneWireBus);
  float minima = 100; //lineas 243 a 253
  float maxima;
    
#endif

#ifdef SSD1306
  #include <Adafruit_SSD1306.h>
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#else
  #include <Adafruit_SH110X.h>
  Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif

//Actualizar version de codigo para ambas pantallas
String versionCodigo = "V2.2";



unsigned char termometro[] =
{
	0b00000001, 0b11000000, //        ###      
	0b00000011, 0b11100000, //       #####     
	0b00000111, 0b00100000, //      ###  #     
	0b00000111, 0b11100000, //      ######     
	0b00000111, 0b00100000, //      ###  #     
	0b00000111, 0b11100000, //      ######     
	0b00000111, 0b00100000, //      ###  #     
	0b00000111, 0b11100000, //      ######     
	0b00000111, 0b00100000, //      ###  #     
	0b00001111, 0b11110000, //     ########    
	0b00011111, 0b11111000, //    ##########   
	0b00011111, 0b11111000, //    ##########   
	0b00011111, 0b11111000, //    ##########   
	0b00011111, 0b11111000, //    ##########   
	0b00001111, 0b11110000, //     ########    
	0b00000111, 0b11100000, //      ######     
};
void setup(){
  
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  
  
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

void loop(){
  
  int valor = analogRead(AOUT_PIN); // lee el valor del pin 0 del esp32
  int voltaje = map(valor, 0, 4095, 0, 2500); //Lee la tension de la batería, a 5v leería el maximo de 2,5V. Las baterias LiPo marcan 4,2V a carga completa(un 16% menos del total)
  int porcentajeCarga = map(voltaje, 1500, 1775, 0, 100);
  int horas = hour();
  int minutos = minute();
  int segundos = second();

  #ifdef ds18b20
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    //float minima; //lineas 243 a 253
    //float maxima;
    if (temp < minima){
      minima = temp;
    }
    if (temp > maxima){
      maxima = temp;
    }
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
    #ifdef ds18b20
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
    display.drawBitmap(2, 25, termometro, 16, 16, 1);
    display.setCursor(25, 25);
    display.setTextColor(WHITE);
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

  #ifdef SH1106
    #ifdef bme280
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
      display.setCursor(2, 24);
      display.setTextColor(SH110X_WHITE);
      display.print("TEMPERATURA: ");
      display.print(bme.readTemperature());
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