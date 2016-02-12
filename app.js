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
  console.log('open http://localhost:3000');
});


try {
  var serialPort = new SerialPort("/dev/cu.usbmodem1411", {
    baudrate: 115200,
    parser: serialportmodule.parsers.readline('\n')
  }, false);

  serialPort.open(function(x) {
    
  });

  serialPort.on("open", function () {
    console.log('open');

    serialPort.on('data', function(data) {
      console.log('data received: ' + data);
      try {
        var d = JSON.parse(data.toString());
        io.emit('update', data.toString());
      } catch(e) {
      }
    });

  });

} catch(e) {
}
