// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 LightPayCoin developers
// Copyright (c) 2018 The Starnodes developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (0, uint256("0x000001c4cc44c869aa98776e0802a274716661a54c16fedde8b7c509ef46e5a1"));
    

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1549987461, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
        (0, uint256("0x3ff088781f162dd56e9e773bc697d31fb20ffba091aa6cb68d611c2af0040735"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1549987461,
    0,
    2000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1524873600,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0xed;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x01;
        pchMessageStart[3] = 0xd6;
        vAlertPubKey = ParseHex("0438d21f5d5e1677c2805e2b623faf4c530214efeaafec04802aafe1895936a12741794eeb06d964196ab84bac40b7885b7b2c1b5824fb157591a84b13835d23ad");
        nDefaultPort = 22115;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Starnodes starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 9999999;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 70;
        nTargetSpacing = 1 * 70;
        nLastPOWBlock = 2000000;
        nMaturity = 15;
        nMasternodeCountDrift = 20;
        nMasternodeCollateralLimit = 2000000;
        nModifierUpdateBlock = 106000;
        nMaxMoneyOut = 50000000000 * COIN;
        const char* pszTimestamp = "Starnodes - High ROI masternode";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("049c4bf0b18b4b968c1136fa1fed29a02192eb4f7d249975e71dd955d6672c3b883e3f60442846747039b1065fb56c89177df6b09b46f71c8f8a02b7807aa42e42") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1549987461;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 20964820;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000003aa516942cef9f10b2f1d96fece432f6b3c542a51548489426b1dc14af2"));
        assert(genesis.hashMerkleRoot == uint256("0x79b5300d37009c025a1eaa9e8acb66f3680862d90d5c0750cc8998466ae0e24b"));

        vSeeds.push_back(CDNSSeedData("1", "45.32.238.57"));
	vSeeds.push_back(CDNSSeedData("2", "66.42.117.99"));
	vSeeds.push_back(CDNSSeedData("3", "80.240.21.160"));



        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63); // S
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 66); // T
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 60); // R
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;       // default true
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;       // default false
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "045d4fd262656b2ed7ae8294fc738dacb010f24e408bd33b2356fb921ff695b342522828f9758a535f4b7f517676678a9defb6df4a2bc26e66dd0fb303b0407493";
        strObfuscationPoolDummyAddress = "SNrp62NZDrwgxTQhP6JRhVKxQFWYsLRYKE";
        nStartMasternodePayments = 1549987461;

    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x5e;
        pchMessageStart[3] = 0x78;
        vAlertPubKey = ParseHex("043e8760d1c9ef3af5a5e49796afe4389a5cb53c6028b54b9af0a152f34762e453615a1aab9260a31045b85f87d4de36bbe6fd04478fcc103fd47c8e1b813c3d3c");
        nDefaultPort = 49795;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Starnodes: 1 day
        nTargetSpacing = 1 * 60;  // Starnodes: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nMasternodeCollateralLimit = 100000;
        nModifierUpdateBlock = 500;
        nMaxMoneyOut = 50000000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1549997540;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1235617300;


        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000cd2ff6be7bcbdc6b96e5260dfb00302ce9f17213d1e8c19d28164206f70"));
        assert(genesis.hashMerkleRoot == uint256("0x79b5300d37009c025a1eaa9e8acb66f3680862d90d5c0750cc8998466ae0e24b"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("1", "45.76.123.6"));         // Single node address

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet starnodes addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet starnodes script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet starnodes BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet starnodes BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet starnodes BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04d32fcf0e8ca12ae8cbed1e8fba544b995901a7fb259acc545fec89d2f65a05b3d280fc7b4eb032f7e8618aba98d6ba56b02857ed322eb7d228f9d0450b278144";
        strObfuscationPoolDummyAddress = "xxVKdbxVogrXrPLMo2qEEyCm1GRv2KZCLy";
        nStartMasternodePayments = 1524873600; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x53;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x40;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Starnodes: 1 day
        nTargetSpacing = 1 * 60;        // Starnodes: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1524873600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 906460;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 39793;
        // assert(hashGenesisBlock == uint256("00000d885e2813770fd59e71010b6b62a9b0609655109bf4e1b24c3bd524ae0c"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 39791;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
