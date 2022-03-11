# Sigmoid KIP-7 Token CPU Miner

solves proof of work to mine supported KIP-7 tokens. This is a CPU miner.

### LICENSE

Since a vast part of this project is borrowed from original [0xBitcoin miner](https://github.com/0xbitcoin/0xbitcoin-miner), which follows GPL license, this project also follows GPL license v3.

### Building from Source

#### Setup (Windows/Linux)
1. Install NodeJS 14 (nvm install 14)
2. Clone/download the project
3. Open a terminal, cd into the project folder and run 'npm install' to install dependencies
  npm install
4. Run the command 'npm run build' to build C files with node-gyp
  npm run build
5. Set up the config file 'miner-config.json' (duplicate miner-config-sample as a reference)
6. Start the miner with 'npm start'
  npm starat

#### Setup (Mac)
1. Install Homebrew & NodeJS 14
2. Run 'brew install yarn' to install yarn package manager
  brew install yarn
3. Clone/download this project
4. Open a terminal, cd into the project folder and run 'yarn'
  yarn
5. Run the command 'yarn build' to build C files with node-gyp
  yarn build
6. Set up the config file 'miner-config.json' (duplicate miner-config-sample as a reference)
7. Start the miner with 'node index.js'
  node index.js

### NOT WORKING ?
Make sure you have build-essential installed to compile C code and make sure you have python3.

Try these commands:
  node-gyp rebuild



## Miner-Config.js File

You must create a file called 'miner-config.json' in the same directory as index.js.  Duplicate 'miner-config-sample.json' and rename it.  

If you do not have a public address or private key, use Metamask or another Etherum wallet to make them.

REMINDER: You >can< set the web3provider to a ropsten, mainnet, or other type of test-network provider and the software will still work. If solo mining (not to a pool) just be sure to define the correct contract address for that network and be sure your account has a small amount of ether (or test-ether).

    "mining_account_public_address":"0x111111",
    "mining_account_private_key":"1234567",
    "mining_style":"solo" OR "pool",
    "contract_address":"0xb6...",
    "pool_url":"http://tokenminingpool.com:8080",
    "gas_price_gwei":10,
    "cpu_thread_count": 1,
    "web3provider": "https://infura.io/API/apikey...."

---------------

### Getting Started
1. Duplicate the 'miner-config-sample.json' file and rename it to 'miner-config.json'
2. Set the parameters in this file appropriately
3. In the console, run the command 'node index.js' to start mining


### Pool Mining
- Pool mining is not supported yet. But it is coming really soon... Stay tuned!


### Solo Mining
- IF SOLO MINING it is necessary to fill the mining account (it is an Ethereum account) with a small amount of ether.  
- Typically 0.005 eth is good enough to get started.  The ether is used for gas to make function calls to the token smart contract when your miner finds a solution to the Proof of Work.  
- When the gas is spent that means that you have found a solution! If you were the first to find it, you will be rewarded with Sigmoid tokens.  (See the block explorer for typical gas prices at the current moment.)



### Testing

npm run test


## Credits

1. Zegordo (Developed the accelerated CPU Miner)

        ETH address [0x8AE981d92875C88f713600EB7dC4D23FA7E0E621]



## Tokens that can be mined using Proof of Work:

1. Sigmoid token - http://Sigmoid.org - https://github.com/Sigmoid/Sigmoid-token
