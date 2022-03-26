const CPUMiner = require('./build/Release/cpuminer.node')

const Caver = require('caver-js')
const caver = new Caver('https://api.baobab.klaytn.net:8651/')

var jayson = require('jayson');

// Load configuration files
const minerConfigJSON = require('./miner-config.json')
const tokenContractJSON = require('./contracts/SigmoidToken.json')
var pjson = require('./package.json');

var is_balloon;
var previousBlockHash;
var currentTarget;
var currentTargetString;
var s_cost, t_cost, delta;

console.log('Welcome to Sigmoid CPU Miner...!');
console.log('Version: ', pjson.version + '\n');

// Mining settings from JSON files
const minerAddress = minerConfigJSON.miner_address;
const minerPrivateKey = minerConfigJSON.miner_private_key;
const contractAddress = minerConfigJSON.contract_address;
const isPool = minerConfigJSON.is_pool;
const poolUrl = minerConfigJSON.pool_url;
const maximumGas = minerConfigJSON.maximum_gas;

// Setting: wallet and contract loading
const keyring = caver.wallet.keyring.createFromPrivateKey(minerPrivateKey);
if (keyring._address != minerAddress) revert();
caver.wallet.add(keyring);
const tokenContract = new caver.contract(tokenContractJSON.abi, contractAddress);

// Pool rpc client loading
const rpcClient = jayson.client.http(poolUrl);

console.log('Miner account address: ' + minerAddress);
console.log('Miner private key: ' + minerPrivateKey);
console.log('Contract address: ' + contractAddress + '\n');

console.log('------------------------------------------------------------------------');
// Check which hashing algorithm to use and Balloon hashing parameters.
// Need not to do this often.
async function set_hashing_parameters() {
    is_balloon = await tokenContract.methods.isBalloon().call();
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
}

// Check blockhash, difficulty, etc.
async function set_parameters() {
    var miningAddress = minerAddress;
    if (isPool) {
        var args = [];
        miningAddress = await new Promise(function (fulfilled, rejected) {
            rpcClient.request('getPoolEthAddress', args, function(err, response) {
               if (err) {rejected(err); return;}
               if (typeof response == 'undefined') {rejected(response); return;}
               fulfilled(response.result)
            });
        });
        previousBlockHash = await new Promise(function(fulfilled, rejected) {
            rpcClient.request('getChallengeNumber', args, function(err, response) {
                if (err) {rejected(err); return;}
                if (typeof response == 'undefined') {rejected(response); return;}
                fulfilled(response.result)
            });
        });
        currentTargetString = await new Promise(function(fulfilled, rejected) {
            rpcClient.request('getMinimumShareTarget', [minerAddress], function(err, response) {
                if (err) {rejected(err); return;}
                if (typeof response == 'undefined') {rejected(response); return;}
                fulfilled(response.result)
            });
        });
    } else {
        previousBlockHash = await tokenContract.methods.getPreviousBlockHash().call();
        currentTargetString = await tokenContract.methods.getCurrentTarget().call();  
    }
    currentTarget = caver.utils.toBN(currentTargetString).toString(16);

    console.log('Current target: 0x' + currentTarget);
    CPUMiner.setDifficultyTarget(currentTarget);
    console.log('Previous Block Hash: ' + previousBlockHash + '\n');
    CPUMiner.setChallengeNumber(previousBlockHash);
    CPUMiner.setMinerAddress(miningAddress);
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
                    submit(sol);
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
    if (isPool) {
        var args = [];
        args[0] = nonce;
        args[1] = minerAddress;
        args[2] = previousBlockHash;

        var _poolSubmit = function () {
            return new Promise(function (fulfilled,rejected) {
                rpcClient.request('submitShare', args, function(err, response) {
                   if (err) {rejected(err); return;}
                   if (typeof response == 'undefined') {rejected(response); return;}
                   fulfilled(response.result)
                });
            });
        };

        _poolSubmit()
        .then(console.log('Submitted the nonce to the pool.'));
    } else {
        tokenContract.methods.mint(nonce).send({from: minerAddress, gas: maximumGas})
        .then(function(receipt) {
            console.log('tx hash: ' + receipt.transactionHash);
            console.log('gas: ' + receipt.gas);
            console.log('gasPrice: ' + receipt.gasPrice);
            console.log('gasUsed: ' + receipt.gasUsed + '\n');
            console.log('------------------------------------------------------------------------');
        });
    }
}

set_hashing_parameters()
.then(mine());