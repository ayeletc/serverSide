/*
 Move this file to the the build dir of the darknet 
 with the relevant node_modules: 
 rtmp-server, http, socket.io, child_process, tree-kill
*/

const S_LOG = "Server: ";
const C_LOG = "CPP: ";
const RtmpServer = require('rtmp-server');
const rtmpServer = new RtmpServer();

var kill = require('tree-kill');

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
     	console.log(S_LOG + 'connect', client.app);
		io.emit('clientConnected', {"data" : "I got a client"});
  });

  client.on('play', ({ streamName }) => {
    console.log(S_LOG + 'PLAY', streamName);
  });

  client.on('publish', ({ streamName }) => {
    console.log(S_LOG + 'PUBLISH', streamName);
	console.log(S_LOG + 'start CV process (C++)');
    var spawn = require('child_process').spawn,
    videoProcessing  = spawn('./darknet', ['./']);
/*	
	if we suspect that there is a problem with the WiFi:
 	we can uncomment the next line (instead of the one above) and compile whatismyip.cpp.
 	if the project works (writing the url in the terminal) the problem is just the Wifi.
*/    
//     videoProcessing  = spawn('./whatismyip', ['./']); 
	
    videoProcessing.stdout.on('data', function(data) {
	    console.log(C_LOG + data.toString());
	    
	    // DARKNET
	    
	    // Green Light Event
	    // The string in the next line  should match darknet's output for greenLight event
	    if(data.toString().includes('green')) { 
	    	console.log(S_LOG + 'Green Light Event');
	    	
		/* in the next line:
			First string is the event's name - should by the same as the name in the app
			Second is the name of the data to TTS (don't change it)
			Last is the message for TTS (this is the only place it is set 
				=> no problem to change it)
    	*/	
	   		io.emit('greenLight', {"data" : 'walk'}); 
	    }
	    
	    // Traffic Light Event Detected
	    // The string in the next line  should match darknet's output for redLight event
	    if(data.toString().includes('red')) { 
	    	console.log(S_LOG + 'Red Light Event');
	    	
		/* in the next line:
			First string is the event's name - should by the same as the name in the app
			Second is the name of the data to TTS (don't change it)
			Last is the message for TTS (this is the only place it is set 
				=> no problem to change it)
    	*/	
	   		io.emit('redLight', {"data" : 'dont walk'}); 
	    }	
	  // DARKNET - END
    
    });  
    videoProcessing.stderr.on('data', function(data) {
    	console.log(C_LOG + 'error:\n' + data);
    });
    
});
  client.on('stop', () => {
    console.log(S_LOG + 'client disconnected');
    console.log(S_LOG + 'kill cpp process');
/* 
	When the next line is uncomment, we kill the process when error occurs.
	It is risky and you need to check if the errors you get are reliable enough.
*/
//     kill(process.pid);   //

  });

});

rtmpServer.listen(1936);
