"use strict"

const addon = require('./build/Release/addon');

// The blocking way
for (let x = 0; x < 10; x++) {
    let y = x;
    let a = ~~(Math.random() * 14620 + 1);
    console.log('Hello #' + y);
    for (let z = 0; z < 400000000; z++) {
        a++;
    }
    console.log("Instance " + y + ": " + "world! Enjoy your number: " + ~~(a % 14620));
}
console.log('Done with the loop!');


// The non-blocking way
for (let x = 0; x < 10; x++) {
    let y = x;
    console.log('Hello #' + y);
    addon.hello((err, result) => {
        console.log("Instance " + y + ": " + result);
    });
}
console.log('Done with the loop!');
