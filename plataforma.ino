boolean reenvio = true; //variable de reenvio activado o desactivado
boolean pulsacionConstante = false; //variable que indica si la maniobra se realiza con pulsacion constante o no


boolean flagCerradura1 = false; // variable que guarda el estado actual de la cerraduras
boolean flagCerradura2 = false; // variable que guarda el estado actual de la cerraduras
boolean flagCerradura3 = false; // variable que guarda el estado actual de la cerraduras

unsigned long parametroTiempoCerradura = 3000; // parametro que indica el tiempo que estará excitada la cerradura cuando llega a la planta correspondiente (3sg)
unsigned long tiempoCerradura1 = 0; //variable que calcula el tiempo que transcurrido de excitacion de cerraduras.
unsigned long tiempoAnteriorCerradura1 = 0;
unsigned long tiempoCerradura2 = 0; //variable que calcula el tiempo que transcurrido de excitacion de cerraduras.
unsigned long tiempoAnteriorCerradura2 = 0;
unsigned long tiempoCerradura3 = 0; //variable que calcula el tiempo que transcurrido de excitacion de cerraduras.
unsigned long tiempoAnteriorCerradura3 = 0;

unsigned long parametroTiempoReenvio = 5000; // parametro que indica el tiempo programado para reenvio a planta 1 (5sg)
unsigned long tiempoReenvio = 0; //variable que calcula el tiempo que transcurrido para realizar el reenvio.
unsigned long tiempoAnteriorReenvio = 0;


boolean estadosInputs[9] = {false, false, false, false, false, false, false, false, false}; //array que me guarda los estados de las diferentes entradas
byte contadores[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //array de contadores para evitar rebotes en los pulsadores; pulsador1,pulsador2,pulsador3,paro1,paro2,paro2

enum ESTADOS {estadoIndeterminado, nivelPlanta1, destinoSubiendoP2, nivelPlanta2, destinoBajandoP1, destinoSubiendoP3, nivelPlanta3, destinoBajandoP2, averia}; //enumeramos todos los estados posibles de la plataforma
byte estado = indeterminado; //cuando hacemos reset iniciamos el software en el estado indeterminado

const byte pulsador1 = 2; //Pulsador planta 1(INPUT)
const byte pulsador2 = 3; //Pulsador planta 2 (INPUT)
const byte pulsador3 = 4; //Pulsador planta 3 (INPUT)
const byte paro1 = 5; //Sensor paro en planta 1(INPUT)
const byte paro2 = 6; //Sensor paro en planta 2 (INPUT)
const byte paro3 = 7; //Sensor paro en planta 3 (INPUT)
const byte seguridades = 8; // Señal correspondientes a todas las seguridades cerradas(INPUT)


const byte releSubir = 9; //reled de mando subir (OUTPUT)
const byte releBajar = 10; //rele de mando bajar (OUTPUT)
const byte cerradura1 = 11; //señal de cerradura1 (OUTPUT)
const byte cerradura2 = 12; //señal de cerradura2 (OUTPUT)
const byte cerradura3 = 13; //señal de cerradura3 (OUTPUT)

void setup() {

  Serial.begin(9600);
  pinMode(pulsador1, INPUT);
  pinMode(pulsador2, INPUT);
  pinMode(pulsador3, INPUT);
  pinMode(paro1, INPUT);
  pinMode(paro2, INPUT);
  pinMode(paro3, INPUT);
  pinMode(seguridades, INPUT);
  pinMode(releSubir, OUTPUT);
  pinMode(releBajar, OUTPUT);
  pinMode(cerradura1, OUTPUT);
  pinMode(cerradura2, OUTPUT);
  pinMode(cerradura3, OUTPUT);


}

void loop() {
  leer(pulsador1, 0);
  leer(pulsador2, 1);
  leer(pulsador3, 2);
  leer(seguridades,6);

  tiempoCerradura1 = millis();
  tiempoCerradura2 = millis();
  tiempoCerradura3 = millis();
  tiempoReenvio = millis();

  switch (estado) {
    case estadoIndeterminado:
      //delay (1500); //espero 1.5sg y mando corregir a planta 1
      //estado = destinoBajandoP1;
      if (estadosInputs[0] == true)  {
        estado = destinoBajandoP1;
        tiempoAnteriorReenvio = tiempoReenvio;
      }
      if (estadosInputs[1] == true)  {
        estado = destinoSubiendoP2;
        tiempoAnteriorReenvio = tiempoReenvio;
      }
      if (estadosInputs[2] == true)  {
        estado = destinoSubiendoP3;
        tiempoAnteriorReenvio = tiempoReenvio;
      }



      break;

    case nivelPlanta1:
      plantaP1();
      if (estadosInputs[1] == true) {

        estado = destinoSubiendoP2;
      }
      if (estadosInputs[2] == true) {
        estado = destinoSubiendoP3;
      }

      break;

    case destinoSubiendoP2:
      if (estadosInputs[6] == true) {
        tiempoAnteriorReenvio = tiempoReenvio;
        tiempoAnteriorCerradura2 = tiempoCerradura2; // asignamos el tiempo actual en el momento de pasar al estado correspondiente
        subiendoP2();
      }

      else{
        estado=estadoIndeterminado;
      }

      break;

    case nivelPlanta2:
        plantaP2();
        if (estadosInputs[0] == true) {
          estado = destinoBajandoP1;
        }
      if (estadosInputs[2] == true) {
        estado = destinoSubiendoP3;
      }

      break;


    case destinoBajandoP1:
        tiempoAnteriorReenvio = tiempoReenvio;
        tiempoAnteriorCerradura1 = tiempoCerradura1; // asignamos el tiempo actual en el momento de pasar al estado correspondiente
        bajandoP1();
        break;


      case destinoSubiendoP3:
          tiempoAnteriorReenvio = tiempoReenvio;
          tiempoAnteriorCerradura3 = tiempoCerradura3; // asignamos el tiempo actual en el momento de pasar al estado correspondiente
          subiendoP3();
          break;

        case nivelPlanta3:

            plantaP3();


            if (estadosInputs[0] == true) {
              estado = destinoBajandoP1;
            }


      if (estadosInputs[1] == true) {
        estado = destinoBajandoP2;
      }
      break;

    case destinoBajandoP2:
        tiempoAnteriorReenvio = tiempoReenvio;
        tiempoAnteriorCerradura2 = tiempoCerradura2; // asignamos el tiempo actual en el momento de pasar al estado correspondiente
        bajandoP2;
        break;

      case averia:
          break;
        }

}

void leer(int pulsador, int posicion) {
  if (digitalRead(pulsador) == true) {
    contadores[posicion] = contadores[posicion] + 1;
    if (contadores[posicion] > 8) { // con el valor regulamos el rebote del pulsador
      estadosInputs[posicion] = true;
      contadores[posicion] = 0;
    }
  }

  else {
    contadores[posicion] = 0;
    estadosInputs[posicion] = false;

  }
}
