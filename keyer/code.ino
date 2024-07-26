const int LED = 19;
const int dit = 2;
const int dah = 3;
const int key = 4;
var int DPM = 25*50;
float element = 3.0;
float ditLang, dahLang;
int ditStat = 0;
int dahStat = 0;

void setup(){
  pinMode(dit, ANALOG_IN);
  pinMode(dah, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digtialWrite(LED, LOW);
  dotLang = (1/DPM)*60*1000;
  dahLang = dotLang*element;
}
//need Functions
void keyUp(){
  digitalWrite(key, LOW);
}
void keyDown(){
  digitalWrite(key, HIGH);
}
void doDit(){
  
}

void loop(){
  ditStat = analogRead(dit);
  dahStat = analogRead(dah);
  if (ditStat >= 100){
    doDit();
  }
  if (dahStat >= 100){
    doDah();
  }

}
