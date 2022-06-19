#include "pitches.h"
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

#include <PS2Mouse.h>

#define MDATA 12
#define MCLK 13
#define SENSIVITY 12

PS2Mouse mouse_one(MCLK, MDATA, REMOTE);
bool noteSession = false;

/*
int notes[12]={ C,  C#,   D,   D#,  E,   F,   F#,  G,   G#,  A,   A#,  B};
int notes[12] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
*/
//int notes[12]={   E,  B ,   A,   G,   D,   E,   B,   A,   G,   A,   E ,  B};
int notesmd[12] = {330, 494, 440, 392, 294, 330, 494, 440, 392, 440, 330, 494};

//int notes[12]={   C,   A# , G#,  G,   D#,  F,   D,   C,   G,   A#,  G# , D#};
int notesds[12] = {262, 466, 415, 392, 311, 349, 294, 262, 392, 466, 415, 311};

int notes_x_C[12]={NOTE_C4, NOTE_C5, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_C5};
int notes_x_D[12]={NOTE_D4, NOTE_D5, NOTE_FS4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_D5, NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_D5};
int notes_x_E[12]={NOTE_E4, NOTE_E5, NOTE_GS4, NOTE_B4, NOTE_CS4, NOTE_B4, NOTE_CS4, NOTE_E5, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_E5};
int notes_x_F[12]={NOTE_F4, NOTE_F5, NOTE_A4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_F5, NOTE_G4, NOTE_A4, NOTE_C4, NOTE_F5};
int notes_x_G[12]={NOTE_G4, NOTE_G5, NOTE_B4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G5, NOTE_A4, NOTE_B4, NOTE_D4, NOTE_G5};
int notes_x_A[12]={NOTE_A4, NOTE_A5, NOTE_CS4, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_A5, NOTE_B4, NOTE_CS4, NOTE_E4, NOTE_A5};
int notes_x_B[12]={NOTE_B4, NOTE_B5, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_GS4, NOTE_B5, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_B5};

int notes_y_C[12]={NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_C4};
int notes_y_D[12]={NOTE_A4, NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_B4, NOTE_FS4, NOTE_A4, NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_FS4, NOTE_D4};
int notes_y_E[12]={NOTE_B4, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_CS4, NOTE_GS4, NOTE_B4, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_GS4, NOTE_E4};
int notes_y_F[12]={NOTE_C4, NOTE_G4, NOTE_A4, NOTE_C4, NOTE_D4, NOTE_A4, NOTE_C4, NOTE_G4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_F4};
int notes_y_G[12]={NOTE_D4, NOTE_A4, NOTE_B4, NOTE_D4, NOTE_E4, NOTE_B4, NOTE_D4, NOTE_A4, NOTE_B4, NOTE_D4, NOTE_B4, NOTE_G4};
int notes_y_A[12]={NOTE_E4, NOTE_B4, NOTE_CS4, NOTE_E4, NOTE_FS4, NOTE_CS4, NOTE_E4, NOTE_B4, NOTE_CS4, NOTE_E4, NOTE_CS4, NOTE_A4};
int notes_y_B[12]={NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_B4};





int curnote, oldX, oldY;
double octave = 1;

/*int lcd_notes[8] = {"c", "d", "e", "f", "g", "a", "b", "kaif"};*/

LiquidCrystal_PCF8574 lcd(0x27);  // Устанавливаем дисплей 

void setup() {
   Serial.begin(9600);   
   mouse_one.initialize(); 
   pinMode(11, OUTPUT);             //  выход на динамик
            
    // input pins
    pinMode(2, INPUT);// Button 1 input pin 2  
    pinMode(3, INPUT);// Button 2 input pin 3  
    pinMode(4, INPUT);// Button 3 input pin 4  
    pinMode(5, INPUT);// Button 4 input pin 5 
    pinMode(6, INPUT);// Button 5 input pin 6  
    pinMode(7, INPUT);// Button 6 input pin 7  
    pinMode(8, INPUT);// Button 7 input pin 8  
    pinMode(9, INPUT);// Button 8 input pin 9

lcd.begin(16, 2);// у нас экран 16 столбцов на 2 строки
lcd.setBacklight(255); //установить яркость подсветки на максимум
lcd.clear(); // очистить экран и установить курсор в позицию 0, 0
lcd.print("*******");// печатаем нужную строку
delay(1000);

lcd.clear();

lcd.print("******8");// печатаем нужную строку
delay(1000);

lcd.clear();

lcd.print("*****08");// печатаем нужную строку
delay(1000);

lcd.clear();

lcd.print("****608");// печатаем нужную строку
delay(1000);

lcd.clear();

lcd.print("***5608");// печатаем нужную строку
delay(1000);

lcd.clear();

lcd.print("**55608");// печатаем нужную строку
delay(1000);

lcd.clear();

lcd.print("*355608");// печатаем нужную строку
delay(1000);

lcd.clear();

lcd.print("7355608");// печатаем нужную строку
delay(1000);

lcd.setCursor(0, 1);// переводим курсор в нужную позицию
lcd.print("Gigos");// печатаем нужную строку

 /* lcd.setCursor(1, 0);     // ставим курсор на 1 символ первой строки
  lcd.print("iarduino.ru");
  lcd.setCursor(8, 1);
  lcd.print("LCD 1602");*/
}

