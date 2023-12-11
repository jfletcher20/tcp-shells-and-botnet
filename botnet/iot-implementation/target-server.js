const express = require('express');
const cors = require('cors');

const app = express();
app.use(cors());

let visitorCount = 0;

app.get('/', (req, res) => {
    visitorCount++;
    res.send(`
        <html>
            <head>
                <title>Target site</title>
                <link rel="icon" href="hacker-icon.png" type="image/png">
                <style>
                    body {
                        background-color: black;
                        color: green;
                        font-family: monospace;
                        font-size: 24px;
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        height: 100vh;
                    }
                </style>
            </head>
            <body>
                <h1>Attacks made: ${visitorCount}</h1>
            </body>
        </html>
    `);
});

app.listen(3000, () => {
    console.log('Server is running on port 3000');
});
