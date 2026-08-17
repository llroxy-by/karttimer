#include <TFT_eSPI.h>
#include <Fonts/Formula1_Display_Regular_44.h>


const int led1pin = 13;
const int led2pin = 12;
const int led3pin = 14;
const int led4pin = 27;    
const int led5pin = 26;    
const int leftbottom = 25;
const int rightbottom = 33;
const int speaker = 32;    
const int button = 19;
bool flag=0;
int state = 0;
unsigned long starttime;
unsigned long stoptime;
unsigned long duration;
unsigned long nowtime;
unsigned long finaltime;
unsigned long lastDraw = 0;   
int minutes;
int seconds;
int milliseconds;



TFT_eSPI tft = TFT_eSPI();
TFT_eSprite timeSprite = TFT_eSprite(&tft);   

bool bottonpress(){

		bool buttonState=digitalRead(button);
		
		if(flag == 1){
      return 0;
			
		}
		if(digitalRead(button)==LOW){
      flag = 1;
			return 1;
			
		}else{
      flag=0;
			return 0;
			
		}
	}





void allHigh() {
  digitalWrite(led1pin, HIGH);
  digitalWrite(led2pin, HIGH);
  digitalWrite(led3pin, HIGH);
  digitalWrite(led4pin, HIGH);
  digitalWrite(led5pin, HIGH);
}

void allLow() {
  digitalWrite(led1pin, LOW);
  digitalWrite(led2pin, LOW);
  digitalWrite(led3pin, LOW);
  digitalWrite(led4pin, LOW);
  digitalWrite(led5pin, LOW);
}

void speak(){
  tone(speaker, 800, 500);  // 响 500ms（三参数版自带定时停止）
}

void setup() {

  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
  pinMode(led4pin, OUTPUT);
  pinMode(led5pin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  allLow();

tone(speaker, 262, 500);  // 1 Do
  delay(600);

  tone(speaker , 262, 500);  // 1 Do
  delay(600);

  tone(speaker, 392, 500);  // 5 Sol
  delay(600);

  tone(speaker, 392, 500);  // 5 Sol
  delay(600);

  tone(speaker, 440, 500);  // 6 La
  delay(600);

  tone(speaker, 440, 500);  // 6 La
  delay(600);

  tone(speaker, 392, 1000); // 5 Sol
  delay(1100);




  tft.init();
  tft.setRotation(4);
  tft.loadFont(Formula1_Display_Regular_44);
  tft.setTextDatum(MC_DATUM);   
  tft.fillScreen(TFT_YELLOW);
  tft.setTextColor(TFT_BLACK, TFT_YELLOW);
  tft.drawString("READY", 120, 120);   

  timeSprite.createSprite(240, 55);    
  timeSprite.loadFont(Formula1_Display_Regular_44);   

  Serial.begin(115200);

}


void loop() {

  Serial.printf("botton = %d,flag = %d \n",digitalRead(button), flag );

  
  if (bottonpress() == true)
    {
      if (state == 0)
      {
        state = 1;
        
      }
      else if (state == 2)
      {
        stoptime = millis();
        finaltime = stoptime - starttime;
        tft.fillScreen(TFT_BLUE);
        tft.setTextColor(TFT_BLACK, TFT_BLUE);
        minutes = finaltime / 60000;
        seconds = (finaltime % 60000) / 1000;
        milliseconds = finaltime % 1000;
        char buf[32];
        sprintf(buf, "%d:%02d.%03d", minutes, seconds, milliseconds);
        tft.drawString("FINAL", 120, 95);      // 第一行：标题（一行放不下就分两行）
        tft.drawString(buf, 120, 135);         // 第二行：时间
        tone(speaker, 440, 500);  // 6 La
        delay(600);

        state = 3;
      }
      else if (state == 3)
      {
        tft.fillScreen(TFT_RED);
        tft.setTextColor(TFT_BLACK, TFT_RED);
        tft.drawString("READY", 120, 120);
        state = 0;
        tone(speaker, 392, 500);  // 5 Sol
        delay(600);
      }
    };

  if (state == 1)
    {
       tft.fillScreen(TFT_GREEN);
       digitalWrite(led1pin,HIGH);
        speak();
        delay(1000);
      digitalWrite(led2pin,HIGH);
        speak();
        delay(1000);
      digitalWrite(led3pin,HIGH);
        speak();
        delay(1000);
       digitalWrite(led4pin,HIGH);
        speak();
        delay(1000);
      digitalWrite(led5pin,HIGH);
        speak();
        delay(1000);
      allLow();
        speak();
        delay(1000);
        speak();
      starttime = millis();
      state = 2;
      
    };

    if (state == 2)
      {
        nowtime = millis();
        duration = nowtime - starttime;   

        if (millis() - lastDraw >= 30) {
          lastDraw = millis();
          minutes = duration / 60000;
          seconds = (duration % 60000) / 1000;
          milliseconds = duration % 1000;
          char buf[32];
          sprintf(buf, "%d:%02d.%03d", minutes, seconds, milliseconds);
          timeSprite.fillSprite(TFT_RED);             
          timeSprite.setTextColor(TFT_BLACK, TFT_RED);
          timeSprite.setTextDatum(MC_DATUM);
          timeSprite.drawString(buf, 120, 27);         
          timeSprite.pushSprite(0, 95);             
        }
      }



  if (digitalRead(button) == HIGH)
    {
      flag = 0;
    };
}
