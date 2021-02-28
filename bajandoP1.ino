void bajandoP1(){
  Serial.println("bajando a P1");
  digitalWrite(releBajar, HIGH);
  digitalWrite(releSubir, LOW);
  digitalWrite(cerradura1, LOW);
  digitalWrite(cerradura2, LOW);
  digitalWrite(cerradura3, LOW);

  leer(paro1,3);
  if (estadosInputs[3] == true)
  estado=nivelPlanta1;
  
}
