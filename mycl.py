from socket import *
import time

address= ( '192.168.0.104', 5000) #define server IP and port
client_socket =socket(AF_INET, SOCK_DGRAM) #Set up the Socket
client_socket.settimeout(1) #Only wait 1 second for a response


while(1):

    data =("Distance") #Set data request to Distance
    client_socket.sendto(data, address) #Send the data request

    try:

        rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
        dis= float(rec_data) #Convert string rec_data to float temp
        print "The Measured Distance is ", dis, " cm " # Print the result
        f=open("distance.txt","a+")
        f.write("%d ,\r\n" %(dis))


    except:
        pass

    time.sleep(2) #delay before sending next command

    f.close()
    print ""


    data =("Temperature") #Set data request to Distance
    client_socket.sendto(data, address) #Send the data request

    try:

        rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
        temp= float(rec_data) #Convert string rec_data to float temp
        print "The Measured Temperature is ", temp, " C " # Print the result
        f=open("temperature.txt","a+")
        f.write("%d ,\r\n" %(temp))

    except:
        pass

    time.sleep(2) #delay before sending next command

    f.close()
    print ""

    data =("Humidity") #Set data request to Distance
    client_socket.sendto(data, address) #Send the data request

    try:

        rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
        hum= float(rec_data) #Convert string rec_data to float temp
        print "The Measured Humidity is ", hum, " % " # Print the result
        f=open("humidity.txt","a+")
        f.write("%d, \r\n" %(hum))

    except:
        pass

    time.sleep(2) #delay before sending next command

    f.close()
    print ""

    data =("AQI")#Set data request to Distance
    client_socket.sendto(data, address) #Send the data request

    try:

        rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
        aqi= float(rec_data) #Convert string rec_data to float temp
        print "The Measured AQI is ", aqi, " % " # Print the result
        f=open("air.txt","a+")
        f.write("%d, \r\n" %(aqi))

    except:
        pass

    time.sleep(2) #delay before sending next command

    f.close()
    print ""


    data =("Soil")#Set data request to Distance
    client_socket.sendto(data, address) #Send the data request

    try:

        rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
        soil= float(rec_data) #Convert string rec_data to float temp
        print "The Moisture in soil is ", soil, " % " # Print the result
        f=open("soil.txt","a+")
        f.write("%d, \r\n" %(soil))

    except:
        pass

    time.sleep(2) #delay before sending next command

    f.close()
    print ""


    
