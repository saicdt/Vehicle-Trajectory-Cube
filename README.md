# Vehicle-Trajectory-Cube

The Nanocube data structure developed by AT&T provides real-time exploration of large multidimensional spatiotemporal datasets with billions of entries. Algorithms have been presented to compute and query nanocube, and show how it can be used to generate well-known visual encodings such as heatmaps, histograms, and parallel coordinate plots. 

However, the origial releases of Nanocube are nothing more than a simple engine for academic demo. It is unstable, unrobust, not user-friendly, highly resouce-consuming, thus unable to be used widely, eg, in a real company's PROD environment.

Here we release a fork from Nanocubes. Goals of this approcach include:
>1 Improve the performance and user experience<br>
2 Abate the resource costs<br>
3 Add functionalities to the front end<br>
4 Improve the stablility of the back end<br>
...<br>

We hope these efforts will make the production applicable for company use.

For the first release, we did some optimization on network transfer, and thus improved the performance by more than 5X. We will also apply Baidu map for CN users.

Below is the typical process for NC install.

## Installing prerequisites

The following are prerequisites for all systems:

The nanocubes server is 64-bit only. There is NO support on 32-bit operating systems.
The nanocubes server is written in C++ 11. You must use a recent version of gcc (>= 4.8).
The nanocubes server uses Boost. You must use version 1.48 or later.
To build the nanocubes server, you must have the GNU build system installed.
Linux (Ubuntu)

On a newly installed 64-bit Ubuntu 14.04 system, gcc/g++ is already 4.8.2, but you should install the following packages:

sudo apt-get install build-essential
sudo apt-get install automake
sudo apt-get install libtool
sudo apt-get install zlib1g-dev
sudo apt-get install libboost-all-dev
sudo apt-get install libcurl4-openssl-dev
The support for Ubuntu 16.04 is currently being tested (due to changes in gcc 5), please try it out with the master version.

Linux (CentOS 6)

Install updated tools from Software Collections

sudo yum install https://www.softwarecollections.org/en/scls/rhscl/devtoolset-3/epel-6-x86_64/download/rhscl-devtoolset-3-epel-6-x86_64.noarch.rpm
sudo yum install https://www.softwarecollections.org/en/scls/denisarnaud/boost157/epel-6-x86_64/download/denisarnaud-boost157-epel-6-x86_64.noarch.rpm
sudo yum install https://www.softwarecollections.org/en/scls/praiskup/autotools/epel-6-x86_64/download/praiskup-autotools-epel-6-x86_64.noarch.rpm
sudo yum updateinfo

sudo yum install curl-devel
sudo yum install zlib-devel
sudo yum install autotools-latest
sudo yum install boost157-devel
sudo yum install devtoolset-3-gcc-c++
Then switch to the software collection environment for the new tools and libraries

scl enable devtoolset-3 autotools-latest bash
export BOOST_ROOT=/usr/include/boost157
export LDFLAGS=-L/usr/lib64/boost157
Mac OS X (10.9 and 10.10)

Example installation on Mac OS 10.9 Mavericks and 10.10 Yosemite with a local homebrew:

git clone https://github.com/mxcl/homebrew.git
Set your path to use this local homebrew

export PATH=${PWD}/homebrew/bin:${PATH}
Install the packages (This assumes your g++ has been installed by XCode)

brew install boost libtool autoconf automake
Set path to the boost directory

export BOOST_ROOT=${PWD}/homebrew

## Compiling the latest release

set env:
export NANOCUBE_SRC=/data/nanocube-3.2.1 && \
export NANOCUBE_BIN=$NANOCUBE_SRC/bin && export PATH=$NANOCUBE_BIN:$PATH &&  \
export BOOST_ROOT=/usr/include/boost157 && export LDFLAGS=-L/usr/lib64/boost157 && \
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:/usr/lib &&\
scl enable devtoolset-3 autotools-latest bash ;
cd $NANOCUBE_SRC

cd $NANOCUBE_SRC &&   rm -rf build && mkdir build && cd /data/nanocube-3.2.1/build/  \
&& ../configure --prefix=$NANOCUBE_SRC --with-tcmalloc CXXFLAGS="-O3"  --enable-multilib \
&& make  && make install && cd $NANOCUBE_SRC

## Running a nanocube

With the nanocube toolkit installed, we are ready to build a nanocube with the Chicago Crimes example dataset file included in the distribution. Here is the command:

cat $NANOCUBE_SRC/data/crime50k.dmp | nanocube-leaf -q 29512 -f 10000
The command above simply says to start a nanocube back-end process from the crime50k.dmp data file, answer queries on port 29512, and report statistics every 10,000 insertions. Sample output from this call is shown below. After inserting all 50,000 records, the nanocube is using 26MB of memory (approximately 20MB if you are using tcmalloc).

Output

VERSION: 3.2.1
query-port: 29512
(stdin     ) count:      10000 mem. res:          7MB. time(s):          0
(stdin     ) count:      20000 mem. res:         12MB. time(s):          0
(stdin     ) count:      30000 mem. res:         17MB. time(s):          0
(stdin     ) count:      40000 mem. res:         22MB. time(s):          0
(stdin     ) count:      50000 mem. res:         26MB. time(s):          0
(stdin:done) count:      50000 mem. res:         26MB. time(s):          0
Please note: If port 29512 is already in use, select another port and use it consistently throughout the examples below.

Please note: For lower level details on how to generate valid data for nanocubes go here

## Simple queries

With a nanocube process running, we are able to query this nanocube using the HTTP-based API. Using your favorite browser (assuming your favorite is Chrome, Firefox, or Safari), enter the following simple queries and verify the JSON objects returned are correct. Please note that differences in computers (e.g. compilers, libraries) may result in some of the data being returned in a different order (e.g. query 2 and query 3).

Query 1: Total count of all records

http://localhost:29512/count
Output

{ "layers":[  ], "root":{ "val":50000 } }
Interpretation

Starting at the root of the nanocube, we have 50,000 records in total.

Query 2: Schema of the nanocube

http://localhost:29512/schema

## Key features in the next release
1. Use Baidu map for CN users<br>
2. Use Nginx as web service engine<br>
3. **Upgrade from HTTP1.1 to 2.0, will get a significant speed up** <br>
4. Optimize user experience of operations on map<br>
