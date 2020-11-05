## MQTT Protocol
### ESP32, Mosquitto Broker on Raspberry Pi and MQTT Dashboard on Android

![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/Image.jpeg)

***

### Topics:

:small_blue_diamond: [MQTT Protocol](#mqtt-protocol)

:small_blue_diamond: [Raspberry Pi](#raspberry-pi)

:small_blue_diamond: [Application Topology](#application-topology)

:small_blue_diamond: [Mosquitto Installation](#mosquitto-installation)

:small_blue_diamond: [Mosquitto User Authentication](#mosquitto-user-authentication)

:small_blue_diamond: [Mosquitto Broker Terminal Test](#mosquitto-broker-terminal-test)

:small_blue_diamond: [Android - MQTT Dashboard](#android---mqtt-dashboard)

:small_blue_diamond: [ESP32 Code - Arduino Ide](#esp32-code---arduino-ide)

:small_blue_diamond: [Results](#results)

***

### MQTT Protocol
MQTT is a messaging protocol for TCP/IP networks.
It is simple and light. Its basic architecture consists of broker and clients. The message exchange scheme is based on the Publish-Subscribe model.

Version 3.1.1 documentation:
http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/mqtt-v3.1.1.html

***

### Raspberry Pi
Raspberry Pi is a series of small computers, which basically connects to a monitor, a keyboard and a mouse. There are several models, varying the available resources and performance.
It is developed in the United Kingdom by the Raspberry Pi Foundation.
In this application, Raspberry Pi 4 Model B with Raspbian operating system (based on Debian) was used.

Learn more at:
https://www.raspberrypi.org/help/

***

### Application Topology
![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/topology.jpg)

***

### Mosquitto Installation
Install the Mosquitto Broker that is available in the Debian archive, following what is described:
https://mosquitto.org/blog/2013/01/mosquitto-debian-repository/

After installing the Mosquitto broker, install the Mosquitto Clients:
```
terminal commands
```

Install the Mosquitto Clients:
```
sudo apt install -y mosquitto-clients
```

Verify the status:
```
sudo systemctl status mosquitto.service
```
![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/status.png)

You will see "active running".

***

### Mosquitto User Authentication

Stop the broker:
```
sudo stop mosquitto
```

Create a user configuration file:
```
sudo mosquitto_passwd -c /etc/mosquitto/pwfile username
```
Replace "user" with your username. When confirming, you will be asked for a password. Type a password and confirm.

Open the Mosquitto configuration file:
```
sudo nano /etc/mosquitto/mosquitto.conf
```
Comment (#) the last line "include_dir /etc/mosquitto/conf.d"
And add the following lines:
```
password_file /etc/mosquitto/pwfile
allow_anonymous false
listener 1883
```

![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/config.png)

This will allow only devices with a name and password to access port 1883.
Type Ctrl+X to exit and S to save.

Enable the service:
```
sudo systemctl enable mosquitto.service
```

Reboot the Raspberry Pi:
```
reboot
```

***

### Mosquitto Broker Terminal Test

Open two terminals, one will be used for Subscribe and the other for Publish.

Do the following command on the first terminal:
```
mosquitto_sub -d -u username -P password -t topic/test.
```
This terminal will listen to the message that will come in the expected topic.

Now, do the command in the second terminal:
```
mosquitto_pub -d -u username -P password -t topic/test -m "Hello, Mosquitto!"
```
This terminal will publish the message in the configured topic.

![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/pubsub.png)

If you got here, the broker is working correctly!!!

***

### Android - MQTT Dashboard

Follow the next steps to install and configure MQTT Dashbord on your Android device:

![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/dashboard1.jpg)

1- Search for mqtt dashboard in the Play Store and install. Version of the app used: 0.6.8 of 09/25/2020.

2- Add the broker.

3- Fill in according to the broker configuration. Important fields: Raspberry IP, broker username and password.

4- Now add the dashboard.

5- "Standard".

6- Add the buttons, configure them and then add "Text".

7- Configure the first button. Important fields: Publish topic and Payload (message).

![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/dashboard2.jpg)

8- Configure desired color and icon.

9- Now, to make it easier, duplicate the button.

10- Edit the color and name of the button. Do this for all buttons.

11- The time has come to add "Text". Important fields: Publish and subscribe topics. Set the first to "inTopic".

12- Configure the other one for "outTopic".

13- Ready!

***

### ESP32 Code - Arduino Ide

Used libraries:
~~~c++
#include <WiFi.h>
#include <PubSubClient.h>
~~~

GPIO Pins. Configure according to your wiring:
~~~c++
#define YEL 12
#define RED 13
#define GRE 14
~~~

Fill in the name and password of your local network:
~~~c++
const char* ssid = "your ssid";
const char* password = "your password";
~~~

Fill in the IP address of that format, separated by commas:
~~~c++
IPAddress server(000, 000, 000, 000); 
~~~
To find the address, type in the terminal:
```
ip a
```
The IP will be described in "inet".

Finally, fill with mqtt_user and mqtt_password, as configured in the mosquitto ( [here](#mosquitto-user-authentication) ):
~~~c++
if (client.connect("espClient", "mqtt_user", "mqtt_password"))
~~~

***

### Results
![](https://github.com/MrFMach/Esp32-MQTT-PubSub/blob/main/media/results.jpg)

If you want to track the message traffic via the terminal, just go back to the broker's test topic ( [here](#mosquitto-broker-terminal-test) ), open a terminal for Subscribe and replace the topic name with the application topic, for example "inTopic":
```
mosquitto_sub -d -u username -P password -t inTopic
```

***

Thank you!

#### Fabio Machado
[![Linkedin Badge](https://img.shields.io/badge/-LinkedIn-blue?style=flat-square&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/in/fabio-machado-b932a476/)](https://www.linkedin.com/in/fabio-machado-b932a476/)

:computer:  Computer Engeneering  | :zap: Electronic  | :brazil:  Brazil

##### " cooperating, we'll go far " :rocket:
