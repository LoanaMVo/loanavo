/* TEJ3M Summative-IntelliPlant
 * 2017-05-29
 * Loana.V & Tasnim.R
 */ 
//RGB LEDs
//water led
const int redPinOne = 12;   
const int bluePinOne = 11;
const int greenPinOne = 10;
//temperature led
const int redPinTwo = 9;   
const int bluePinTwo = 8;
const int greenPinTwo = 7;
//light led
const int redPinThree = 6;   
const int bluePinThree = 5;
const int greenPinThree = 4;
//photoresistor 
const int photoPin = A1;
//TMP36
const int tempPin = A0;
//buzzer
const int buzzer = 3;
//moisture 
const int moistPin = A2;

boolean buzzOne = false;
boolean buzzTwo = false;
boolean buzzThree = false;

void setup() {
  Serial.begin(9600);
  //LED pin
  pinMode(redPinOne, OUTPUT);
  pinMode(bluePinOne, OUTPUT);
  pinMode(greenPinOne, OUTPUT);
  pinMode(redPinTwo, OUTPUT);
  pinMode(bluePinTwo, OUTPUT);
  pinMode(greenPinTwo, OUTPUT);
  pinMode(redPinThree, OUTPUT);
  pinMode(bluePinThree, OUTPUT);
  pinMode(greenPinThree, OUTPUT); 
  //buzzer
  pinMode(buzzer, OUTPUT);
}

int allGoodOne(){
  analogWrite(redPinOne, 255);//green
  analogWrite(bluePinOne, 255);
  analogWrite(greenPinOne, 0);
}

int allGoodTwo(){
  analogWrite(redPinTwo, 255);//green
  analogWrite(bluePinTwo, 255);
  analogWrite(greenPinTwo, 0);
}

int allGoodThree(){
  analogWrite(redPinThree, 255);//green
  analogWrite(bluePinThree, 255);
  analogWrite(greenPinThree, 0);
}

int tooCold(){
  analogWrite(redPinOne, 0);//orange 
  analogWrite(bluePinOne, 255);
  analogWrite(greenPinOne, 150);
  delay(500);
  analogWrite(redPinOne, 255);//blue
  analogWrite(bluePinOne, 0);
  analogWrite(greenPinOne, 255);
  delay(500);  
}

int tooWarm(){
  analogWrite(redPinOne, 0);//orange
  analogWrite(bluePinOne, 255);
  analogWrite(greenPinOne, 150);
  delay(500);
  analogWrite(redPinOne, 0);//red
  analogWrite(bluePinOne, 255);
  analogWrite(greenPinOne, 255);
  delay(500);    
}

int tooDark(){
  analogWrite(redPinTwo, 0);//yellow
  analogWrite(bluePinTwo, 255);
  analogWrite(greenPinTwo, 0);
  delay(500);
  analogWrite(redPinTwo, 255);//green
  analogWrite(bluePinTwo, 255);
  analogWrite(greenPinTwo, 0);
  delay(500); 
}

int tooBright(){
  analogWrite(redPinTwo, 0);//yellow
  analogWrite(bluePinTwo, 255);
  analogWrite(greenPinTwo, 0);
  delay(500);
  analogWrite(redPinTwo, 0);//red
  analogWrite(bluePinTwo, 255);
  analogWrite(greenPinTwo, 255);
  delay(500);   
}

int moreWater(){
  analogWrite(redPinThree, 255);//blue
  analogWrite(bluePinThree, 0);
  analogWrite(greenPinThree, 255);
  delay(500);
  analogWrite(redPinThree, 255);//green
  analogWrite(bluePinThree, 255);
  analogWrite(greenPinThree, 0);
  delay(500);
  }

int lessWater(){
  analogWrite(redPinThree, 255);//blue
  analogWrite(bluePinThree, 0);
  analogWrite(greenPinThree, 255);
  delay(500);
  analogWrite(redPinThree, 0);//red
  analogWrite(bluePinThree, 255);
  analogWrite(greenPinThree, 255);
  delay(500);
}

void loop() {
  //current light
  int currLight = analogRead(photoPin); 
  Serial.print("light: ");
  Serial.println(currLight);
  
  //current temperature
  int tempReading = analogRead(tempPin);
  //converting
  float voltage = tempReading*5.0;
  voltage/=1023.0;
  //convert to C
  float currTemp = (voltage - 0.5)*100;
  Serial.print("temp: ");
  Serial.println(currTemp);
  
  //moisture
  int moisture = analogRead(moistPin);
  Serial.print("moisture: ");
  Serial.println(moisture);
  
  //temperature
if (currTemp >= 26){//temp is 23 
  tooWarm();
  buzzOne = true;
  Serial.println("too warm");  
}else if (currTemp <= 20){
  tooCold();
  buzzOne = true;
  Serial.println("too cold");
  //too hot
 }else{
  allGoodOne();
  buzzOne = false;
  Serial.println("temperature all good");           
  }

//sunlight level
if (currLight < 800){//800-870 is normal ambient light of room
  tooDark();    
  buzzTwo = true;
  Serial.println("too dark");
}else if(currLight > 870){
  tooBright();
  buzzTwo = true;
  Serial.println("too bright");
}else{
  allGoodTwo();
  buzzTwo = false;
  Serial.println("sunlight all good");
}

//moisture level
if (moisture > 400 ){//at 300-400 is good
  lessWater();
  buzzThree = true;
  Serial.println("less water");
} else if (moisture < 300){
  moreWater();
  buzzThree = true;
  Serial.println("more water");
}else{
  allGoodThree();
  buzzThree = false;
  Serial.println("moisture all good");
}

if (buzzOne == true || buzzTwo == true ||buzzThree == true ){ 
  tone(buzzer,200);
  delay(500);
  tone(buzzer,500);
  delay(500);
  tone (buzzer,800);
  delay(500);
}else{
  noTone(buzzer);
}
}



