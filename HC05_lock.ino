int const DELAY_TO_CLOSE = 30000;
const int RELAY = A5;

int data;
bool is_open = false;
unsigned long time_of_openning; 

/*
* Se inicializa el puerto de comunicacion serial y
* el pin analogo A5 para controlar el rele
*/
void setup()
{
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
}

/*
* Bucle principal
*/
void loop()
{
  // Verificar si la cerradura esta abierta
  // y pasaron 30 segundos para cerrarla automaticamente
  if (is_open && (millis() >= time_of_openning + DELAY_TO_CLOSE) )
  {
      digitalWrite(RELAY, LOW);
      is_open = false;
  }
  // Verificar si existen mensajes enviados por comunicacion serial
  while(Serial.available() > 0)
  {
    data = Serial.read();
    Serial.println(data);
  
    // Si el mensaje es 'A' abrir la cerradura (activar el rele)
    if(data == 'A')
    {
      is_open = true;
      time_of_openning = millis();
      digitalWrite(RELAY, HIGH);
    }
    // Si el mensaje es 'B' cerrar la cerradura (desactivar el rele)
    if(data == 'B')
    {
      is_open = false;
      digitalWrite(RELAY, LOW);
    }    
  }
}