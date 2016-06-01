"use strict"

const addon = require('./build/Release/addon');

for (let x = 0; x < 10; x++) {
    let y = x;
    console.log('hello...');
    addon.hello((err, result) => {
        console.log("Instance " + y + ": " + result);
    });
}
