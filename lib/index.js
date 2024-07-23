let addon

function isProcessRunning (...args) {
  if (process.platform !== 'win32') {
    throw new Error('windows-processes works only on Windows')
  }

  addon = addon || require('bindings')('processes')
  return addon.isProcessRunning(...args)
}

module.exports = { isProcessRunning }
