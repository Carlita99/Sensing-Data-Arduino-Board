const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);


var mysql = require('mysql');
var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'root1234',
    database: 'pollution_detection'
});
connection.connect(function(err) {
    if (err) {
        console.error('Impossible de se connecter ', err);
    }
});

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});


io.on('connection', (socket) => {


    list = []
    socket.on('init', function(messages) {
        connection.query(
            'SELECT *  FROM ValuesReceived ORDER BY timestampp',
            function(err, rows) {
                if (err) {
                    socket.emit('error', err.code);
                } else {
                    rows.reverse(); // On veut les plus vieux en premier
                    for (k in rows) {
                        // console.log(list);
                        var row = rows[k];
                        var inside = 0;
                        for(index in list){
                            if(list[index].id == row.id)
                                inside = 1;
                        }
                        if (inside == 0) {
                            // console.log(row);
                            socket.emit('initresponse', {
                                x: Date.parse(row.timestampp),
                                y: row.valuee,
                                f: row.flagID
                            })
                            list.push(row);
                        }

                    }
                }
            })
    });

    socket.on('initresponse', (msg) => {
        io.emit('initresponse', msg);
    });
});


server.listen(3000, () => {
    console.log('listening on *:3000');
});