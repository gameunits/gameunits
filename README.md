#Gameunits integration/staging tree
================================
Copyright (c) 2009-2011 Bitcoin Developers<br>
Copyright (c) 2011-2013 Litecoin Developers<br>
Copyright (c) 2013-2014 ShadowCoin Developers<br>
Copyright (c) 2015-2016 Moin Developers<br>
Copyright (c) 2015-2017 GameUnits Developers<br>

![GameUnits](http://i.imgur.com/Cokp8iC.png)

#What is GameUnits?
----------------
A new and exciting open source gaming currency that will revolutionize in-game purchases.

GameUnits is a forked version of Bitcoin using scrypt as a proof-of-work & proof-of-stake algorithm.
 - 13 million total coins
 - 1 blocks to retarget difficulty

# We :heart: Pull Requests!
Seriously, we really do.  It doesn't matter whether you're fixing a typo or overhauling a major area of the code base.  You will be showered in :thumbsup: :thumbsup: :thumbsup:<br>

#Compiling the GameUnits daemon from source on Debian
-----------------------------------------------------
The process for compiling the GameUnits daemon, gameunits-qt & gameunitsd, from the source code is pretty simple. This guide is based on the latest stable version of Debian Linux, though it should not need many modifications for any distro forked from Debian, such as Ubuntu and Xubuntu.

###Update and install dependencies for Gameunits-Qt

```
apt-get update && apt-get upgrade
apt-get install qt5-default qt5-qmake qtbase5-dev-tools qttools5-dev-tools \
    build-essential libboost-dev libboost-system-dev \
    libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev \
    libssl-dev libdb++-dev libminiupnpc-dev libqt5webkit5-dev git

	Then execute the following:
git clone https://github.com/gameunits/gameunits
cd gameunits
qmake
make
```

###Update and install dependencies for gameunitsd

```
apt-get update && apt-get upgrade
sudo apt-get install build-essential libssl-dev libdb++-dev libboost-all-dev libqrencode-dev git

	Then execute the following:
git clone https://github.com/gameunits/gameunits
cd gameunits/src
make -f makefile.unix
```

Development process
===========================

Developers work in their own trees, then submit pull requests when
they think their feature or bug fix is ready.

The patch will be accepted if there is broad consensus that it is a
good thing.  Developers should expect to rework and resubmit patches
if they don't match the project's coding conventions (see coding.txt)
or are controversial.

The master branch is regularly built and tested, but is not guaranteed
to be completely stable. Tags are regularly created to indicate new
stable release versions of Gameunits.

Feature branches are created when there are major new features being
worked on by several people.

From time to time a pull request will become outdated. If this occurs, and
the pull is no longer automatically mergeable; a comment on the pull will
be used to issue a warning of closure. The pull will be closed 15 days
after the warning if action is not taken by the author. Pull requests closed
in this manner will have their corresponding issue labeled 'stagnant'.

Issues with no commits will be given a similar warning, and closed after
15 days from their last activity. Issues closed in this manner will be 
labeled 'stale'.

