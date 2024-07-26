const int LED = 9;
const int dit = 21;
const int dah = 24;
const int key = 4;
const int reset = 3;
const int speed = 20;
const int threshold = 512;

int DPM = 25*50;
float element = 3.0;
float ditLang, dahLang;
int ditStat = 0;
int dahStat = 0;
i

void setup(){
  pinMode(dit, INPUT);
  pinMode(dah, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  ditLang = (1/DPM)*60*1000;
  dahLang = ditLang*element;
}
//need Functions
void keyUp(){
  digitalWrite(key, HIGH);
  digitalWrite(LED, LOW);
}
void keyDown(){
  digitalWrite(key, LOW);
  digitalWrite(LED, HIGH);
}
void doDit(){
  keyDown();
  delay(ditLang);
  keyUp();
  delay(ditLang);
  ditStat = 0;
}

void doDah(){
  keyDown();
  delay(dahLang);
  keyUp();
  delay(dahLang);
  dahStat = 0;
}

void loop(){
  ditStat = analogRead(dit);
  dahStat = analogRead(dah);
  if (ditStat >= 100){
    doDit();
  }
  else if (dahStat >= 100){
    doDah();
  }
  else if (digitalRead(reset) == HIGH){
    int read = analogRead(speed);
    DPM = DPM + ((read-threshold)*0.01);
    ditLang = (1/DPM)*60*1000;
    dahLang = ditLang*element;
  }

}
