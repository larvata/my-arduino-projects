#include <IRremote.h>

int RECV_PIN = 11;
int LED_PIN = 13;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

bool redirect_flag; 

// TODO: additional led for signal flag

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if(irrecv.decode(&results)){
      if((&results)->decode_type == SONY){
        // magie remoter
        Serial.println("SONY");

        if((&results)->value == 0x5D0){
          Serial.println("SWITCH REDIRECTOR");
          // switch redirector
          redirect_flag=!redirect_flag;

          if(redirect_flag){
            digitalWrite(LED_PIN, HIGH);
          }
          else{
            digitalWrite(LED_PIN, LOW);
          }
          delay(200);
        }
        else if(redirect_flag){
          switch ((&results)->value) {

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
                // do something
                break;
          }

        }
        
      }
      irrecv.resume();



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











