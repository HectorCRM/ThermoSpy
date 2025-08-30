void lecturaDS18B20(){
  #ifdef ds18b20
  sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    //float minima; //lineas 243 a 253
    //float maxima;
    if (temp < minima){
      minima = temp;
    }
    if (temp > maxima){
      maxima = temp;
    }
    #endif
}

void lecturaBME280(){
  //Lectura temperatura
  temp = bme.readTemperature();
  if (temp < tempMinima){
      tempMinima = temp;
    }
    if (temp > tempMaxima){
      tempMaxima = temp;
    }
  //Lectura humedad
  humedad = bme.readHumidity();
  if (humedad < humedadMinima){
      humedadMinima = humedad;
    }
    if (humedad > humedadMaxima){
      humedadMaxima = humedad;
    }
  //Lectura presion atmosferica
  presion = (bme.readPressure() / 100.0F);
  if (presion < presionMinima){
      presionMinima = presion;
    }
    if (presion > presionMaxima){
      presionMaxima = presion;
    }
  //Lectura altitud
  altura = bme.readAltitude(PresionNivelMar_HPA);
  if (altura < alturaMinima){
      alturaMinima = altura;
    }
    if (altura > alturaMaxima){
      alturaMaxima = altura;
    }

}
