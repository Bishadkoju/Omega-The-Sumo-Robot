//For front motor 
const int fLin1=2;
const int fLin2=4;
const int fLpwm=3;

const int fRin3=7;
const int fRin4=8;
const int fRpwm=5;


//For back motor 
const int bLin1=1;
const int bLin2=0;
const int bLpwm=6;

const int bRin3=9;
const int bRin4=13;
const int bRpwm=10;

//For Ultrasonic Sensor
const int ftrigPin=A5;  
const int fechoPin=A4;  
const int btrigPin=12;  
const int bechoPin=11;  

// For IR Sensors
const int br=A1;
const int fr=A0;  
const int bl=A3;  
const int fl=A2;    
double Fdistance=0;
double Bdistance=0;
int timer=0; 

void setup() {  
  pinMode(fRin3,OUTPUT);
  pinMode(fRin4,OUTPUT);
  pinMode(fRpwm,OUTPUT);
    
  pinMode(bRin3,OUTPUT);
  pinMode(bRin4,OUTPUT);
  pinMode(bRpwm,OUTPUT);
    
  pinMode(fLin1,OUTPUT);
  pinMode(fLin2,OUTPUT);
  pinMode(fLpwm,OUTPUT);
    
  pinMode(bLin1,OUTPUT);
  pinMode(bLin2,OUTPUT);
  pinMode(bLpwm,OUTPUT);
    
    
  pinMode(ftrigPin, OUTPUT);  
  pinMode(fechoPin, INPUT);  
  pinMode(btrigPin, OUTPUT);  
  pinMode(bechoPin, INPUT);  
  pinMode(fl, INPUT);  
  pinMode(fr, INPUT);  
  pinMode(bl, INPUT);  
  pinMode(br, INPUT);  
   
}  
  
  
void loop() {  
  // put your main ) here, to run repeatedly:  
 if (analogRead(fl)<=530 && analogRead(bl)<=530 && analogRead(fr)<=530 && analogRead(br)<=530){ 
 irCheck();
 uvCheck();
 milliCheck();
}
} 

 void irCheck(){
 if (analogRead(fl)> 530 || analogRead(fr)>530)
 {
backward(100);
delay(1000);
 }

 if (analogRead(bl)>530 || analogRead(br)>530)
 {
  forward(100);
  delay(1000);
 }
}

void uvCheck(){
  double fDist = u1detect();  
  double bDist = u2detect();
  if(fDist<20)  
   {
    brake();
    delay(50);
    irCheck();
    forward(100);  
    delay(300); 
}  
  else if(bDist<20 )  
   {
    brake();
   delay(50);
    irCheck();
    backward(100);  
    delay(300); 
} 
}

double u1detect(){
  double Fduration,Fdistance;
  digitalWrite(ftrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(ftrigPin, HIGH);
  delayMicroseconds(10);
  Fduration = pulseIn(fechoPin, HIGH);
  Fdistance= Fduration*0.034/2;
 return Fdistance;
 }

double u2detect(){
  double Bduration,Bdistance;
 digitalWrite(btrigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(btrigPin, HIGH);
  delayMicroseconds(10);
  Bduration = pulseIn(bechoPin, HIGH);
  Bdistance= Bduration*0.034/2;
 return Bdistance;
 } 


void milliCheck(){
  if (timer==0){
       irCheck();
      uvCheck();
      timer=millis();
    }
    else if(millis()<=(timer+1000)){
      irCheck();
      uvCheck();
      rotate(255);
      
      }
      else if(millis()>(timer+1000) && millis()<=(timer+3000)){
        irCheck();
        uvCheck();
        forward(100);
      }
      else if(millis()>(timer+3000)){
        timer=0;
      }
}
  void rotate(int rate){
 digitalWrite(fRin3,HIGH);
  digitalWrite(fRin4,LOW);
  analogWrite(fRpwm,rate);

  digitalWrite(bRin3,HIGH);
  digitalWrite(bRin4,LOW);
analogWrite(bRpwm,rate);

   digitalWrite(fLin1,LOW);
  digitalWrite(fLin2,HIGH);
analogWrite(fLpwm,rate);

  digitalWrite(bLin1,LOW);
  digitalWrite(bLin2,HIGH);
  analogWrite(bLpwm,rate);
  }

 void forward(int rate){
 digitalWrite(fRin3,HIGH);
  digitalWrite(fRin4,LOW);
  analogWrite(fRpwm,rate);

  digitalWrite(bRin3,HIGH);
  digitalWrite(bRin4,LOW);
analogWrite(bRpwm,rate);

   digitalWrite(fLin1,HIGH);
  digitalWrite(fLin2,LOW);
analogWrite(fLpwm,rate);

  digitalWrite(bLin1,HIGH);
  digitalWrite(bLin2,LOW);
  analogWrite(bLpwm,rate);
  }
  
void backward(int rate){
  digitalWrite(fRin3,LOW);
  digitalWrite(fRin4,HIGH);
analogWrite(fRpwm,rate);

  digitalWrite(bRin3,LOW);
  digitalWrite(bRin4,HIGH);
analogWrite(bRpwm,rate);

   digitalWrite(fLin1,LOW);
  digitalWrite(fLin2,HIGH);
analogWrite(fLpwm,rate);

  digitalWrite(bLin1,LOW);
  digitalWrite(bLin2,HIGH);
  analogWrite(bLpwm,rate);
  }

  void brake(){
  
  digitalWrite(fRin3,LOW);
  digitalWrite(fRin4,LOW);
analogWrite(fRpwm,0);

  digitalWrite(bRin3,LOW);
  digitalWrite(bRin4,LOW);
analogWrite(bRpwm,0);

   digitalWrite(fLin1,LOW);
  digitalWrite(fLin2,LOW);
analogWrite(fLpwm,0);

  digitalWrite(bLin1,LOW);
  digitalWrite(bLin2,LOW);
  analogWrite(bLpwm,0);
} 
  
 
