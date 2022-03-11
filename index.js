const CPUMiner = require('./build/Release/cpuminer.node')

const Caver = require('caver-js')
const caver = new Caver('https://api.baobab.klaytn.net:8651/')

const web3Utils = require('web3-utils')

const minerConfigJSON = require('./miner-config.json')
const tokenContractJSON = require('./contracts/SigmoidToken.json')
var pjson = require('./package.json');

var is_balloon;
var previousBlockHash;
var currentTarget;
var s_cost, t_cost, delta;

console.log('Welcome to Sigmoid CPU Miner...!');
console.log('Version: ', pjson.version + '\n');

const minerAddress = minerConfigJSON.miner_address;
const minerPrivateKey = minerConfigJSON.miner_private_key;
const contractAddress = minerConfigJSON.contract_address;
const maximumGas = minerConfigJSON.maximum_gas;

// Setting: wallet and contract loading
const keyring = caver.wallet.keyring.createFromPrivateKey(minerPrivateKey);
if (keyring._address != minerAddress) revert();
caver.wallet.add(keyring);
const tokenContract = new caver.contract(tokenContractJSON.abi, contractAddress);

console.log('Miner account address: ' + minerAddress);
console.log('Miner private key: ' + minerPrivateKey);
console.log('Contract address: ' + contractAddress + '\n');

console.log('------------------------------------------------------------------------');

async function set_parameters() {
    is_balloon = await tokenContract.methods.isBalloon().call();
    previousBlockHash = await tokenContract.methods.getPreviousBlockHash().call();
    var currentTargetString = await tokenContract.methods.getCurrentTarget().call();
    currentTarget = web3Utils.toBN(currentTargetString).toString(16)

    var params_array = await tokenContract.methods.getHashingParameters().call();
    s_cost = params_array[0];
    t_cost = params_array[1];
    delta = params_array[2];

    if (is_balloon) console.log('Using Balloon hashing... \n');
    else console.log('Using Keccak-256...\n');
    CPUMiner.setWhetherBalloon(is_balloon);

    console.log('Balloon hashing parameter: ');
    console.log('s_cost: ' + s_cost + ', t_cost: ' + t_cost + ', delta: ' + delta + '\n');
    CPUMiner.setParameters(s_cost, t_cost, delta);

    console.log('Current target: 0x' + currentTarget);
    CPUMiner.setDifficultyTarget(currentTarget);
    console.log('Previous Block Hash: ' + previousBlockHash + '\n');
    CPUMiner.setChallengeNumber(previousBlockHash);
    CPUMiner.setMinerAddress(minerAddress);
}

const COLLECT_MINING_PARAMS_TIMEOUT = 120000;

async function mine() {
    CPUMiner.stop();

    // Keep checking hash rate and whether the block hash has changed
    setInterval(() => {
        printHashRate();
        checkBlockHash().then((hash) => {
            if (hash != previousBlockHash) {
                set_parameters();
            };
        });
    }, COLLECT_MINING_PARAMS_TIMEOUT);

    console.log('Starting mining...');
    
    // Run CPU miner
    set_parameters().then(() => {
        CPUMiner.run((err, sol) => {
            if (sol) {
                console.log('Found nonce: ' + sol);
                try {
                    //submit(sol);
                    console.log('Submitted. \n');
                } catch (e) {
                    console.log(e);
                    console.log(err);
                }
                // Repeat mining after 3 sec
                setTimeout(mine, 3000);              
            }
        });
    });   
}

async function checkBlockHash() {return await tokenContract.methods.getPreviousBlockHash().call();}

async function printHashRate() {console.log('Hash rate: ' + parseInt( CPUMiner.hashes() / COLLECT_MINING_PARAMS_TIMEOUT) + " kH/s");}

async function submit(nonce) {
    tokenContract.methods.mint(nonce).send({from: minerAddress, gas: maximumGas})
    .then(function(receipt) {
        console.log('tx hash: ' + receipt.transactionHash);
        console.log('gas: ' + receipt.gas);
        console.log('gasPrice: ' + receipt.gasPrice);
        console.log('gasUsed: ' + receipt.gasUsed + '\n');
        console.log('------------------------------------------------------------------------');
    });
}

mine();