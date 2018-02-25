
//2018_Hack_HSV

  const int LEDR = 7; //Red-high priotiry
  const int LEDY = 6 ; //Yeelow-medium priority
  const int LEDG = 5; //Green-low priority
  const int LEDB = 4; //Blue no priority
  int latch=9;  //74HC595  pin 9 STCP
  int clock=10; //74HC595  pin 10 SHCP
  int data=8;   //74HC595  pin 8 DS
  const int Button = 11;
  const int digit1 = 3;
  const int digit10 = 2;
  int time_wait = 10;

unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};


//size of the time file
const int timefSize =50;
//size of the priority file
const int priorityfSize =50;
//creating the array for the time file
//add in a variable a array size possible fault
int timeArray[timefSize];
//creating the file for the priority level
int priorityArray[priorityfSize];
int dummyArray[timefSize+priorityfSize];

double currentMinute()
{
  long milliSec = millis();
  double seconds = milliSec/1000;
  double minutes = seconds/60;
  return minutes;
}
void timer(int minutes)
{ 
  double minutesNow = 0;
 //adding current time and array time together
 double timeEnd = currentMinute() + minutes;
  minutesNow= timeEnd - currentMinute();
 do
 {
  LCD_display((int)ceil(minutesNow));
  minutesNow= timeEnd - currentMinute();
 }
 //possibly needs semi colon
 while(minutesNow>0);
}
char val; // Data received from the serial port
int ledPin = 13; // Set the pin to digital I/O 13
boolean ledState = LOW; //to toggle our LED
void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}
void setup() 
{
    pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
  //initialize serial communications at a 9600 baud rate
  Serial.begin(9600);
  establishContact();  // send a byte to establish contact until receiver responds 
  pinMode(LEDR, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
  pinMode(digit1,OUTPUT);
  pinMode(digit10,OUTPUT);
  pinMode(Button, INPUT);
  Serial.println("Hello, world!"); //send back a hello world
  int i=0;
  while(val!=-1)
  {
      if (Serial.available() > 0) { // If data is available to read,
    val = Serial.read(); // read it and store it in val
    if((i==0)&&(val== 'A'))
    {
      
    }
    else
    {
    dummyArray[i]=val;
    i++;
    }
    //Serial.println(val);
    /*if(val == '1') //if we get a 1
    {
       ledState = !ledState; //flip the ledState
       digitalWrite(ledPin, ledState); 
    }*/
    delay(100);
  } 
  }
  // put your main code here, to run repeatedly:
  

  //parse
  i=0;
  while(dummyArray[i*2]!=-1)
  {
    timeArray[i]=dummyArray[i*2];
    Serial.println((int)dummyArray[i*2]);
    priorityArray[i]=dummyArray[i*2+1];
    Serial.println((int)dummyArray[i*2+1]);
    i++;
  }
  timeArray[i]=-1;
  priorityArray[i]=-1;
}

void loop() {
  //variable holding the next value in the time array
  int timeAlotted;
  //variable holding the next value in the priority array
  int priorty;
  int i =0;
  while(timeArray[i]!=-1)
  {
    LED_display(priorityArray[i]);
    //calculating the end time
    timer(timeArray[i]);
    i++;
    while(digitalRead(Button)!= HIGH)
    {
      delay(10);
    }
  }
  LED_display(4);
  while(1)
  {
    delay(10);
  }
}


/*void loop() {
  LED_display(11);
  LCD_display(11);
  while(Button != HIGH) {
  delay(10);
  }
  
}*/

void LED_display(int priority) {
  // put your main code here, to run repeatedly:
  //Serial.read(NEED .txt file);
  if (priority == 1) {
  digitalWrite(LEDR, HIGH); //turns red on
  digitalWrite(LEDY, LOW); //turns yellow off
  digitalWrite(LEDG, LOW); //turns green off
  digitalWrite(LEDB, LOW); //turns blue off
  
  }
  
  else if(priority == 2) {
  digitalWrite(LEDR, LOW); //turns Red off
  digitalWrite(LEDY, HIGH); //turns yellow on
  digitalWrite(LEDG, LOW); //turns green off
  digitalWrite(LEDB, LOW); //turns blue off
  
  }

  else if(priority == 3) {
  digitalWrite(LEDR, LOW); //turns red off
  digitalWrite(LEDY, LOW); //turns yellow off
  digitalWrite(LEDG, HIGH); //turns green on
  digitalWrite(LEDB, LOW); //turns blue off

  }
  
  else {
  digitalWrite(LEDR, LOW); //turns red off
  digitalWrite(LEDY, LOW); //turns yellow off
  digitalWrite(LEDG, LOW); //turns green off
  digitalWrite(LEDB, HIGH); //turns blue on
   
  }

} 
void Display(unsigned char num)
{

  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,table[num]);
  digitalWrite(latch,HIGH);
  
}

void LCD_display(int number)
{
  int i = number % 10;
  int j = (number - i)/10;

  // Ones digit
  digitalWrite(digit1,LOW);
  digitalWrite(digit10,HIGH);
  Display(i);
  delay(time_wait);

  // Tens digit
  digitalWrite(digit1,HIGH);
  digitalWrite(digit10,LOW);
  Display(j);
  delay(time_wait);
}
