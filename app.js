var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var serialportmodule = require("serialport");
var SerialPort = serialportmodule.SerialPort;

app.get('/', function(req, res){
  res.sendfile('public/index.html');
});

io.on('connection', function(socket){
  console.log('a user connected');
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});


try {
  var serialPort = new SerialPort("/dev/cu.usbmodem1411", {
    baudrate: 115200,
    parser: serialportmodule.parsers.readline('\n')
  });

  serialPort.on("open", function () {
    console.log('open');

    serialPort.on('data', function(data) {
      console.log('data received: ' + data);
      io.emit('update', data.toString());
    });

  });
} catch(e) {
}
