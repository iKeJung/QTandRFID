#include <LiquidCrystal.h>


/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
 *----------------------------------------------------------------------------- empty_skull 
 * Aggiunti pin per arduino Mega
 * add pin configuration for arduino mega
 * http://mac86project.altervista.org/
 ----------------------------------------------------------------------------- Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     8               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK
 *
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Ethernet.h>

#define SS_PIN 8
#define RST_PIN 9
void mensageminicial();
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Create LCD instance.

byte mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[]      = { 192,168,1,160};
//byte ip[]      = { 169,254,222,70};
byte gateway[] = { 192, 168, 1, 1};
byte subnet[]  = { 255, 255, 255, 0};
IPAddress server(192,168,1,155);

EthernetClient client;

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  lcd.begin(16, 2);
  mensageminicial(); 
  Ethernet.begin(mac, ip, gateway, subnet);
  delay(1000);
  
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String conteudo= "";
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println("");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(conteudo);
  if (client.connect(server, 2222)) {
    Serial.println("connected");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  String nome = "";
  if (client.connected()) {
      Serial.println("Waiting");
      /*while(!client.available()){
        
      }*/
      while(client.available()){
        char c = client.read();
        Serial.print(c);
      }
      Serial.println("Finished Waiting");
      delay(2);
      client.print(conteudo);
      delay(2);
      
      while(!client.available()){
        
      }
      while(client.available()){
        char c = client.read();
        nome.concat(c);
      }
  }
  Serial.println(nome);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(nome);
  conteudo = "";
  client.stop();
  
  delay(500);
  mensageminicial();
}

void mensageminicial()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}
