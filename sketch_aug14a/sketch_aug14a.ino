#include <TFT_eSPI.h>
#include <Fonts/Formula1_Display_Regular_48.h>


const int led1pin = 13;
const int led2pin = 12;
const int led3pin = 14;
const int led4pin = 27;    
const int led5pin = 26;    
const int leftbottom = 25;
const int rightbottom = 33;
const int speaker = 32;    
const int button = 35;
bool flag=0;
int state = 0;
unsigned long starttime;
unsigned long stoptime;
unsigned long duration;
unsigned long nowtime;
unsigned long finaltime;
int minutes;
int seconds;
int milliseconds;





TFT_eSPI tft = TFT_eSPI();

bool bottonpress(){
、
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
  digitalWrite(speaker,HIGH);
  delay(100);
  digitalWrite(speaker,LOW);
}

void setup() {

  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
  pinMode(led4pin, OUTPUT);
  pinMode(led5pin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  allLow();


  tft.init();
  tft.setRotation(4);
  tft.loadFont(Formula1_Display_Regular_48);
  tft.fillScreen(TFT_YELLOW);
  tft.setTextColor(TFT_BLACK, TFT_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(20, 100);
  tft.println("1234567890");

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
        tft.fillRect(0, 90, 180, 50, TFT_BLUE);
        tft.setCursor(20, 100);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK, TFT_BLUE);
        minutes = finaltime / 60000;
        seconds = (finaltime % 60000) / 1000;
        milliseconds = finaltime % 1000;
        tft.printf("Finaltime \n %02d:%02d.%03d\n", minutes, seconds, milliseconds);

        state = 3;
      }
      else if (state == 3)
      {
        tft.fillRect(30, 90, 180, 50, TFT_RED);
        tft.setCursor(50, 100);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK, TFT_BLUE);
        tft.println("Yes");
        state = 0;
      }
    };

  if (state == 1)
    {
       tft.fillScreen(TFT_GREEN);
       digitalWrite(led1pin,HIGH);


        delay(1000);
      digitalWrite(led2pin,HIGH);
        delay(1000);
      digitalWrite(led3pin,HIGH);
        delay(1000);
       digitalWrite(led4pin,HIGH);
        delay(1000);
      digitalWrite(led5pin,HIGH);
        delay(1000);
      allLow();
      starttime = millis();
      state = 2;
      
    };

    if (state == 2)
      {
        nowtime = millis();
        duration = nowtime - starttime;
        tft.fillRect(0, 90, 180, 50, TFT_RED);
        tft.setCursor(20, 100);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK, TFT_RED);
        minutes = duration / 60000;
        seconds = (duration % 60000) / 1000;
        milliseconds = duration % 1000;
        tft.printf("Duration \n %02d:%02d.%03d\n", minutes, seconds, milliseconds);
        delay(50);
      }



  if (digitalRead(button) == HIGH)
    {
      flag = 0;
    };
}
