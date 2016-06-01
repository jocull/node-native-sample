// hello.js
const addon = require('./build/Release/addon');

console.log('hello...');
console.log(addon.hello()); // 'world'
