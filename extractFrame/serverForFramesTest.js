const S_LOG = "Server: ";
const C_LOG = "CPP: ";
const RtmpServer = require('rtmp-server');
const rtmpServer = new RtmpServer();

// Http Server for sending data to the device
const http = require('http').createServer();
const io = require('socket.io')(http);

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

   // Run the CPP file
    var spawn = require('child_process').spawn,
    videoProcessing  = spawn('./extractFrame', ['./']);
    // Print LOG from CPP file
    videoProcessing.stdout.on('data', function(data) {
	    console.log(C_LOG + data.toString());     
    });  
    videoProcessing.stderr.on('data', function(data) {
    	console.log(C_LOG + 'error:\n' + data);
    });
    
});
  client.on('stop', () => {
    console.log(S_LOG + 'client disconnected');
    console.log(S_LOG + 'kill cpp process');
	  
/*

	TODO next:
	
	Last frame has been saved (hopefully).
	
	Time to call java to start processing using:
	
	var child = require('child_process').spawn(
  	'MatlabEngineMain', ['-jar', 'enginejar.jar', 'argument to pass in']
	);

	where 'MatlabEngineMain' is the compile .java file (after running "javac MatlabEngineMain.java" in cmd)
	
	ref: https://stackoverflow.com/a/29242794
	
*/
  });

});

rtmpServer.listen(1936);
