var udp = require('dgram');

var server = udp.createSocket('udp4');

server.on('error',function(error){
    console.log('Error: ' + error);
    server.close();
});

server.on('message',function(msg, info){
    // console.log('Data received from client : ' + msg.toString());
    // console.log('Received %d bytes from %s:%d\n', msg.length, info.address, info.port);

    console.log(info.address);
});

server.on('listening',function(){
    console.log("Scan device...");

    server.send("IP", 887, '192.168.1.255', function(error){
        if(error){
            client.close();
        }
    });
});

server.on('close',function(){
    console.log('Done.');
});

server.bind(2222);

setTimeout(function(){
    server.close();
}, 1000);