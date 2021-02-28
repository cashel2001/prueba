void plantaP1() {
  Serial.println("ascensor nivel planta 1");
  digitalWrite(releBajar, LOW);
  digitalWrite(releSubir, LOW);
  digitalWrite(cerradura2, LOW);
  digitalWrite(cerradura3, LOW);

  if (tiempoCerradura1 - tiempoAnteriorCerradura1 < parametroTiempoCerradura)
  {
    digitalWrite(cerradura1, HIGH);
    flagCerradura1 = true;
  }
  else {
    digitalWrite(cerradura1, LOW);
    flagCerradura1 = false;

  }
      if ((estadosInputs[0] == true) && (flagCerradura1 == false)) { //si la plataforma se encuentra en planta, con la cerradura sin excitar y se pulsa el pulsador de su planta ==> manda abrir puertas el tiempo programado
    tiempoAnteriorCerradura1 = tiempoCerradura1;

  }

}
