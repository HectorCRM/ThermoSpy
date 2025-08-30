void lecturaTempGrafDs18b20(){
  #ifdef ds18b20
  sensors.requestTemperatures();
    tempGraficas = sensors.getTempCByIndex(0);
    tempGrafica = map(tempGraficas, -10, 40, 64, 15);
    //float minima; //lineas 243 a 253
    //float maxima;
    if (tempGraficas < minimaGraficas){
      minimaGraficas = tempGraficas;
    }
    if (tempGraficas > maximaGraficas){
      maximaGraficas = tempGraficas;
    }
  #endif
}
//Lectura valores BME280 para generar graficas
void lecturaTempBME(){
  //Lectura temperatura
  tempGraf = bme.readTemperature();
  mapTempGraf = map(tempGraf, -10, 40, 64, 15);
  if (tempGraf < tempMinGraf){
      tempMinGraf = tempGraf;
    }
    if (tempGraf > tempMaxGraf){
      tempMaxGraf = tempGraf;
    }
}
void lecturaHumBME(){
  //Lectura humedad
  humGraf = bme.readHumidity();
  mapHumGraf = map(humGraf, 0, 100, 64, 15);
  if (humGraf < minHumGraf){
      minHumGraf = humGraf;
    }
    if (humGraf > maxHumGraf){
      maxHumGraf = humGraf;
    }
}
void lecturaPresBME(){
  //Lectura presion atmosferica
  presGraf = (bme.readPressure() / 100.0F);
  mapPresGraf = map(presGraf, 1013, 701, 15, 64);
  if (presGraf < minPresGraf){
      minPresGraf = presGraf;
    }
    if (presGraf > maxPresGraf){
      maxPresGraf = presGraf;
    }
}
void lecturaAltBME(){
  //Lectura altitud
  altGraf = bme.readAltitude(PresionNivelMar_HPA);
  mapAltGraf = map(altGraf, 0, 1500, 64, 15);
  if (altGraf < minAltGraf){
      minAltGraf = altGraf;
    }
    if (altGraf > maxAltGraf){
      maxAltGraf = altGraf;
    }
}
