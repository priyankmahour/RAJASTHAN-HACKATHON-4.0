#include <Ethernet.h> //Load Ethernet Library
#include <EthernetUdp.h> //Load the Udp Library
#include <SPI.h> //Load SPI Library

#include <DHT.h>

// if you require to change the pin number, Edit the pin with your arduino pin.

#define DHTPIN 7 // Defines pin number to which the sensor is connected
#define DHTTYPE DHT11 
# define soil A2

DHT dht(DHTPIN, DHTTYPE);

#define trigPin 9
#define echoPin 8

#define relay 2

long duration, distance;
float hum;  //Stores humidity value 
float temp; //Stores temperature value

int smoke = A1;



byte mac[] ={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE}; //Assign mac address
IPAddress ip(192, 168, 0, 104); //Assign the IP Adress
unsigned int localPort = 5000; // Assign a port to talk over
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //dimensian a char array to hold our data packet
String datReq; //String for our data
int packetSize; //Size of the packet
EthernetUDP Udp; // Create a UDP Object

void setup()
{
  
  Serial.begin(9600); //Initialize Serial Port 
  pinMode(trigPin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(smoke, INPUT);
  dht.begin();
  
  Ethernet.begin( mac, ip); //Inialize the Ethernet
  Udp.begin(localPort); //Initialize Udp
  delay(1500); //delay
  

}

void loop()
{
    
  packetSize =Udp.parsePacket(); //Reads the packet size
  
  if(packetSize>0)
  { //if packetSize is >0, that means someone has sent a request
    
      Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); //Read the data request
      String datReq(packetBuffer); //Convert char array packetBuffer into a string called datReq
    
      if (datReq =="Distance")
      { //Do the following if Distance is requested

        
        digitalWrite(trigPin, LOW);  // Added this line
        delayMicroseconds(2); // Added this line
        digitalWrite(trigPin, HIGH);
  
        delayMicroseconds(10); // Added this line
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distance = (duration/2) / 29.1;

                                       
      
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); //Initialize packet send
      Udp.print(distance); //Send the temperature data
      Udp.endPacket(); //End the packet
      
     }
    
    
     if (datReq =="Temperature")
      { //Do the following if Distance is requested
        
        temp= dht.readTemperature(); // Gets the values of the temperature
                                    
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); //Initialize packet send
      Udp.print(temp); //Send the temperature data
      Udp.endPacket(); //End the packet
      
     }

    if (datReq =="Humidity")
      { //Do the following if Distance is requested

        hum = dht.readHumidity();
        
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); //Initialize packet send
      Udp.print(hum); //Send the temperature data
      Udp.endPacket(); //End the packet
      
     }

     if (datReq =="AQI")
      { //Do the following if Distance is requested

        int analogSensor = analogRead(smoke);        
        
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); //Initialize packet send
      Udp.print(analogSensor); //Send the temperature data
      Udp.endPacket(); //End the packet
      
     }      

     if (datReq =="Soil")
      { //Do the following if Distance is requested

        int sensorValue = analogRead(A2);

        if(sensorValue <20)
        {
          digitalWrite(relay, HIGH);
          
        }
        else
        {
          digitalWrite(relay, LOW);
        }
        
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); //Initialize packet send
      Udp.print(sensorValue); //Send the temperature data
      Udp.endPacket(); //End the packet
      
     }      
     
  }
  memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE); //clear out the packetBuffer array
}
