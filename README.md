# Sigmoid KIP-7 Token CPU Miner

solves proof of work to mine supported KIP-7 tokens. This is a CPU miner.

### LICENSE

Since a vast part of this project is borrowed from original [0xBitcoin miner](https://github.com/0xbitcoin/0xbitcoin-miner), which follows GPL license, this project also follows GPL license v3.

### Building from Source

#### Setup (Windows/Linux)
1. Install NodeJS 14 (nvm install 14)
2. Clone/download the project
3. Open a terminal, cd into the project folder and run 'npm install' to install dependencies
4. Run the command 'npm run build' to build C files with node-gyp
5. Set up the config file 'miner-config.json' (duplicate miner-config-sample as a reference)
6. Start the miner with 'npm start'

#### Setup (Mac)
1. Install Homebrew & NodeJS 14
2. Run 'brew install yarn' to install yarn package manager
3. Clone/download this project
4. Open a terminal, cd into the project folder and run 'yarn'  
5. Run the command 'yarn build' to build C files with node-gyp
6. Set up the config file 'miner-config.json' (duplicate miner-config-sample as a reference)
7. Start the miner with 'node index.js'


### NOT WORKING ?
Make sure you have build-essential installed to compile C code and make sure you have python3.

Try this command:

  node-gyp rebuild
  

## Miner-Config.js File

You must create a file called 'miner-config.json' in the same directory as index.js. Follow the form below to fill the configuration file. 

    "mining_address": "0x111111",
    "mining_private_key": "1234567",
    "contract_address": "0xb6...",
    "maximum_gas": 80000000
    

If you do not have a public address or a private key, please use Metamask or [official website for Klaytn wallet management](https://wallet.klaytn.com/) to make a new mainnet(cypress) wallet. For testing purposes, please use [the website for wallets on Baobab Testnet](https://baobab.wallet.klaytn.com/).

---------------

### Getting Started
1. Open 'miner-config.json' file
2. Set the parameters in this file appropriately
3. In the console, run the command 'node index.js' to start mining


### Pool Mining
- Pool mining is not supported yet. But it is coming really soon... Stay tuned!


### Solo Mining
- For solo mining. it is necessary to fill the mining account (it is an Ethereum account) with a small amount of ether.  
- A small amount of Klaytn is used for gas to make function calls to the token smart contract when the miner finds a solution to the Proof of Work. Since Klaytn is a POS cryptocurrency, the transaction fee won't be expensive as Ethereum.
- If the gas is spent that means that you have found a solution! If you were the first to find it, you will be rewarded with Sigmoid tokens. (See the block explorer for typical gas prices at the current moment.)


## For more information, visit:
[Sigmoid homepage](https://sigmoid-token.github.io)
