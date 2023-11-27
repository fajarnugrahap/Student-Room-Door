#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>

#define RELAY_PIN  A4 // the Arduino pin, which connects to the IN pin of relay
#define ROW_NUM    4  // four rows
#define COLUMN_NUM 4  // four columns
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {A1, A2, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password_1 = "ABC1234"; // change your password here
const String password_2 = "5642B";  // change your password here
const String password_3 = "9765";   // change your password here
const String password_4 = "120702";
String input_password;

const int BUTTON_PIN = A3;
int currentState;
void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  input_password.reserve(32); // maximum password size is 32, change if needed
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
  digitalWrite(RELAY_PIN, HIGH);
  
}

void loop() {
  rfid();
  pushbutton();
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = ""; // reset the input password
    } else if (key == '#') {
      //if (input_password == password_1 || input_password == password_2 || input_password == password_3)
      if (input_password == password_4) {
        Serial.println("The password is correct, turning ON relay");
        digitalWrite(RELAY_PIN, LOW);
        delay(3000);
        digitalWrite(RELAY_PIN, HIGH);
      } else {
        Serial.println("The password is incorrect, try again");
      }

      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}

void rfid(){
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "EA 6C C9 83") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
    digitalWrite(RELAY_PIN, HIGH);
  }

  else if (content.substring(1) == "8A 76 8F B1") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
    digitalWrite(RELAY_PIN, HIGH);
  }

  else if (content.substring(1) == "F3 C1 4D 06") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
    digitalWrite(RELAY_PIN, HIGH);
  }

  else if (content.substring(1) == "04 5E 8E B2 BA 61 80") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
    digitalWrite(RELAY_PIN, HIGH);
  }
 else   {
    Serial.println(" Access denied");
  }
}

void pushbutton(){
  currentState = digitalRead(BUTTON_PIN);
  if(currentState == LOW){
    digitalWrite(RELAY_PIN, LOW);
    delay(3000);
    digitalWrite(RELAY_PIN, HIGH);
  } 
}
