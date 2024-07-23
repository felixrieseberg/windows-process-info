const assert = require('assert')
const isProcessRunning = require('../lib/index').isProcessRunning

assert.strictEqual(isProcessRunning("node.exe"), true)
assert.strictEqual(isProcessRunning("adrgadjfgbkjhdbgjnkdkjgdgdfgdfgd.exe"), false)
