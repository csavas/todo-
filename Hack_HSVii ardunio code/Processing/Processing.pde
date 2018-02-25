 import processing.serial.*;
 Serial myPort;
 String val;
// since we're doing serial handshaking, 
// we need to check if we've heard from the microcontroller
boolean firstContact = false;
 void setup() 
 {
   myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
  //parseFile();
 }

void parseFile() {
  // Open the file from the createWriter() example
  BufferedReader reader = createReader("NEED.txt");
  int wait = 100;
  String line = null;
  try {
    while ((line = reader.readLine()) != null) {
      String[] pieces = split(line, TAB);
      int x = int(pieces[1]);
      int y = int(pieces[2]);
      myPort.write(x);
      delay(wait);
      myPort.write(y);
      delay(wait);
    }
      myPort.write(-1);
      delay(wait);
      myPort.write(-1);
      delay(wait);
    reader.close();
    while(myPort.available()>0)
    {
      println(myPort.read());
    }
    }
  catch (IOException e) {
    e.printStackTrace();
  }
}
void draw() {
  //we can leave the draw method empty, 
  //because all our programming happens in the serialEvent (see below)
}
void serialEvent( Serial myPort) {
//put the incoming data into a String - 
//the '\n' is our end delimiter indicating the end of a complete packet
val = myPort.readStringUntil('\n');
//make sure our data isn't empty before continuing
if (val != null) {
  //trim whitespace and formatting characters (like carriage return)
  val = trim(val);
  //println(val);

  //look for our 'A' string to start the handshake
  //if it's there, clear the buffer, and send a request for data
  if (firstContact == false) {
    if (val.equals("A")) {
      myPort.clear();
      firstContact = true;
      myPort.write("A");
      println("contact");
    }
  }
  else { //if we've already established contact, keep getting and parsing data
    println(val);
  parseFile();
    // when you've parsed the data you have, ask for more:
    //myPort.write("A");
    }
  }
}