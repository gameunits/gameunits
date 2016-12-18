// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

//#include "chainparamsseeds.h"

unsigned int pnSeed[] =
{
     //0x047ffe33, 0xa646c405, 0x0e550905, 
};


int64_t CChainParams::GetProofOfWorkReward(int nHeight, int64_t nFees) const
{
    // miner's coin base reward
    int64_t nSubsidy = 0;
    
    if (nHeight <= 10)
        nSubsidy = 0 * COIN;
    else
    if (nHeight <= 110)
        nSubsidy = 30000 * COIN;    // 3m Premine for Gameunits Headquarters 2017-2020
    else
    if (nHeight <= nLastPOWBlock)
        nSubsidy = 0 * COIN;
    
    if (fDebug && GetBoolArg("-printcreation"))
        LogPrintf("GetProofOfWorkReward() : create=%s nSubsidy=%d\n", FormatMoney(nSubsidy).c_str(), nSubsidy);
    
    return nSubsidy + nFees;
};


int64_t CChainParams::GetProofOfStakeReward(int64_t nCoinAge, int64_t nFees) const
{
    // miner's coin stake reward based on coin age spent (coin-days)
    int64_t nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 + 8);

	
        if(pindexBest->nHeight+1 >= 111 && pindexBest->nHeight+1 <= 300)   
    {
        nSubsidy = 0 * COIN;   // no stake rewards till PoS v2
    }
        else if(pindexBest->nHeight+1 >= 301 && pindexBest->nHeight+1 <= 24479)
    {
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 +8);
    }
        else if(pindexBest->nHeight+1 >= 24480 && pindexBest->nHeight+1 <= 24480)
    {
        nSubsidy = 1000 * COIN;  // Megablock 1
    }
    else if(pindexBest->nHeight+1 >=24481 && pindexBest->nHeight+1 <= 44639)
    { 
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 +8);   // 50% first year
    }
    else if(pindexBest->nHeight+1 >= 44640 && pindexBest->nHeight+1 <= 44640)
    { 
        nSubsidy = 1000 * COIN;  // Megablock 2 
    }
    else if(pindexBest->nHeight+1 >= 44641 && pindexBest->nHeight+1 <= 64799)
    {
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 +8);
    }
    else if(pindexBest->nHeight+1 >= 64800 && pindexBest->nHeight+1 <=64800)
    { 
        nSubsidy = 1500 * COIN;  // Megablock 3 
    }
    else if(pindexBest->nHeight+1 >= 64801 && pindexBest->nHeight+1 <= 84959)
    {
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 +8);
    }
    else if(pindexBest->nHeight+1 >= 84960 && pindexBest->nHeight+1 <= 84960)
    { 
        nSubsidy = 2500 * COIN;  // Megablock 4 
    }
    else if(pindexBest->nHeight+1 >= 84961 && pindexBest->nHeight+1 <= 105119)
    {
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 +8);
    }
    else if(pindexBest->nHeight+1 >= 105120 && pindexBest->nHeight+1 <= 105120)
    { 
        nSubsidy = 5000 * COIN;  // Megablock 5 
    }
    else if(pindexBest->nHeight+1 >= 105121 && pindexBest->nHeight+1 <= nFirstYearBlock)
    {
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 +8);    // 50% first year
    }
    else if(pindexBest->nHeight+1 > nFirstYearBlock && pindexBest->nHeight+1 <= nSecondYearBlock)
    {
        nSubsidy = nCoinAge * MCOIN_YEAR_REWARD * 33 / (365 * 33 +8);   // 25% second year
    }
    else if(pindexBest->nHeight+1 > nSecondYearBlock && pindexBest->nHeight+1 <= nThirdYearBlock)
    {
        nSubsidy = nCoinAge * OCOIN_YEAR_REWARD * 33 / (365 * 33 +8);   // 10% third year
    }
    else if(pindexBest->nHeight+1 > nThirdYearBlock && pindexBest->nHeight+1 <= nFourthYearBlock)
    {
        nSubsidy = nCoinAge * ICOIN_YEAR_REWARD * 33 / (365 * 33 +8);   // 5% fourth year
    }
    else if(pindexBest->nHeight+1 > nFourthYearBlock)
    {
        nSubsidy = nCoinAge * NCOIN_YEAR_REWARD * 33 / (365 * 33 +8);   // 2% till supply reaches 21m
    }
    
    if (fDebug && GetBoolArg("-printcreation"))
        LogPrintf("GetProofOfStakeReward(): create=%s nCoinAge=%d\n", FormatMoney(nSubsidy).c_str(), nCoinAge);
    
    return nSubsidy + nFees;
}



