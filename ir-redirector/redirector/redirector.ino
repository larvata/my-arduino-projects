#include <IRremote.h>

int RECV_PIN = 11;
int LED_ACTION = 13;
int LED_PIN = 12;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

bool redirect_flag;
unsigned long switch_off_start_timer;
bool redirect_active_flag;
// unsigned long switch_off_end_timer;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_ACTION, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void doRedirect(int command){
  switch (command) {
      case 0x2F0:
        Serial.println("UP");
        sendCommand(0x24DBC837);
        break;
      case 0xAF0:
        Serial.println("DOWN");
        sendCommand(0x24DBA857);
        break;
      case 0x2D0:
        Serial.println("LEFT");
        sendCommand(0x24DB22DD);
        break;
      case 0xCD0:
        Serial.println("RIGHT");
        sendCommand(0x24DB20DF);
        break;

      case 0x72E9:
        Serial.println("YELLOW");
        sendCommand(0x24DBA25D);
        break;
      case 0x12E9:
        Serial.println("BLUE");
        sendCommand(0x24DBA05F);
        break;
      case 0x52E9:
        Serial.println("RED");
        sendCommand(0x24DBC23D);
        break;
      case 0x32E9:
        Serial.println("GREEN");
        sendCommand(0x24DBC03F);
        break;

      case 0x1758:
        Serial.println("HOME");
        sendCommand(0x24DB40BF);
        break;

      case 0xA70:
        Serial.println("OK");
        sendCommand(0x24DB28D7);
        break;

      case 0x62E9:
        Serial.println("BACK");
        sendCommand(0x24DB629D);
        break;

      case 0xDD0:
        Serial.println("MENU");
        sendCommand(0x24DB609F);
        break;

      default:
        redirect_active_flag=false;
        break;
  }
}

void loop() {
  if(irrecv.decode(&results)){
    if((&results)->decode_type == SONY){
      // magie remoter
      Serial.println("SONY");

      redirect_active_flag=true;

      if((&results)->value == 0x5D0){

        Serial.println("SWITCH REDIRECTOR");
        // switch redirector
        redirect_flag=!redirect_flag;

        switch_off_start_timer=millis();

        delay(200);
      }
      else if(redirect_flag){
        digitalWrite(LED_ACTION, HIGH);
        
        if(redirect_flag&&redirect_active_flag){
          switch_off_start_timer=millis();
        }
        


        doRedirect((&results)->value);

        digitalWrite(LED_ACTION, LOW);
      }
      
    }
    irrecv.resume();

  }

  // auto turn off after no signal input
  if(redirect_flag){
    digitalWrite(LED_PIN, HIGH);

    // Serial.println(millis()-switch_off_start_timer);
    if(millis()-switch_off_start_timer>600000){
      Serial.println("timeout turn off");
      digitalWrite(LED_PIN, LOW);
      redirect_flag=false;
      redirect_active_flag=false;
    }
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }

}

void sendCommand(unsigned long data){
  for(int i=0;i<1;i++){
    irsend.sendNEC(data,32);
    
  }
  irrecv.enableIRIn();
  irrecv.resume();
  delay(100);
}


