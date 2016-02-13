# AQ

Our contribution to the [Smart Cities Green Hackathon in Stockholm](http://smartcities.greenhackathon.com/) Sweco City Sensors category.



## The visualization

In the [app/](app/) folder you find the node.js proxy, run `npm install` then `node app.js` to start it, then go to `http://localhost:3000` to see the sensor data in real time.

<img src="https://raw.githubusercontent.com/possan/smartcitiesgreenhackathon/master/doc/screenshot.png" width="400" alt="Screenshot" />



## The Arduino firmware

In the [firmware/](firmware/) folder you find the Arduino firmware for this project, it uses three cheap sensors, one for air quality (MQ135), one for temperature and humidity (DHT11) and one for sound.

<img src="https://raw.githubusercontent.com/possan/smartcitiesgreenhackathon/master/doc/mq135.jpg" width="250" alt="MQ135" /> <img src="https://raw.githubusercontent.com/possan/smartcitiesgreenhackathon/master/doc/dht11.jpg" width="250" alt="DHT11" />

Right now the arduino needs to run tethered to a computer that will render the values, the goal of course would be to connect a cheap gps and modem so that this could be made wireless and put up all over the city.
