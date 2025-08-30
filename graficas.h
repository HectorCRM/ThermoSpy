
//GRAFICAS TEMPERATURA PARA DS18B20(SSD1306) Y BME280(SH1106)
void grafTemp2(){

  #ifdef ds18b20
    #ifdef SSD1306
      lecturaTempGrafDs18b20();
      
      if (columna <= 14){
       display.clearDisplay();
      }
      display.fillRoundRect(0, 0, 128, 10, 2, WHITE);
      display.setTextColor(BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 2'");
      
      display.setTextColor(WHITE);
      display.setCursor(1, 10);
      display.print("40");
      display.setCursor(1, 20);
      display.print("30");
      display.setCursor(1, 30);
      display.print("20");
      display.setCursor(1, 40);
      display.print("10");
      display.setCursor(1, 50);
      display.print("0");
      display.setCursor(1, 60);
      display.print("-10");

      display.drawLine(columna, 20, columna, 50, BLACK);
      display.drawPixel(columna, tempGrafica, WHITE);
      columna ++;
      display.drawLine(columna, 20, columna, 50, WHITE);
      display.display();
      delay(937);
      Serial.println(tempGraficas);
      Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, WHITE);
          display.setCursor(18, 2);
          display.setTextColor(BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(WHITE);
          //RESULTADO PRUEBA TEMPERATURA MINIMA
          display.setCursor(2, 15);
          display.print("TEMP MIN: ");
          display.print(minimaGraficas); 
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MAXIMA
          display.setCursor(2, 25);
          display.print("TEMP MAX: ");
          display.print(maximaGraficas);
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maximaGraficas + minimaGraficas)/2);
          display.print((char)247);
          display.println("C");
          
          display.fillRoundRect(1, 48, 128, 12, 2, WHITE);
          display.setCursor(2, 50);
          display.setTextColor(BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif

  #ifdef bme280
    #ifdef SH1106

    lecturaTempBME();

    while (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 2'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 10);
      display.print("40");
      display.setCursor(1, 20);
      display.print("30");
      display.setCursor(1, 30);
      display.print("20");
      display.setCursor(1, 40);
      display.print("10");
      display.setCursor(1, 50);
      display.print("0");
      display.setCursor(1, 60);
      display.print("-10");

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapTempGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(937);
      //Serial.println(tempGraficas);
      Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA TEMPERATURA MINIMA
          display.setCursor(2, 15);
          display.print("TEMP MIN: ");
          display.print(tempMinGraf); 
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MAXIMA
          display.setCursor(2, 25);
          display.print("TEMP MAX: ");
          display.print(tempMaxGraf);
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((tempMaxGraf + tempMinGraf)/2);
          display.print((char)247);
          display.println("C");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
      
}
void grafTemp15(){
   #ifdef ds18b20
    #ifdef SSD1306
      lecturaTempGrafDs18b20();
      
      if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, WHITE);
      display.setTextColor(BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 15'");
      
      display.setTextColor(WHITE);
      display.setCursor(1, 10);
      display.print("40");
      display.setCursor(1, 20);
      display.print("30");
      display.setCursor(1, 30);
      display.print("20");
      display.setCursor(1, 40);
      display.print("10");
      display.setCursor(1, 50);
      display.print("0");
      display.setCursor(1, 60);
      display.print("-10");

      display.drawLine(columna, 12, columna, 64, BLACK);
      display.drawPixel(columna, tempGrafica, WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, WHITE);
      display.display();
      delay(7031);
      Serial.println(tempGraficas);
      Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, WHITE);
          display.setCursor(18, 2);
          display.setTextColor(BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(WHITE);
          //RESULTADO PRUEBA TEMPERATURA MINIMA
          display.setCursor(2, 15);
          display.print("TEMP MIN: ");
          display.print(minimaGraficas); 
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MAXIMA
          display.setCursor(2, 25);
          display.print("TEMP MAX: ");
          display.print(maximaGraficas);
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maximaGraficas + minimaGraficas)/2);
          display.print((char)247);
          display.println("C");
          
          display.fillRoundRect(1, 48, 128, 12, 2, WHITE);
          display.setCursor(2, 50);
          display.setTextColor(BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif

  #ifdef bme280
    #ifdef SH1106

    lecturaTempBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 15'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 10);
      display.print("40");
      display.setCursor(1, 20);
      display.print("30");
      display.setCursor(1, 30);
      display.print("20");
      display.setCursor(1, 40);
      display.print("10");
      display.setCursor(1, 50);
      display.print("0");
      display.setCursor(1, 60);
      display.print("-10");

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapTempGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(7031);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA TEMPERATURA MINIMA
          display.setCursor(2, 15);
          display.print("TEMP MIN: ");
          display.print(tempMinGraf); 
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MAXIMA
          display.setCursor(2, 25);
          display.print("TEMP MAX: ");
          display.print(tempMaxGraf);
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((tempMaxGraf + tempMinGraf)/2);
          display.print((char)247);
          display.println("C");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
         
      
}
void grafTemp60(){
    #ifdef ds18b20
    #ifdef SSD1306
      lecturaTempGrafDs18b20();
      
      if (columna <= 14){
       display.clearDisplay();
      }
      display.fillRoundRect(0, 0, 128, 10, 2, WHITE);
      display.setTextColor(BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 60'");
      
      display.setTextColor(WHITE);
      display.setCursor(1, 10);
      display.print("40");
      display.setCursor(1, 20);
      display.print("30");
      display.setCursor(1, 30);
      display.print("20");
      display.setCursor(1, 40);
      display.print("10");
      display.setCursor(1, 50);
      display.print("0");
      display.setCursor(1, 60);
      display.print("-10");

      display.drawLine(columna, 20, columna, 50, BLACK);
      display.drawPixel(columna, tempGrafica, WHITE);
      columna ++;
      display.drawLine(columna, 20, columna, 50, WHITE);
      display.display();
      delay(28125);
      Serial.println(tempGraficas);
      Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, WHITE);
          display.setCursor(18, 2);
          display.setTextColor(BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(WHITE);
          //RESULTADO PRUEBA TEMPERATURA MINIMA
          display.setCursor(2, 15);
          display.print("TEMP MIN: ");
          display.print(minimaGraficas); 
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MAXIMA
          display.setCursor(2, 25);
          display.print("TEMP MAX: ");
          display.print(maximaGraficas);
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maximaGraficas + minimaGraficas)/2);
          display.print((char)247);
          display.println("C");
          
          display.fillRoundRect(1, 48, 128, 12, 2, WHITE);
          display.setCursor(2, 50);
          display.setTextColor(BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif

  #ifdef bme280
    #ifdef SH1106

    lecturaTempBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 60'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 10);
      display.print("40");
      display.setCursor(1, 20);
      display.print("30");
      display.setCursor(1, 30);
      display.print("20");
      display.setCursor(1, 40);
      display.print("10");
      display.setCursor(1, 50);
      display.print("0");
      display.setCursor(1, 60);
      display.print("-10");

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapTempGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(28125);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA TEMPERATURA MINIMA
          display.setCursor(2, 15);
          display.print("TEMP MIN: ");
          display.print(tempMinGraf); 
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MAXIMA
          display.setCursor(2, 25);
          display.print("TEMP MAX: ");
          display.print(tempMaxGraf);
          display.print((char)247);
          display.println("C");
          //RESULTADO PRUEBA TEMPERATURA MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((tempMaxGraf + tempMinGraf)/2);
          display.print((char)247);
          display.println("C");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}

//GRAFICAS HUMEDAD PARA BME280 CON PANTALLA SH1106
void grafHum2(){
  #ifdef bme280
    #ifdef SH1106

    lecturaHumBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 2'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("100");
      display.setCursor(1, 25);
      display.print("75");
      display.setCursor(1, 35);
      display.print("50");
      display.setCursor(1, 45);
      display.print("25");
      display.setCursor(1, 55);
      display.print("0");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapHumGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(937);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("HUMEDAD MIN: ");
          display.print(minHumGraf); 
          display.println("%");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("HUMEDAD MAX: ");
          display.print(maxHumGraf);
          display.println("%");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxHumGraf + minHumGraf)/2);
          display.println("%");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}
void grafHum15(){
  #ifdef bme280
    #ifdef SH1106

    lecturaHumBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 15'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("100");
      display.setCursor(1, 25);
      display.print("75");
      display.setCursor(1, 35);
      display.print("50");
      display.setCursor(1, 45);
      display.print("25");
      display.setCursor(1, 55);
      display.print("0");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapHumGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(7031);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("HUMEDAD MIN: ");
          display.print(minHumGraf); 
          display.println("%");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("HUMEDAD MAX: ");
          display.print(maxHumGraf);
          display.println("%");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxHumGraf + minHumGraf)/2);
          display.println("%");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}
void grafHum60(){
  #ifdef bme280
    #ifdef SH1106

    lecturaHumBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 60'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("100");
      display.setCursor(1, 25);
      display.print("75");
      display.setCursor(1, 35);
      display.print("50");
      display.setCursor(1, 45);
      display.print("25");
      display.setCursor(1, 55);
      display.print("0");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapHumGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(28125);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("HUMEDAD MIN: ");
          display.print(minHumGraf); 
          display.println("%");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("HUMEDAD MAX: ");
          display.print(maxHumGraf);
          display.println("%");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxHumGraf + minHumGraf)/2);
          display.println("%");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}

//GRAFICAS PRESION ATMOSFERICA PARA BME280 CON PANTALLA SH1106V
void grafPres15(){
  #ifdef bme280
    #ifdef SH1106

    lecturaPresBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 15'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("1013");
      display.setCursor(1, 25);
      display.print("935");
      display.setCursor(1, 35);
      display.print("857");
      display.setCursor(1, 45);
      display.print("779");
      display.setCursor(1, 55);
      display.print("700");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapPresGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(7031);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("PRESION MIN: ");
          display.print(minPresGraf); 
          display.println("hPA");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("PRESION MAX: ");
          display.print(maxPresGraf);
          display.println("hPA");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxPresGraf + minPresGraf)/2);
          display.println("hPA");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}
