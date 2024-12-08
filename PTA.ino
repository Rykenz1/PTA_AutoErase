//button pin
const int btnPin=A0;

//left sensor
const int trigL=4;
const int echoL=5;

//right sensor
const int trigR=6;
const int echoR=7;

//motor direction
const int mtrFWD=8;
const int mtrRVS=9;

//pwm pin
const int EnAPin=10;
const int EnBPin=11;

//led pin
const int LedL=A1;
const int LedR=A2;

bool start=false;
bool reverse;

long durationL,durationR;
int distanceL,distanceR,speed=150,StopDelay=1000;
int Seconds=1;

void setup() {
  // put your setup code here, to run once:
  
  //OUTPUT PIN
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(trigL, OUTPUT);
  pinMode(trigR, OUTPUT);
  pinMode(mtrFWD, OUTPUT);
  pinMode(mtrRVS, OUTPUT);
  pinMode(EnAPin, OUTPUT);
  pinMode(EnBPin, OUTPUT);
  pinMode(LedL, OUTPUT);
  pinMode(LedR, OUTPUT);
  
  //INPUT PIN
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(echoL, INPUT);
  pinMode(echoR, INPUT);
  
  //Serial begin
  Serial.begin(9600);

  reverse=false;
  Seconds=Seconds * StopDelay;
}

void loop() {

  analogWrite(EnAPin, speed);
  analogWrite(EnBPin, speed);

  int btn=digitalRead(btnPin);
  
  //button press start the process
  if(btn==LOW){
    digitalWrite(LED_BUILTIN, HIGH);
    start=true;
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  if(start==true){
    if(reverse==false){
      MoveLeft();
      DistanceMeasureL();
      digitalWrite(LedL, HIGH);
      digitalWrite(LedR, LOW);
      
      if(distanceL<=5){
        reverse=true;
        Stop();
        delay(Seconds);
      }

    }else{
      MoveRight();
      DistanceMeasureR();
      digitalWrite(LedL, LOW);
      digitalWrite(LedR, HIGH);


      if(distanceR<=5){
        Stop();
        start=false;
        reverse=false;
      }
    }
  }
  
  
  Serial.print(start);
  Serial.println(reverse);
}

void DistanceMeasureL() {
  digitalWrite(trigL, LOW);
  delayMicroseconds(2);

  digitalWrite(trigL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL, LOW);
  
  durationL= pulseIn(echoL, HIGH);
  distanceL= durationL/29/2;

  // Serial.println("Distance: " + String(distanceL)+"cm");
  delay(50);
}

void DistanceMeasureR() {
  digitalWrite(trigR, LOW);
  delayMicroseconds(2);

  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR, LOW);
  
  durationR= pulseIn(echoR, HIGH);
  distanceR= durationR/29/2;

  // Serial.println("Distance: " + String(distanceR)+"cm");
  delay(50);
}

void MoveLeft(){
  digitalWrite(mtrFWD, HIGH);
  digitalWrite(mtrRVS, LOW);
}


void MoveRight(){
  digitalWrite(mtrFWD, LOW);
  digitalWrite(mtrRVS, HIGH);
}


//stop everything
void Stop(){
  digitalWrite(mtrFWD, LOW);
  digitalWrite(mtrRVS, LOW);
  digitalWrite(LedL, LOW);
  digitalWrite(LedR, LOW);
  
}
