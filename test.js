// var SegfaultHandler = require('segfault-handler')
// SegfaultHandler.registerHandler("crash.log")

const expect = require('chai').expect
const rnode = require('./build/Debug/RNode')

process.env.DYLD_LIBRARY_PATH = "/Users/nick/Code/Personal/RNode/r_tmp/R-3.4.3/lib"

describe('RNode', () => {
  describe('#call', () => {
    it ('should return an integer', () => {
      expect(rnode.call("return_immediate", 100)).to.equal(100)
    })

    it ('should return a string', () => {
      expect(rnode.call('return_immediate', 'hello world')).to.equal('hello world')
    })
  })
})

// let x = rnode.call("return_immediate", 100)
// console.log('x : ', x)

// x = rnode.call('return_immediate', 'hello world')
// console.log('x : ', x)
