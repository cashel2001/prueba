void subiendoP3() {
  Serial.println("Subiendo  a P3");
  digitalWrite(releBajar, LOW);
  digitalWrite(releSubir, HIGH);
  digitalWrite(cerradura1, LOW);
  digitalWrite(cerradura2, LOW);
  digitalWrite(cerradura3, LOW);

  leer(paro3, 5);
  if (estadosInputs[5] == true)
    estado = nivelPlanta3;
}