void loop() {

  int ton;
  // button 1 action
 for (int b=2; b<10; b++){
    if(digitalRead(b)){
      if(b==2)
      {
        for (int x_C=0;x_C<12; x_C++)
        {
           notesmd[x_C] = notes_x_C[x_C];
        }
        {
          for (int y_C=0; y_C<12; y_C++)
          {
            notesds[y_C] = notes_y_C[y_C];
          }
        }
      }
      if(b==3)
      {
        for (int x_D=0;x_D<12; x_D++)
        {
           notesmd[x_D] = notes_x_D[x_D];
        }
        {
          for (int y_D=0; y_D<12; y_D++)
          {
            notesds[y_D] = notes_y_D[y_D];
          }
        }
      }
      if(b==4)
      {
        for (int x_E=0;x_E<12; x_E++)
        {
           notesmd[x_E] = notes_x_E[x_E];
        }
        {
          for (int y_E=0; y_E<12; y_E++)
          {
            notesds[y_E] = notes_y_E[y_E];
          }
        }
      }
      if(b==5)
      {
        for (int x_F=0;x_F<12; x_F++)
        {
           notesmd[x_F] = notes_x_F[x_F];
        }
        {
          for (int y_F=0; y_F<12; y_F++)
          {
            notesds[y_F] = notes_y_F[y_F];
          }
        }
      }
      if(b==6)
      {
        for (int x_G=0;x_G<12; x_G++)
        {
           notesmd[x_G] = notes_x_G[x_G];
        }
        {
          for (int y_G=0; y_G<12; y_G++)
          {
            notesds[y_G] = notes_y_G[y_G];
          }
        }
      }
      if(b==7)
      {
        for (int x_A=0;x_A<12; x_A++)
        {
           notesmd[x_A] = notes_x_A[x_A];
        }
        {
          for (int y_A=0; y_A<12; y_A++)
          {
            notesds[y_A] = notes_y_A[y_A];
          }
        }
      }
      if(b==8)
      {
        for (int x_B=0;x_B<12; x_B++)
        {
           notesmd[x_B] = notes_x_B[x_B];
        }
        {
          for (int y_B=0; y_B<12; y_B++)
          {
            notesds[y_B] = notes_y_B[y_B];
          }
        }
      }
 
 
 
 
 /* for (int b=2; b<10; b++){
    if(digitalRead(b){
      
        notesmd[0] = b*262; 
        notesmd[1] = b*277;
        notesmd[2] = b*294;
        notesmd[3] = b*311;
        notesmd[4] = b*330;
        notesmd[5] = b*349;
        notesmd[6] = b*370;
        notesmd[7] = b*392;
        notesmd[8] = b*415;
        notesmd[9] = b*440;
        notesmd[10] = b*466;
        notesmd[11] = b*494;*/

      lcd.clear();
     /* lcd.print(lcd_notes[b]); */
     if (b==2)
     {
      lcd.print("C");
     }
     if (b==3)
     {
      lcd.print("D");
     }
     if (b==4)
     {
      lcd.print("E");
     }
     if (b==5)
     {
      lcd.print("F");
     }
     if (b==6)
     {
      lcd.print("G");
     }
     if (b==7)
     {
      lcd.print("A");
     }
     if (b==8)
     {
      lcd.print("B");
     }
     if (b==9)
     {
      lcd.print("KAIF");
     }
      /*  notesmd[] = {b*330, b*494, b*440, b*392, b*294, b*330, b*494, b*440, b*392, b*440, b*330, b*494};
        notesds[] = {b*262, b*466, b*415, b*392, b*311, b*349, b*294, b*262, b*392, b*466, b*415, b*311};*/
       
  // Устанавливаем курсор на вторую строку и нулевой символ.


  
  /*lcd.setCursor(0, 1);
  int lcd_notes[12] = {"C","D", "E", "F", "G", "A", "B", "C#", "D#", "F#", "G#", "A#"};
  lcd.print(lcd_notes[b]);
  delay(1000);*/
 
  
  /* Выводим на экран количество секунд с момента запуска ардуины
  lcd.print(millis()/1000);*/
    }
  }
  int data[2];
  mouse_one.report(data);
  Serial.print(data[0]); // Status Byte
  Serial.print(":");
  Serial.print(data[1]); // X Movement Data
  Serial.print(",");
  Serial.print(data[2]); // Y Movement Data
  Serial.println();

  if(data[0]==8&&data[1]==0&&data[2]==0) { noTone(11); noteSession = false; }
  else {
    noteSession = true;
  }

  if(noteSession) {
    curnote = 0;
    octave = 1;
    oldX = data[1];
    oldY = data[2];
    while(!(data[0]==8&&data[1]==0&&data[2]==0))
    {
      if(data[1]>10) curnote++;
      if(data[1]<-10) curnote--;
      if(data[2]<-5) octave /=2;
      else if(data[2]>5) octave *=2;
      if(octave>5) octave = 4;
      if(octave<1/5) octave = 1/4;
      tone(11, notesmd[abs(curnote)%12]*octave);
      
      Serial.print(curnote);
      Serial.print(":");
      Serial.print(octave);
      Serial.print(",");
      Serial.print(notesds[abs(curnote)%12]*octave);
      Serial.println();

      delay(100);
      mouse_one.report(data);

    }
  }
  
  delay(100);
}
