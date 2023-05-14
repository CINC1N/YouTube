#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include<Servo.h>
Servo Servo1;
int servoPin=9;
int angle=0;

//code for OLED
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//code for keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {10, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char s[22]="Sifra (*=.):";
char password[10]="30*7*2019";
char input[10];
int counter=0;
int motor_state=0;

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 
  Servo1.attach(servoPin);
  Servo1.write(angle); 
  Serial.begin(9600);
}

void loop(){
  display.clearDisplay(); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(s);
  display.display();
  char key[2];
  key[0] = keypad.getKey();
  if (key[0]){
    Serial.println(key[0]);
    input[counter]=key[0];
    counter++;
  }
  key[1]='\0';
  strcat(s,key);
  if(counter==9){
    input[9]='\0';
    if(strcmp(input,password)==0){
      motor_state++;
      if((motor_state%2)==1){
        Servo1.write(angle+100);
      }
      if((motor_state==0)){
        Servo1.write(angle);
      }
      display.clearDisplay(); 
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Tacna sifra, mozete uzeti poklon ^_^");
      display.display();
      delay(4000); 
      counter=0;
    }
    else{
      counter=0;
      strcpy(s,"Sifra (*=.):");
      display.clearDisplay(); 
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Netacna sifra, probajte ponovo :(");
      display.display();
      delay(4000);  
    } 
  }
}
