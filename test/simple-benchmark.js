const isProcessRunning = require('../lib/index').isProcessRunning

// Warmup
isProcessRunning('node.exe')

console.time('Existing process')
isProcessRunning("node.exe")
console.timeEnd('Existing process')

console.time('Non-existing process')
isProcessRunning("node23423423423423423423423.exe")
console.timeEnd('Non-existing process')
