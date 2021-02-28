void plantaP3() {
  Serial.println("ascensor nivel planta 3");
  digitalWrite(releBajar, LOW);
  digitalWrite(releSubir, LOW);
  digitalWrite(cerradura1, LOW);
  digitalWrite(cerradura2, LOW);


  if (tiempoCerradura3 - tiempoAnteriorCerradura3 < parametroTiempoCerradura)
  {
    digitalWrite(cerradura3, HIGH);
    flagCerradura3 = true;
  }
  else {
    digitalWrite(cerradura3, LOW);
    flagCerradura3 = false;
  }

  if ((estadosInputs[2] == true) && (flagCerradura3 == false)) {
    tiempoAnteriorCerradura3 = tiempoCerradura3;

  }
  if ((tiempoReenvio - tiempoAnteriorReenvio > parametroTiempoReenvio)&&(reenvio==true)) {

    estado = destinoBajandoP1;
  }
}
