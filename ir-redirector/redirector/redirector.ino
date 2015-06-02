#include <IRremote.h>

int RECV_PIN = 11;
int LED_PIN = 13;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    digitalWrite(LED_PIN, HIGH);
    for(int i=0;i<4;i++){
      irsend.sendSony(0xa50,12);
      delay(40);
    }
    irrecv.enableIRIn();
    irrecv.resume(); // Receive the next value
  }
  digitalWrite(LED_PIN, LOW);
  delay(100);
}


