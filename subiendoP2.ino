void subiendoP2() {
  Serial.println("Subiendo  a P2");
  digitalWrite(releBajar, LOW);
  digitalWrite(releSubir, HIGH);
  digitalWrite(cerradura1, LOW);
  digitalWrite(cerradura2, LOW);
  digitalWrite(cerradura3, LOW);

  leer(paro2, 4);
  if (estadosInputs[4] == true)
    estado = nivelPlanta2;

}
