const RtmpServer = require('rtmp-server');
const rtmpServer = new RtmpServer();

var kill = require('tree-kill');
var spawn = require("child_process").spawn;
var process = spawn('/Users/ayelet/.virtualenvs/cv/bin/python', [] );


// Http Server for sending data to the device
const http = require('http').createServer();
const io = require('socket.io')(http);
// when this event is uncomment, the program stop here (until the client disconnects)
// io.on('connection', function(socket) {
// 	console.log('a user connected');
// 	}); 
http.listen(1937);


// RTMP Server for video streaming
rtmpServer.on('error', err => {
  throw err;
});

rtmpServer.on('client', client => {

  client.on('connect', () => {
     	console.log('connect', client.app);
		io.emit('clientConnected', {"data" : "I got a client"});
  });

  client.on('play', ({ streamName }) => {
    console.log('PLAY', streamName);
  });

  client.on('publish', ({ streamName }) => {
    console.log('PUBLISH', streamName);
    //start python process (processRTMP.py) using python from "cv" virtual env
    console.log('start python process');
    process = spawn('/Users/ayelet/.virtualenvs/cv/bin/python', ["./processRTMP.py"] );
//     console.log('spawn process id = %d\n', process.pid);    
    process.stdout.on('data', function(data) {
	    console.log(data.toString());
	    if(data.toString().includes('10')) {
	    	console.log('match');

    		io.emit('match', {"data" : 'I got a match'});
	    }
	    else {
	    	console.log('no match');
	    }	    
    });  
    process.stderr.on('data', function(data) {
    	console.log('python error:\n' + data);
    });
	 
});
  client.on('stop', () => {
    console.log('client disconnected');
    console.log('kill python process');
//     kill(process.pid);    	
  });
});
rtmpServer.listen(1936);
