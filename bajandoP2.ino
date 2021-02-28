void bajandoP2() {
  Serial.println("bajando a P2");
  digitalWrite(releBajar, HIGH);
  digitalWrite(releSubir, LOW);
  digitalWrite(cerradura1, LOW);
  digitalWrite(cerradura2, LOW);
  digitalWrite(cerradura3, LOW);

  leer(paro2, 4);
  if (estadosInputs[4] == true)
    estado = nivelPlanta2;

}