//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// Convert the pnSeeds6 array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, unsigned int *data, unsigned int count, int port)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in_addr ip;
        memcpy(&ip, &pnSeed[i], sizeof(ip));
        CAddress addr(CService(ip, Params().GetDefaultPort()));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x13;
        pchMessageStart[1] = 0xfa;
        pchMessageStart[2] = 0x37;
        pchMessageStart[3] = 0x2f;
        
        vAlertPubKey = ParseHex("0431a08fafcf6aeb8d471cc418eb89b0991dfa6de65a4e1b928187dda9a3d680d90b17e40cd3565ec193271ccdfba998b0e1ac3ce41675d738521388628c4b4940");
        
        nDefaultPort = 1338;
        nRPCPort = 1337;
        
        nFirstPosBlock = 111; 
        nFirstPosv2Block = 300;
        
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20); // "standard" scrypt target limit for proof of work, results with 0,000244140625 proof-of-work difficulty
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 48);
        
        const char* pszTimestamp = "△ Whatever you seek, whatever you dream, whatever you hope, all is possible if you follow the Light △ 11/06/16";
        CTransaction txNew;
        txNew.nTime = GENESIS_BLOCK_TIME;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = GENESIS_BLOCK_TIME;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 88473;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000743190fbaea62d4748157e22ef44850668c071f3709883b83ef24ec0ff"));
        assert(genesis.hashMerkleRoot == uint256("0x8f2d39604893b2588767903bc075befec96f0883832a8ca62a102a680c64b394"));
        
        vSeeds.push_back(CDNSSeedData("91.121.108.101", "91.121.108.101"));
        vSeeds.push_back(CDNSSeedData("91.121.108.101", "91.121.108.101"));

        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(68)                    .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(115)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(197)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0xEA)(0x91)(0x10)(0x49).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0xEA)(0x91)(0x52)(0xB8).convert_to_container<std::vector<unsigned char> >();
        
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nFirstYearBlock = 529900; // 525600 blocks per year + 4300 blocks 
        nSecondYearBlock = 1055500; // + 1 year blocks average 
        nThirdYearBlock = 1581100; // + 1 year blocks average 
        nFourthYearBlock = 2106700; // + 1 year blocks average 
        
        nLastPOWBlock = 300;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const std::vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    std::vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;

//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x10;
        pchMessageStart[2] = 0x70;
        pchMessageStart[3] = 0x2f;
        
        nFirstPosBlock = 111; 
        nFirstPosv2Block = 301;
        
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 16);
        
        vAlertPubKey = ParseHex("04ea7ed9441cfe7d149223301c40c7c6880ba8833302febbe2d4c195a33c18edef028d76ca8b3c37c614d592e65be3c29d3dd1156f1b1a5d066dd7f882fe2eaf43");
        nDefaultPort = 17997;
        nRPCPort = 17996;
        strDataDir = "testnet";

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 48194;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000e6e5fbcd90563e4389c8722e7a2cf00ffbfcd2b0af6b045ebd47abde95d1"));
        assert(genesis.hashMerkleRoot == uint256("0x8f2d39604893b2588767903bc075befec96f0883832a8ca62a102a680c64b394"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(112)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(177)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(250)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0x6F)(0xB3)(0xA3).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0x6F)(0x02)(0x0D).convert_to_container<std::vector<unsigned char> >();
        
        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        //nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x57;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0x2f;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
    //    genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        
     //   assert(hashGenesisBlock == uint256("0x"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

const CChainParams &TestNetParams() {
    return testNetParams;
}

const CChainParams &MainNetParams() {
    return mainParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network)
    {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    };
};

bool SelectParamsFromCommandLine()
{
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest)
    {
        return false;
    };

    if (fRegTest)
    {
        SelectParams(CChainParams::REGTEST);
    } else
    if (fTestNet)
    {
        SelectParams(CChainParams::TESTNET);
    } else
    {
        SelectParams(CChainParams::MAIN);
    };
    
    return true;
}
