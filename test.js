// var SegfaultHandler = require('segfault-handler')
// SegfaultHandler.registerHandler("crash.log")

const rnode = require('./build/Debug/RNode')
let x = rnode.call("return_immediate", 100)
console.log('x : ', x)
