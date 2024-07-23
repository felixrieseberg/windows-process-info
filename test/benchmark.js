const perfy = require('perfy')
const fs = require('fs')
const isProcessRunning = require('../lib/index').isProcessRunning

const iterations = process.argv[2] || 100

// Surpress windows-registry's dumb logs
const log = console.log
console.log = function () {}

function getIsProcessRunning () {
  return isProcessRunning("Un_A.exe")
}

function measureThisTime () {
  perfy.start('this')
  for (let i = 0; i < iterations; i++) {
    getIsProcessRunning()
  }

  return perfy.end('this').time
}

function measureFsTime() {
  perfy.start('fs')
  for (let i = 0; i < iterations; i++) {
    fs.existsSync('./Un_A.exe')
  }

  return perfy.end('fs').time
}

// Fight!
log(`Reading "isProcessRunning('Un_A.exe')" ${iterations} times:`)

const thisTime = measureThisTime()
const fsTime = measureFsTime()

log(`With this addon:                 ${thisTime}`)
log(`With fs.existSync:               ${fsTime}`)
