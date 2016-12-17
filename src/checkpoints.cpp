// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0, uint256("0x00000b5f443912867c4717556e94bfab9ff48cfc9926f9c5a49bb04e277fd59c") ) // Params().HashGenesisBlock())
        ( 300, uint256("0x00000321b789d306c1dd0f7ce50c5d19a08161948952da7b7a889481b50ce361") ) 
        ( 10000, uint256("0x9becec254ad78d5a5442a1bc797f42fb5677a43c802a6c6032e6596231662500") )
        ( 20000, uint256("0xb9c3a27a0698f32ae2dc120cd41e0fdb27fbfbab69177aed33adb5b3cbcbd270") )
        ( 30000, uint256("0x750ff461c7f13f55a03a692434164b228d11c75d6f8efce2c6adae0d788c85d5") )
        ( 40000, uint256("0xe1fc90203562dc6546fbca60e668a81f12f1dc01cf2cd9e759c0d3da8c7b9254") )
        ( 50000, uint256("0x186380fa67dac1f3dd106e4257bbdf2a1322fc25081cee637642b0258af8623d") )
	( 60000, uint256("0x6bb2e8cf4c22f5ced103291dded430aab915cbea1a0b3d726e87ed52bc2befec") )
        ( 70000, uint256("0x10cd4718b817524d8a9b9f247f4d4f9cae77efb204e307e884ff160ae0191f47") )
        ( 80000, uint256("0xc9a95718ba5ef54116ea20a4afb7b82721d0e7187b96a149e5d7851a92eb718a") )
        ( 90000, uint256("0xbbec501dc36c8bac40553d829a3992bdc47664641520481150fd7f31a2c5bfd2") )
        ( 100000, uint256("0x9cab96c468075abf7ff36e0b721cd6bd923b931bf3bb87267e4530f27504dca6") )
        ( 110000, uint256("0x5b694f3eb70cd3903e44b21adb187000bffcacbf6050aeada2e82e4de7281262") )
	( 120000, uint256("0x6a8b0277d14b0a0808b2cfa2c178e92ce0a868061eef885ac749ff0aedd74396") )
        ( 130000, uint256("0xc2be325dc98aac7d2688626c876fa292b477fd33108039e6a9160163eaab8092") )
        ( 140000, uint256("0xd16ae0b9d93b3ac06973095e9762c085f7ea01ef0068681e1274c72cd861bef8") )
        ( 150000, uint256("0x9841585b5eeae61a3bf42fc32b998b0df66f7bf582217af8a31367b72ecd411a") )
        ( 160000, uint256("0x5fbb7c710fcf5d0aabbb34ffbb1af4c1e47bad8ed804c6c190373391994f2040") )
	( 170000, uint256("0x74349ba2ba92fc4ca21bf3c6376a7a042b73b35d7c9f40974e2a2729d92d9906") )
        ( 180000, uint256("0x9e9e760a55de9dae5912479658d5dc2cc5525a64dd827fd91a8783174c95964f") )
        ( 190000, uint256("0x84fc304c178a3c049c79d9c86623ec132f028a2f7cae89f3e95a50087a3413ea") )
    ;

    // TestNet has no checkpoints
    MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x0000d316cb03da99b4c1ff7be5f17a7ca68db8002d8b2b0ed6bcaf7ca7dd1256") ) // hashGenesisBlockTestNet
    ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end())
            return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    CBlockThinIndex* GetLastCheckpoint(const std::map<uint256, CBlockThinIndex*>& mapBlockThinIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockThinIndex*>::const_iterator t = mapBlockThinIndex.find(hash);
            if (t != mapBlockThinIndex.end())
                return t->second;
        }
        return NULL;
    }


    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Automatically select a suitable sync-checkpoint - Thin mode
    const CBlockThinIndex* AutoSelectSyncThinCheckpoint()
    {
        const CBlockThinIndex *pindex = pindexBestHeader;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        if(nNodeMode == NT_FULL)
        {
            const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

            if (nHeight <= pindexSync->nHeight)
                return false;
        }
        else {
            const CBlockThinIndex *pindexSync = AutoSelectSyncThinCheckpoint();

            if (nHeight <= pindexSync->nHeight)
                return false;
        }
        return true;
    }
}
