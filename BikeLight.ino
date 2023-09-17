
const int leds[] = {5, 6, 9, 10, 11};
const int btn = 2;
const int patternCount = 5;
int crnt_pattern = 0;

int bounceIdx = 0;

# define POT A4



uint32_t blinkTime;


void setup(){
  pinMode(leds[0],OUTPUT);
  pinMode(leds[1],OUTPUT);
  pinMode(leds[2],OUTPUT);
  pinMode(leds[3],OUTPUT);
  pinMode(leds[4],OUTPUT);
  pinMode(btn,INPUT);
  pinMode(POT,INPUT);
  Serial.begin(9600);
  blinkTime = millis();
}


void loop(){
  int pot_delay = analogRead(POT)/16;
  int btnState = digitalRead(btn); // 1 if pressed, 0 if not
  // Keep track of pattern #
  if (btnState == 1){
    Serial.println("Pressed");
    crnt_pattern++;
    delay(150);
    // Reset if crnt_pattern exceeds # of patterns
    if (crnt_pattern > patternCount){
      crnt_pattern = 0;
    }
  }

  uint32_t t;
  t = millis();

  // Pattern #0: OFF
  if (crnt_pattern == 0){
    digitalWrite(leds[0],LOW);
    digitalWrite(leds[1],LOW);
    digitalWrite(leds[2],LOW);
    digitalWrite(leds[3],LOW);
    digitalWrite(leds[4],LOW);
  }

  // Pattern #1: All on
  if (crnt_pattern == 1){
    digitalWrite(leds[0],HIGH);
    digitalWrite(leds[1],HIGH);
    digitalWrite(leds[2],HIGH);
    digitalWrite(leds[3],HIGH);
    digitalWrite(leds[4],HIGH);
  }

  // Pattern #2: All blink together + Potentiometer controlls blink speed
  if (crnt_pattern == 2){
    int interval = analogRead(POT)/4;
    if (t >= blinkTime + interval){
      digitalWrite(leds[0],!digitalRead(leds[0]));
      digitalWrite(leds[1],!digitalRead(leds[1]));
      digitalWrite(leds[2],!digitalRead(leds[2]));
      digitalWrite(leds[3],!digitalRead(leds[3]));
      digitalWrite(leds[4],!digitalRead(leds[4]));     
      blinkTime = t;  
    }
  }

  // Pattern #3: Breathing mode + Potentiometer controlls blink speed
  if (crnt_pattern == 3){
    // Slowly light up
    for(int i = 0; i < 255; i++){
      if (t >= blinkTime + 50 + pot_delay){
        analogWrite(leds[0],  i);
        analogWrite(leds[1],  i);
        analogWrite(leds[2],  i);
        analogWrite(leds[3],  i);
        analogWrite(leds[4],  i);
        blinkTime = t;
      }   
      t = millis();
    } 
    // Slowly dim
    for(int i  = 255; i >= 0; i--){
      if (t >= blinkTime + 50 + pot_delay){
        analogWrite(leds[0],  i);
        analogWrite(leds[1],  i);
        analogWrite(leds[2],  i);
        analogWrite(leds[3],  i);
        analogWrite(leds[4],  i);
        blinkTime = t;
      }
      t = millis();
    }
  }

  // #4 Wave mode + speed determined by potentiometer
  if (crnt_pattern == 4){
    if (t >= blinkTime + 50 + pot_delay){
      digitalWrite(leds[bounceIdx%5], !digitalRead(leds[bounceIdx%5]));
      bounceIdx++;
      blinkTime = t;
    }
  }

  // #5 Random mode + speed determined by potentiometer
  if (crnt_pattern == 5){
    if (t>blinkTime + 50 + pot_delay){
      digitalWrite(leds[rand() % 5],!digitalRead(leds[rand() % 5]));
      blinkTime = t;
    }
  }

}