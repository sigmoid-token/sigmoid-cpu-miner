var miner

if (process.env.DEBUG) {
  miner= require('./build/Debug/cpuminer')
} else {
  miner= require('./build/Release/cpuminer')
}

module.exports = miner