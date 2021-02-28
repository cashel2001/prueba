void plantaP2() {
  Serial.println("ascensor nivel planta 2");
  digitalWrite(releBajar, LOW);
  digitalWrite(releSubir, LOW);
  digitalWrite(cerradura1, LOW);
  digitalWrite(cerradura3, LOW);

  if (tiempoCerradura2 - tiempoAnteriorCerradura2 < parametroTiempoCerradura)
  {
    digitalWrite(cerradura2, HIGH);
    flagCerradura2 = true;
  }
  else {
    digitalWrite(cerradura2, LOW);
    flagCerradura2 = false;

  }

    if ((estadosInputs[1] == true) && (flagCerradura2 == false)) {
    tiempoAnteriorCerradura2 = tiempoCerradura2;

  }

  if ((tiempoReenvio - tiempoAnteriorReenvio > parametroTiempoReenvio)&&(reenvio==true)) {
  
    estado = destinoBajandoP1;
  }

}
