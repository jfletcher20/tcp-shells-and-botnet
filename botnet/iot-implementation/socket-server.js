const net = require('net');
const http = require('http');
const readline = require('readline'); // Import readline module
// Create a TCP server
const server = net.createServer();

// Array to store connected clients
const clients = [];

// Event handler for when a client connects
server.on('connection', (socket) => {
    console.log('A new client connected.');

    // Add the new client to the array
    clients.push(socket);

    // Event handler for when data is received from a client
    socket.on('data', (data) => {
        // Broadcast the received data to all connected clients
        broadcast(data);
    });

    // Event handler for when a client disconnects
    socket.on('end', () => {
        console.log('A client disconnected.');
        // Remove the disconnected client from the array
        clients.splice(clients.indexOf(socket), 1);
    });
});

// Function to broadcast a message to all connected clients
function broadcast(message) {
    clients.forEach((client) => {
        // Write the message to each client
        client.write(message);
    });
}

// Create an HTTP server to receive POST requests
const httpServer = http.createServer((req, res) => {
    if (req.method === 'POST' && req.url === '/command') {
        let body = '';
        req.on('data', (chunk) => {
            body += chunk;
        });
        req.on('end', () => {
            const command = JSON.parse(body).body;
            broadcast(command);
            res.statusCode = 200;
            res.end('Command broadcasted successfully');
        });
    } else {
        res.statusCode = 404;
        res.end('Not found');
    }
});

// Start the TCP server and listen on a specific port
const tcpPort = 3001;
server.listen(tcpPort, () => {
    console.log(`Socket hosted on port ${tcpPort}`);
});

// Start the HTTP server and listen on a specific port
const httpPort = 3002;
httpServer.listen(httpPort, () => {
    console.log(`HTTP server hosted on port ${httpPort}`);
});

// Create readline interface for CLI input
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// Event handler for CLI input
rl.on('line', (input) => {
    const command = input.trim(); // Trim the input
    broadcast(command); // Broadcast the command to all clients
});