void grafPres60(){
  #ifdef bme280
    #ifdef SH1106

    lecturaPresBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 60'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("1013");
      display.setCursor(1, 25);
      display.print("935");
      display.setCursor(1, 35);
      display.print("857");
      display.setCursor(1, 45);
      display.print("779");
      display.setCursor(1, 55);
      display.print("700");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapPresGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(28125);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("PRESION MIN: ");
          display.print(minPresGraf); 
          display.println("hPA");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("PRESION MAX: ");
          display.print(maxPresGraf);
          display.println("hPA");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxPresGraf + minPresGraf)/2);
          display.println("hPA");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}
void grafPres120(){
  #ifdef bme280
    #ifdef SH1106

    lecturaPresBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 120'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("1013");
      display.setCursor(1, 25);
      display.print("935");
      display.setCursor(1, 35);
      display.print("857");
      display.setCursor(1, 45);
      display.print("779");
      display.setCursor(1, 55);
      display.print("700");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapPresGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(56250);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("PRESION MIN: ");
          display.print(minPresGraf); 
          display.println("hPA");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("PRESION MAX: ");
          display.print(maxPresGraf);
          display.println("hPA");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxPresGraf + minPresGraf)/2);
          display.println("hPA");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}

//GRAFICAS ALTITUD PARA BME280 Y PANTALLA SH1106
void grafAlt15(){
  #ifdef bme280
    #ifdef SH1106

    lecturaAltBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 15'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("1500");
      display.setCursor(1, 25);
      display.print("1125");
      display.setCursor(1, 35);
      display.print("750");
      display.setCursor(1, 45);
      display.print("325");
      display.setCursor(1, 55);
      display.print("0");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapAltGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(7031);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("ALTITUD MIN: ");
          display.print(minAltGraf); 
          display.println("mts");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("ALTITUD MAX: ");
          display.print(maxAltGraf);
          display.println("mts");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxAltGraf + minAltGraf)/2);
          display.println("mts");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}
void grafAlt60(){
  #ifdef bme280
    #ifdef SH1106

    lecturaAltBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 60'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("1500");
      display.setCursor(1, 25);
      display.print("1125");
      display.setCursor(1, 35);
      display.print("750");
      display.setCursor(1, 45);
      display.print("325");
      display.setCursor(1, 55);
      display.print("0");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapAltGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(28125);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("ALTITUD MIN: ");
          display.print(minAltGraf); 
          display.println("mts");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("ALTITUD MAX: ");
          display.print(maxAltGraf);
          display.println("mts");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxAltGraf + minAltGraf)/2);
          display.println("mts");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}
void grafAlt120(){
  #ifdef bme280
    #ifdef SH1106

    lecturaAltBME();

    if (columna <= 14){
       display.clearDisplay();
       columna ++;
      }
      display.fillRoundRect(0, 0, 128, 10, 2, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(40, 2);
      display.setTextSize(1);
      display.print("TEST 120'");
      
      display.setTextColor(SH110X_WHITE);
      display.setCursor(1, 15);
      display.print("1500");
      display.setCursor(1, 25);
      display.print("1125");
      display.setCursor(1, 35);
      display.print("750");
      display.setCursor(1, 45);
      display.print("325");
      display.setCursor(1, 55);
      display.print("0");
     

      display.drawLine(columna, 12, columna, 64, SH110X_BLACK);
      display.drawPixel(columna, mapAltGraf, SH110X_WHITE);
      columna ++;
      display.drawLine(columna, 12, columna, 64, SH110X_WHITE);
      display.display();
      delay(56250);
      //Serial.println(tempGraficas);
      //Serial.println(columna);
        while (columna == 128){
          lecturaBotones();
          display.clearDisplay();
          display.fillRoundRect(0, 0, 128, 12, 2, SH110X_WHITE);
          display.setCursor(18, 2);
          display.setTextColor(SH110X_BLACK);
          display.print("RESULTADO PRUEBA");
          display.setTextColor(SH110X_WHITE);
          //RESULTADO PRUEBA HUMEDAD MINIMA
          display.setCursor(2, 15);
          display.print("ALTITUD MIN: ");
          display.print(minAltGraf); 
          display.println("mts");
          //RESULTADO PRUEBA HUMEDAD MAXIMA
          display.setCursor(2, 25);
          display.print("ALTITUD MAX: ");
          display.print(maxAltGraf);
          display.println("mts");
          //RESULTADO PRUEBA HUMEDAD MEDIA
          display.setCursor(2, 35);
          display.print("PROMEDIO: ");
          display.print((maxAltGraf + minAltGraf)/2);
          display.println("mts");
          
          display.fillRoundRect(1, 48, 128, 12, 2, SH110X_WHITE);
          display.setCursor(2, 50);
          display.setTextColor(SH110X_BLACK);
          display.print("PULSA 'OK' PARA SALIR");
          display.display();
            if (selector == 2){
              columna =0;
              contador =0;
              selector =0;
            }
        }
    #endif
  #endif
}
