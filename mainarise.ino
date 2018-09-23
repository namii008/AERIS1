#include<SoftwareSerial.h>
#include<LiquidCrystal.h>
SoftwareSerial gsm(6, 7);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Threshold;  // whether the string is complete

String textmessage;


void setup()


{

  lcd.begin(16, 2);

  lcd.print(" Project ARIES");
  pinMode(A0, INPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9,LOW);
  delay(10000);
  Serial.begin(9600);
  gsm.begin(9600);
  gsm.println("AT+CMGF=1");
    delay(5000);

}
void loop()
{

{
  if(gsm.available()>0){
    textmessage=gsm.readString();
    textmessage.toLowerCase();
    delay(10);}
    if(textmessage.indexOf("rainy")>=0){
      Threshold=400;
      textmessage="";
    }
    else 
    {Threshold=750;
    textmessage="";
    }
  }
  

//lcd.clear();
  //  lcd.setCursor(0, 1);
  //  lcd.print(Threshold);
//delay(500);



  int val = analogRead(A0);


  if (val > Threshold)
  {
    lcd.setCursor(0, 1);
    lcd.print("M LOW");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("S MSG");
    //gsm.println("AT+CMGF=1");
    //delay(5000);

    gsm.println("AT+CMGS=\"+918559877405\"\r");
    gsm.println("Moisture is low ,turning motor on");
    delay(1000);

    gsm.println((char)26);
    delay(5000);

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("MM ON");
    do { 
      digitalWrite(9, HIGH);
      delay(5000);
      val = analogRead(A0);
    } while (val > Threshold);
    lcd.clear();
  }
  else
  {
    lcd.clear();
    gsm.println("AT+CMGF=1");
    delay(5000);

    gsm.println("AT+CMGS=\"+918559877405\"\r");
    gsm.println("Soil is in good condition, Motor is turning off ");
    delay(1000);

    gsm.println((char)26);
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("M Good");
    while (val < Threshold) {
      digitalWrite(9, LOW);
      val = analogRead(A0);
    }

  }
  lcd.clear();
}



