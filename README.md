# satori-kawpowminer - KAWPOW GPU Miner for Satori Blockchain

## What is Satori?

**Satori is a brand new blockchain** launching with the KAWPOW mining algorithm. As a fresh chain starting from block #1, the DAG (Directed Acyclic Graph) size begins at just **1GB**, making it mineable on virtually any GPU with 2GB+ of VRAM. This represents a unique opportunity for miners with older hardware to participate from day one.

### Key Satori Blockchain Facts:
- **Algorithm**: KAWPOW (Ravencoin-compatible, ProgPoW variant)
- **Starting DAG Size**: 1GB at genesis block
- **DAG Growth Rate**: ~8MB per week (increases every 7,500 blocks)
- **Block Time**: ~60 seconds
- **Minimum GPU Memory**: 2GB VRAM
- **Direct Mining Support**: Built-in HTTP/RPC - no stratum proxy needed!
- **Network Ports**: 8420 (mainnet), 18420 (testnet), 28420 (devnet)

Satori-kawpowminer is a fork of Ravencoin's [kawpowminer](https://github.com/RavenCommunity/kawpowminer), optimized for Satori blockchain. It is a derivative of Ethash enhanced with [Programmable Proof of Work](https://github.com/ifdefelse/progpow) for ASIC and FPGA resistance.

### Why Mine Satori from Day One?
* **Low DAG Size**: Starting at just 1GB means even older 2GB GPUs can mine efficiently
* **Early Adopter Advantage**: Lower network difficulty in the early days
* **Fair Launch**: No premine, everyone starts equal
* **Growing Ecosystem**: Be part of a new blockchain from the beginning

## Miner Features:
* Starting DAG size at block #1 is 1GB (Ravencoin compatible)
* EPOCH duration is 7,500 blocks (Ravencoin compatible)
* Direct solo mining to satorid/satori-qt via HTTP/RPC - no stratum proxy needed!
* Comprehensive NVIDIA GPU support:
  - Legacy: GTX 600/700 series (Kepler, compute 3.0+)
  - Modern: GTX 900 series through RTX 5090 (Maxwell to Blackwell)
  - Datacenter: Tesla, Quadro, A100, H100, H200, B100, B200
* AMD GPU support via OpenCL:
  - GCN 1.0+: HD 7000 series, R5/R7/R9 200/300 series
  - Polaris: RX 400/500 series (RX 470, 480, 570, 580, 590)
  - Vega: RX Vega 56/64, Radeon VII
  - RDNA1: RX 5000 series (RX 5500, 5600, 5700 XT)
  - RDNA2: RX 6000 series (RX 6600, 6700, 6800, 6900 XT)
  - RDNA3: RX 7000 series (RX 7600, 7700, 7800, 7900 XT/XTX)
* Intel GPU support via OpenCL:
  - Intel HD Graphics 4000 and newer
  - Intel Iris Graphics
  - Intel Iris Xe Graphics
  - Intel Arc A-series (A380, A750, A770)

### Network Information:
* **Mainnet**: Uses KAWPOW algorithm (use this miner)
* **Testnet**: Uses SHA256 CPU mining (this miner not needed)
* **Devnet**: Uses KAWPOW for testing (use this miner)

You do not need this software for Satori testnet. Testnet uses SHA256 CPU mining.
For devnet testing (KAWPOW), use this miner.
Satori-kawpowminer is for use on Satori mainnet and devnet. 

====

## Quick Start Guide for New Miners

### Step 1: Set Up Your Satori Node

Before mining, configure your Satori node (satorid or satori-qt):

1. **Create/edit satori.conf** (located in ~/.satori/ on Linux, %APPDATA%\Satori\ on Windows):
```
# Required for mining
miningaddress=YOUR_SATORI_ADDRESS_HERE
rpcuser=yourusername
rpcpassword=yourpassword
rpcallowip=127.0.0.1
rpcport=8420
server=1

# Optional: Increase RPC threads for better mining performance
rpcthreads=8
```

2. **Start your node and wait for sync**:
```bash
# Start the daemon
./satorid -daemon

# Check sync status
./satori-cli getblockchaininfo

# Check your mining address is set
./satori-cli getmininginfo
```

### Step 2: Choose Your Mining Method

## Usage Examples

### Pool Mining
    # For NVIDIA GPUs (CUDA)
    satori-kawpowminer -U -P stratum+tcp://SATORIaddress.worker@minersite.com:minerport
    
    # For AMD/Intel GPUs (OpenCL)
    satori-kawpowminer -G -P stratum+tcp://SATORIaddress.worker@minersite.com:minerport

### Direct Solo Mining (no proxy needed!)
    # IMPORTANT: satori-kawpowminer has built-in stratum support!
    # You do NOT need a separate stratum proxy for pool mining.
    # For solo mining, it can connect directly to satorid via HTTP/RPC:
    # For NVIDIA GPUs
    satori-kawpowminer -U -P http://mynodeusername:mynodepassword@127.0.0.1:8420
    
    # For AMD/Intel GPUs
    satori-kawpowminer -G -P http://mynodeusername:mynodepassword@127.0.0.1:8420
    
    # List available OpenCL devices (AMD/Intel)
    satori-kawpowminer --list-devices
    
    # Select specific GPU when multiple are present (0=first device)
    satori-kawpowminer -G --opencl-device 0 -P http://user:pass@127.0.0.1:8420
    
    # Intel GPU specific: May need to select platform
    satori-kawpowminer -G --opencl-platform 1 --opencl-device 0 -P http://user:pass@127.0.0.1:8420
    
Note: Direct mining uses the built-in HTTP/RPC support to connect directly to your Satori node
without needing a separate stratum proxy. Just set miningaddress="youraddress" in satori.conf!

====

## Requirements

### For NVIDIA GPUs:
- CUDA drivers (get from NVIDIA)
- Minimum 2GB VRAM (DAG starts at 1GB)

### For AMD GPUs:
- Latest AMD drivers with OpenCL support
- Minimum 2GB VRAM (DAG starts at 1GB)
- ROCm drivers recommended for Linux

### For Intel GPUs:
- Intel Graphics drivers with OpenCL support
- Windows: Download from Intel Driver Support Assistant
- Linux: Install intel-opencl-icd and beignet-opencl-icd packages
- Minimum 2GB shared memory (DAG starts at 1GB)

### Solo Mining Checklist:
If you are solo mining direct to satorid or satori-qt, before launching satori-kawpowminer, verify:
    * ✅ The node is fully synced (check with `satori-cli getblockchaininfo`)
    * ✅ The node is listening on the RPC port (8420 for mainnet, 18420 for testnet, 28420 for devnet, 38420 for regtest)
    * ✅ The node has miningaddress="youraddress" set in the satori.conf file
    * ✅ The node has rpcuser and rpcpassword set in the satori.conf file
    * ✅ The firewall allows connections on the RPC port (if mining from another machine)


===============

> Satori KAWPOW miner with OpenCL, CUDA and stratum support

**satori-kawpowminer** is a KAWPOW GPU mining worker: with satori-kawpowminer you can mine Satori, which relies on a KAWPOW-based Proof of Work. This is the actively maintained version for Satori blockchain. It originates from the [kawpowminer](https://github.com/RavenCommunity/kawpowminer) project. Check the original [ProgPoW](https://github.com/ifdefelse/progpow) implementation and [EIP-1057](https://eips.ethereum.org/EIPS/eip-1057) for specification.

## Features

* Optimized KAWPOW Satori miner software for miners
* **Built-in stratum support** - no separate proxy needed!
* **Direct HTTP/RPC mining** to satorid - no stratum proxy needed!
* OpenCL mining (AMD, Intel GPUs)
* Nvidia CUDA mining
* Realistic benchmarking against arbitrary epoch/DAG/blocknumber
* On-GPU DAG generation (no more DAG files on disk)
* Stratum mining without proxy (built-in stratum client)
* OpenCL devices picking
* Farm failover (getwork + stratum)

## GPU Support Matrix - Which Build Should You Use?

**Important**: Since Satori is a NEW blockchain with DAG starting at just 1GB, ANY GPU with 2GB+ VRAM can mine from day one! This is your chance to mine with older hardware.

### 🎯 Quick GPU Selection Guide

| Compute Capability | Architecture | Example GPUs | **USE THIS BUILD** | Why? |
|-------------------|--------------|--------------|-------------------|------|
| **sm_30, sm_32** | Kepler (2012) | GTX 660, 670, 680, 690, GT 640 | **Ancient** ✅ | ONLY build supporting these |
| **sm_35, sm_37** | Kepler (2013) | GTX 780, 780 Ti, Titan, Titan Black, K40 | **Legacy** ✅ | ONLY build supporting these |
| **sm_50** | Maxwell 1.0 | GTX 750, 750 Ti | **Standard** ✅ | ONLY build supporting these |
| **sm_52** | Maxwell 2.0 | GTX 950, 960, Titan X (Maxwell) | **Standard** ✅ | ONLY build supporting these |
| **sm_53** | Maxwell 2.0 | GTX 970, 980, 980 Ti, M40 | **Standard** ✅ | ONLY build supporting these |
| **sm_60** | Pascal | GTX 1060, Tesla P40, Quadro P5000 | **Standard** ✅ | ONLY build supporting these |
| **sm_61** | Pascal | GTX 1050, 1050 Ti, 1070, 1080, P106-100 | **Standard** ✅ | ONLY build supporting these |
| **sm_62** | Pascal | GTX 1080 Ti, Titan X/Xp (Pascal), P104-100 | **Standard** ✅ | ONLY build supporting these |
| **sm_70** | Volta | Titan V, Tesla V100 (PCIe/SMX2) | **Standard** ✅ | ONLY build supporting these |
| **sm_72** | Volta | Tesla V100 (NVLink), Quadro GV100 | **Standard** ✅ | ONLY build supporting these |
| **sm_75** | Turing | GTX 1650, 1660, RTX 2060, 2070, 2080, 2080 Ti | **Modern** 🔄 | Works with Standard but use Modern |
| **sm_80** | Ampere | A100 (PCIe/SMX4), A30 | **Modern** 🔄 | Works with Standard but use Modern |
| **sm_86** | Ampere | RTX 3050, 3060, 3070, 3080, 3090, A40 | **Modern** 🔄 | Works with Standard but use Modern |
| **sm_87** | Ampere | RTX 3060 Ti, 3070 Ti, 3080 Ti, 3090 Ti | **Modern** 🔄 | Works with Standard but use Modern |
| **sm_88** | Ampere Refresh | A100 (80GB), A800 | **Modern** ✅ | ONLY Modern supports this |
| **sm_89** | Ada Lovelace | RTX 4060, 4070, 4080, 4090, L4, L40 | **Modern** 🔄 | Works with Standard but use Modern |
| **sm_90, sm_90a** | Hopper | H100, H200, H800 | **Modern** 🔄 | Works with Standard but use Modern |
| **sm_100, 100f, 100a** | Grace Hopper | GH100, GH200 (Grace + Hopper) | **Modern** 🔄 | Both support but use Modern |
| **sm_101, 101f, 101a** | Blackwell Variant | Special Blackwell configs | **Standard** ⚠️ | ONLY Standard has these! |
| **sm_103, 103f, 103a** | Future Reserved | TBD | **Modern** 🔄 | Both support but use Modern |
| **sm_110, 110f, 110a** | Blackwell | RTX 5070, 5080, 5090, B100, B200 | **Modern** ✅ | ONLY Modern has these! |
| **sm_120, 120f, 120a** | Future Reserved | Next-gen after Blackwell | **Modern** 🔄 | Both support but use Modern |
| **sm_121, 121f, 121a** | Future Reserved | Next-gen after Blackwell | **Modern** 🔄 | Both support but use Modern |

### 📌 Which Build Should YOU Download?

**Legend:**
- ✅ = You MUST use this build (only one that supports your GPU)
- 🔄 = Your GPU works with multiple builds, but use the recommended one
- ⚠️ = Special case - pay attention!

**Simple Decision Guide:**
1. **GTX 600 series (except 780)** → Download **Ancient** build (CUDA 10.2)
2. **GTX 780/Titan** → Download **Legacy** build (CUDA 11.8)
3. **GTX 900/1000 series, Titan V** → Download **Standard** build (CUDA 12.9.1)
4. **RTX 2000/3000/4000/5000 series** → Download **Modern** build (CUDA 13.0)
5. **Special Blackwell configs (sm_101)** → Download **Standard** build (CUDA 12.9.1)
6. **AMD/Intel GPUs** → Download **OpenCL** build

| **AMD GPUs** | OpenCL Build | All GCN, RDNA, RDNA2, RDNA3 architectures |
| **Intel GPUs** | OpenCL Build | HD Graphics 4000+, Iris, Arc A-series |

### Complete CUDA Architecture Support Matrix

> **⚠️ CRITICAL BLACKWELL NOTE:**
> - **CUDA 12.9.1** supports sm_101/101f/101a BUT NOT sm_110/110f/110a
> - **CUDA 13.0** supports sm_110/110f/110a BUT NOT sm_101/101f/101a
> - This means some Blackwell GPUs need Standard build, others need Modern build!

**Detailed breakdown of which architectures each CUDA version supports:**

#### Ancient Build (CUDA 10.2) Architectures:
```
Supports: sm_30, sm_32, sm_35, sm_50, sm_52, sm_53, sm_60, sm_61, sm_62, sm_70, sm_72, sm_75
UNIQUE: sm_30, sm_32 (early Kepler - no other CUDA version supports these!)
```

#### Legacy Build (CUDA 11.8) Architectures:
```
Supports: sm_35, sm_37, sm_50, sm_52, sm_53, sm_60, sm_61, sm_62, sm_70, sm_72, sm_75, 
         sm_80, sm_86, sm_87, sm_89, sm_90
UNIQUE: sm_35, sm_37 (late Kepler - no other CUDA version we use supports these!)
```

#### Standard Build (CUDA 12.9.1) Architectures:
```
Supports: sm_50, sm_52, sm_53, sm_60, sm_61, sm_62, sm_70, sm_72, sm_75, sm_80, sm_86, 
         sm_87, sm_89, sm_90, sm_90a, sm_100, sm_100f, sm_100a, sm_101, sm_101f, sm_101a,
         sm_103, sm_103f, sm_103a, sm_120, sm_120f, sm_120a, sm_121, sm_121f, sm_121a
UNIQUE: sm_50-72 (Maxwell/Pascal/Volta) AND sm_101/101f/101a (special Blackwell variants)
⚠️ NOTE: Does NOT support sm_110/110f/110a (only CUDA 13.0 has these!)
```

#### Modern Build (CUDA 13.0) Architectures:
```
Supports: sm_75, sm_80, sm_86, sm_87, sm_88, sm_89, sm_90, sm_90a, sm_100, sm_100f, 
         sm_100a, sm_103, sm_103f, sm_103a, sm_110, sm_110f, sm_110a, sm_120, sm_120f, 
         sm_120a, sm_121, sm_121f, sm_121a
UNIQUE: sm_88 (Ampere refresh) AND sm_110/110f/110a (main Blackwell)
⚠️ NOTE: Does NOT support sm_101/101f/101a (only CUDA 12.9.1 has these!)
```

### NVIDIA GPU Support - 4 Builds Available

#### Build 1: Ancient (CUDA 10.2) - For 2012-2013 GPUs
**Unique Support**: Kepler sm_30, sm_32 (not available in newer builds)
- GTX 680, GTX 690, GTX 670, GTX 660 Ti, GTX 660
- GT 640 (GDDR5 2GB+), GT 630 (2GB+)
- Quadro K5000, K4200, K4000, K2200, K2000
- Tesla K10, K20, K20X

#### Build 2: Legacy (CUDA 11.8) - For 2013-2014 GPUs
**Unique Support**: Kepler sm_35, sm_37 (not available in CUDA 12.9+)
- GTX 780 Ti, GTX 780, GTX Titan, GTX Titan Black, GTX Titan Z
- Quadro K6000, Tesla K40, Tesla K80

**Also supports everything from Build 1 EXCEPT sm_30, sm_32**

#### Build 3: Standard (CUDA 12.9.1) - For 2014-2024 GPUs
**Unique Support**: Maxwell/Pascal/Volta (dropped in CUDA 13.0) + sm_101 Blackwell variants
- **Maxwell (2014-2016)**: GTX 750, GTX 750 Ti, GTX 950, GTX 960, GTX 970, GTX 980, GTX 980 Ti, GTX Titan X
- **Pascal (2016-2018)**: GTX 1050, GTX 1050 Ti, GTX 1060, GTX 1070, GTX 1070 Ti, GTX 1080, GTX 1080 Ti, Titan Xp
- **Volta (2017-2018)**: Titan V, Tesla V100, Quadro GV100
- **Plus sm_101 Blackwell variants** not available in CUDA 13.0

**Also supports all newer GPUs (Turing through Blackwell)**

#### Build 4: Modern (CUDA 13.0) - For 2018+ GPUs
**Unique Support**: sm_88 Ampere refresh + sm_110 Blackwell variants
**Minimum GPU**: GTX 1650, RTX 2060

Supported GPUs:
- **Turing (2018-2019)**: GTX 1650, GTX 1660, GTX 1660 Ti, RTX 2060, RTX 2070, RTX 2080, RTX 2080 Ti
- **Ampere (2020-2022)**: RTX 3050, RTX 3060, RTX 3060 Ti, RTX 3070, RTX 3080, RTX 3090, A100, A30
- **Ada Lovelace (2022-2024)**: RTX 4060, RTX 4060 Ti, RTX 4070, RTX 4070 Ti, RTX 4080, RTX 4090
- **Hopper (2022-2024)**: H100, H200
- **Blackwell (2025+)**: RTX 5060, RTX 5070, RTX 5080, RTX 5090, B100, B200, GB200

### Quick Decision Guide for NVIDIA:
- **Have GTX 600 series?** → Use CUDA 10.2 build
- **Have GTX 700 series (780/Titan)?** → Use CUDA 11.8 build  
- **Have GTX 900/1000 series or Volta?** → Use Standard build (CUDA 12.9.1)
- **Have RTX 2000 series or newer?** → Use CUDA 13.0 build (best performance)

### AMD GPU Support (OpenCL)
All builds support AMD GPUs with 2GB+ VRAM via OpenCL:
- **GCN 1.0-3.0**: HD 7950, HD 7970, R9 280X, R9 290X, R9 380X, R9 390X
- **GCN 4.0 (Polaris)**: RX 470, RX 480, RX 570, RX 580, RX 590
- **GCN 5.0 (Vega)**: Vega 56, Vega 64, Radeon VII
- **RDNA 1**: RX 5500 XT, RX 5600 XT, RX 5700, RX 5700 XT
- **RDNA 2**: RX 6400, RX 6500 XT, RX 6600, RX 6700 XT, RX 6800, RX 6900 XT
- **RDNA 3**: RX 7600, RX 7700 XT, RX 7800 XT, RX 7900 XT, RX 7900 XTX

### Intel GPU Support (OpenCL)
All builds support Intel GPUs with adequate shared memory via OpenCL:
- **Intel HD Graphics**: 4000+ series (Haswell and newer)
- **Intel Iris Graphics**: All models
- **Intel Iris Xe Graphics**: All models (11th gen+)
- **Intel Arc**: A380, A580, A750, A770


## Table of Contents

* [Install](#install)
* [Usage](#usage)
    * [Examples connecting to pools](#examples-connecting-to-pools)
* [Build](#build)
    * [Continuous Integration and development builds](#continuous-integration-and-development-builds)
    * [Building from source](#building-from-source)
* [Maintainers & Authors](#maintainers--authors)
* [Contribute](#contribute)
* [F.A.Q.](#faq)


## Install

[Releases][Releases]

Standalone **executables** for *Linux*, *macOS* and *Windows* are provided in
the [Releases] section.
Download an archive for your operating system and unpack the content to a place
accessible from command line. The satori-kawpowminer is ready to go.

| Builds | Release |
| ------ | ------- |
| Last   | [GitHub release](https://github.com/EchelonTechnologyGroup/satori-kawpowminer/releases) 


If you have trouble with missing .dll or CUDA errors, [please install the latest version of CUDA drivers](https://developer.nvidia.com/cuda-downloads) or report to project maintainers.

## Usage

The **satori-kawpowminer** is a command line program. This means you launch it either
from a Windows command prompt or Linux console, or create shortcuts to
predefined command lines using a Linux Bash script or Windows batch/cmd file.
For a full list of available command, please run:

```sh
satori-kawpowminer --help
```

### Examples connecting to pools

Example connecting to a Satori pool:

`./satori-kawpowminer -U -P stratum+tcp://<wallet>.worker@pooladdress:port` (NVIDIA)

`./satori-kawpowminer -G -P stratum+tcp://<wallet>.worker@pooladdress:port` (AMD/Intel)

`satori-kawpowminer.exe -U -P stratum+tcp://<wallet>.worker@pooladdress:port` (Windows NVIDIA)

`satori-kawpowminer.exe -G -P stratum+tcp://<wallet>.worker@pooladdress:port` (Windows AMD/Intel)

## Build Instructions

### Prerequisites

#### All Platforms:
- **Git**: For cloning the repository
- **CMake**: Version 3.16 or higher
- **Compiler**: GCC 8+ (Linux), Clang (macOS), MSVC 2019+ (Windows)

#### For NVIDIA GPU Support:
Choose your CUDA version based on your GPU (DAG requires 2GB+ VRAM):

**Build 1: CUDA 10.2** ("Ancient" - Kepler sm_30/32 support)
- **UNIQUE Support**: GTX 680, GTX 690, GTX 670, GTX 660 (sm_30, sm_32)
- **Also supports**: Everything through Turing
- Download: https://developer.nvidia.com/cuda-10.2-download-archive

**Build 2: CUDA 11.8** ("Legacy" - Kepler sm_35/37 support)  
- **UNIQUE Support**: GTX 780, GTX Titan, Tesla K40 (sm_35, sm_37)
- **Also supports**: Everything through Hopper (except sm_30/32)
- Download: https://developer.nvidia.com/cuda-11-8-0-download-archive

**Build 3: Standard (CUDA 12.9.1)** - Maxwell/Pascal/Volta support
- **UNIQUE Support**: Maxwell (sm_50-53), Pascal (sm_60-62), Volta (sm_70-72)
- **⚠️ SPECIAL**: CUDA 12.9.1 has sm_101 variants but NOT sm_110
- **⚠️ IMPORTANT**: CUDA 13.0 has sm_110 variants but NOT sm_101
- **Minimum GPU**: GTX 750, GTX 750 Ti
- **Maximum GPU**: Titan V, Tesla V100
- Download: https://developer.nvidia.com/cuda-12-9-1-download-archive

**Build 4: Modern (CUDA 13.0)** - Latest optimizations
- **UNIQUE Support**: sm_88 Ampere, sm_110 Blackwell variants
- **Minimum GPU**: GTX 1650, RTX 2060 (Turing sm_75)
- **Best for**: RTX 20/30/40/50 series
- Download: https://developer.nvidia.com/cuda-downloads

**Quick GPU to Build Guide:**
- GTX 600 series (except 780) → CUDA 10.2
- GTX 780/Titan → CUDA 11.8
- GTX 900/1000 series, Volta → Standard (CUDA 12.9.1)
- RTX series → CUDA 13.0 (recommended)

#### For AMD GPU Support:
- **Linux**: ROCm drivers or Mesa OpenCL
- **Windows**: Latest AMD Radeon drivers (includes OpenCL)

#### For Intel GPU Support:
- **Linux**: Intel Compute Runtime
- **Windows**: Latest Intel Graphics drivers

####The OpenCL ICDs (Installable Client Drivers) are only needed at runtime to actually use GPUs:
- **ocl-icd-opencl-dev** - OpenCL loader (finds ICDs)
- **intel-opencl-icd** - For Intel GPUs
- **mesa-opencl-icd** - For AMD GPUs (basic)
- **nvidia-cuda-toolkit** - For NVIDIA GPUs

####For ROCM on Ubuntu 24.04 (Noble)
    wget https://repo.radeon.com/amdgpu-install/latest/ubuntu/noble/amdgpu-install_6.4.60403-1_all.deb
    sudo apt install ./amdgpu-install_6.4.60403-1_all.deb
    sudo amdgpu-install --usecase=rocm,opencl --no-dkms
    sudo reboot

####For ROCM On Ubuntu 22.04 (Jammy) Use This Link Instead When Running wget Above
    wget https://repo.radeon.com/amdgpu-install/latest/ubuntu/jammy/amdgpu-install_6.4.60403-1_all.deb
---

### Linux Build Instructions

## 📦 Complete Ubuntu 24.04 LTS Build Guide (Step-by-Step)

This guide will walk you through building satori-kawpowminer on Ubuntu 24.04 LTS from scratch.

#### Step 1: Install Dependencies

**Ubuntu 24.04 / Debian 12 - Complete Dependencies:**
```bash
# Update package list
sudo apt-get update

# Essential build tools and libraries (REQUIRED)
sudo apt-get install -y \
    git \
    cmake \
    build-essential \
    pkg-config \
    libboost-all-dev \
    libssl-dev

# OpenCL support for AMD/Intel GPUs (OPTIONAL - skip if NVIDIA only)
sudo apt-get install -y \
    ocl-icd-opencl-dev \
    opencl-headers \
    clinfo

# Intel GPU specific (OPTIONAL)
sudo apt-get install -y \
    intel-opencl-icd \
    beignet-opencl-icd

# AMD GPU specific (OPTIONAL)
# Option 1: Mesa OpenCL (basic support)
sudo apt-get install -y mesa-opencl-icd

# Option 2: ROCm (better performance)
# Follow: https://rocm.docs.amd.com/en/latest/deploy/linux/quick_start.html

# NVIDIA CUDA Installation (CHOOSE ONLY ONE based on your GPU)

# Option A: CUDA 10.2 (GTX 600 series - Kepler sm_30/32)
wget https://developer.download.nvidia.com/compute/cuda/10.2/Prod/local_installers/cuda_10.2.89_440.33.01_linux.run
sudo sh cuda_10.2.89_440.33.01_linux.run --toolkit --silent --override
export PATH=/usr/local/cuda-10.2/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-10.2/lib64:$LD_LIBRARY_PATH

# Option B: CUDA 11.8 (GTX 700 series - Kepler sm_35/37)
wget https://developer.download.nvidia.com/compute/cuda/11.8.0/local_installers/cuda_11.8.0_520.61.05_linux.run
sudo sh cuda_11.8.0_520.61.05_linux.run --toolkit --silent --override
export PATH=/usr/local/cuda-11.8/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-11.8/lib64:$LD_LIBRARY_PATH

# Option C: CUDA 12.9.1 (GTX 900/1000 series - RECOMMENDED FOR MOST USERS)
wget https://developer.download.nvidia.com/compute/cuda/12.9.0/local_installers/cuda_12.9.0_560.28.03_linux.run
sudo sh cuda_12.9.0_560.28.03_linux.run --toolkit --silent --override
export PATH=/usr/local/cuda-12.9/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-12.9/lib64:$LD_LIBRARY_PATH

# Option D: CUDA 13.0 (RTX 2000+ series - Latest optimizations)
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2404/x86_64/cuda-keyring_1.1-1_all.deb
sudo dpkg -i cuda-keyring_1.1-1_all.deb
sudo apt-get update
sudo apt-get install -y cuda-toolkit-13-0
export PATH=/usr/local/cuda-13.0/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-13.0/lib64:$LD_LIBRARY_PATH

# Verify installations
nvidia-smi      # Check NVIDIA driver (if installed)
clinfo          # Check OpenCL devices (if installed)
nvcc --version  # Check CUDA version (if installed)
```

**Fedora/RHEL/CentOS:**
```bash
# Build essentials
sudo dnf install -y git cmake gcc-c++ make

# Boost libraries
sudo dnf install -y boost-devel

# OpenCL support
sudo dnf install -y ocl-icd-devel opencl-headers
```

**Arch Linux:**
```bash
# Build essentials and dependencies
sudo pacman -S git cmake gcc boost opencl-headers ocl-icd
```

#### Step 2: Clone and Build

```bash
# Clone the repository
git clone https://github.com/EchelonTechnologyGroup/satori-kawpowminer.git
cd satori-kawpowminer

# Initialize submodules (IMPORTANT!)
git submodule update --init --recursive

# Create build directory
mkdir build && cd build

# Configure based on your hardware:
# For NVIDIA + AMD/Intel GPUs:
cmake .. -DETHASHCUDA=ON -DETHASHCL=ON -DAPICORE=ON -DCMAKE_BUILD_TYPE=Release

# For NVIDIA only:
cmake .. -DETHASHCUDA=ON -DETHASHCL=OFF -DAPICORE=ON -DCMAKE_BUILD_TYPE=Release

# For AMD/Intel only:
cmake .. -DETHASHCUDA=OFF -DETHASHCL=ON -DAPICORE=ON -DCMAKE_BUILD_TYPE=Release

# Build (using all CPU cores)
make -j$(nproc)

# The executable will be in: satori-kawpowminer/satori-kawpowminer
# Test it:
./satori-kawpowminer/satori-kawpowminer --list-devices

# Optional: Install system-wide
sudo make install
```

**Build Options:**
- `-DETHASHCUDA=OFF`: Disable NVIDIA support (if no CUDA)
- `-DETHASHCL=OFF`: Disable OpenCL support (AMD/Intel)
- `-DAPICORE=OFF`: Disable API support
- `-DCMAKE_BUILD_TYPE=Debug`: Build with debug symbols

---

### Windows Build Instructions

## 📦 Complete Visual Studio 2022 Build Guide

**IMPORTANT CUDA Compatibility Note:**
- CUDA 10.2 & 11.8: Work with Visual Studio 2017, 2019, 2022
- CUDA 12.9.1: Works with Visual Studio 2019, 2022 (NOT VS 2017)
- CUDA 13.0: Works with Visual Studio 2019, 2022 (NOT VS 2017)

#### Step 1: Install Prerequisites

1. **Visual Studio 2022 Community Edition** (Free, Recommended)
   - Download: https://visualstudio.microsoft.com/downloads/
   - During installation, select these workloads:
     - ✅ "Desktop development with C++"
     - ✅ "C++ CMake tools for Windows"
     - ✅ "Windows 10/11 SDK (latest)"
     - ✅ "MSVC v143 - VS 2022 C++ x64/x86 build tools"

2. **Git for Windows**
   - Download: https://git-scm.com/download/win

3. **Perl** (required for OpenSSL)
   - Download Strawberry Perl: https://strawberryperl.com/
   - Install to default location (C:\Strawberry)

4. **CUDA Toolkit** (Choose ONE based on your GPU)
   
   **For GTX 600 series (Kepler sm_30/32):**
   - Download CUDA 10.2: https://developer.nvidia.com/cuda-10.2-download-archive
   - Select: Windows → x86_64 → 10 → exe (local)
   - Install with default settings
   
   **For GTX 700 series (Kepler sm_35/37):**
   - Download CUDA 11.8: https://developer.nvidia.com/cuda-11-8-0-download-archive
   - Select: Windows → x86_64 → 11 → exe (local)
   - Install with default settings
   
   **For GTX 900/1000 series (Maxwell/Pascal) - MOST COMMON:**
   - Download CUDA 12.9.1: https://developer.nvidia.com/cuda-12-9-1-download-archive
   - Select: Windows → x86_64 → 11 → exe (local)
   - Install with default settings
   
   **For RTX 2000+ series (Turing/Ampere/Ada):**
   - Download CUDA 13.0: https://developer.nvidia.com/cuda-downloads
   - Select: Windows → x86_64 → 11 → exe (local)
   - Install with default settings

#### Step 2: Build Using Command Line

**IMPORTANT**: Open "x64 Native Tools Command Prompt for VS 2022" from the Start Menu
(NOT regular Command Prompt or PowerShell!)

```cmd
# Clone the repository
git clone https://github.com/EchelonTechnologyGroup/satori-kawpowminer.git
cd satori-kawpowminer

# Initialize submodules
git submodule update --init --recursive

# Create build directory
mkdir build
cd build

REM Configure for Visual Studio 2022 (RECOMMENDED)
cmake -G "Visual Studio 17 2022" -A x64 -DETHASHCUDA=ON -DETHASHCL=ON -DAPICORE=ON ..

REM If you get CUDA errors with newer CUDA versions, try:
cmake -G "Visual Studio 17 2022" -A x64 -T v142 -DETHASHCUDA=ON -DETHASHCL=ON -DAPICORE=ON ..

REM Build the Release version (this will take a few minutes)
cmake --build . --config Release

REM The executable will be in: build\satori-kawpowminer\Release\satori-kawpowminer.exe
REM Test it:
satori-kawpowminer\Release\satori-kawpowminer.exe --list-devices
```

#### Step 3: (Alternative) Build Using Visual Studio GUI

1. Open Visual Studio 2022
2. On the start screen, select "Clone a repository"
3. Enter repository URL: `https://github.com/EchelonTechnologyGroup/satori-kawpowminer.git`
4. Click "Clone"
5. After cloning completes, Visual Studio will detect CMakeLists.txt
6. In the configuration dropdown (top toolbar), select "x64-Release"
7. Build → Build All (or press F7)
8. Find executable in: `out\build\x64-Release\satori-kawpowminer\satori-kawpowminer.exe`

---

### macOS Build Instructions

#### Step 1: Install Dependencies

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake boost git

# For OpenCL support (included with macOS)
# No additional installation needed
```

#### Step 2: Clone and Build

```bash
# Clone the repository
git clone https://github.com/EchelonTechnologyGroup/satori-kawpowminer.git
cd satori-kawpowminer

# Initialize submodules
git submodule update --init --recursive

# Create build directory
mkdir build && cd build

# Configure (OpenCL only, no CUDA on macOS)
cmake .. -DETHASHCUDA=OFF -DETHASHCL=ON -DAPICORE=ON

# Build
make -j$(sysctl -n hw.ncpu)

# The executable will be in: satori-kawpowminer/satori-kawpowminer
```

#### Troubleshooting Windows Build Issues

**Common Issues and Solutions:**

1. **"CUDA not found" error:**
   - Ensure CUDA is installed to default location
   - Restart your command prompt after CUDA installation
   - Try specifying CUDA path: `cmake -DCUDA_TOOLKIT_ROOT_DIR="C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.9" ...`

2. **"Missing MSVCR140.dll" when running:**
   - Install Visual C++ Redistributables: https://aka.ms/vs/17/release/vc_redist.x64.exe

3. **"nvrtc64_*.dll not found" error:**
   - Copy missing DLLs from CUDA installation:
   ```cmd
   copy "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.9\bin\nvrtc64_*.dll" .
   ```

4. **Build fails with CUDA 12.9/13.0 on older Visual Studio:**
   - CUDA 12.9.1+ requires VS 2019 or newer
   - If using VS 2017, stick with CUDA 11.8 or older

---

### Cross-Compilation

#### Linux to Windows (using MinGW)

```bash
# Install MinGW
sudo apt-get install -y mingw-w64

# Configure for Windows build
mkdir build-win && cd build-win
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-mingw64.cmake \
         -DETHASHCUDA=OFF -DETHASHCL=ON -DAPICORE=ON

# Build
make -j$(nproc)
```

---

### Troubleshooting Build Issues

**CUDA not found:**
- Ensure CUDA toolkit is installed
- Add CUDA to PATH: `export PATH=/usr/local/cuda/bin:$PATH`
- Set CUDA_HOME: `export CUDA_HOME=/usr/local/cuda`

**OpenCL not found:**
- Install OpenCL headers: `opencl-headers` package
- Install ICD loader: `ocl-icd-opencl-dev` package

**Boost not found:**
- Ubuntu/Debian: `sudo apt-get install libboost-all-dev`
- Windows: Download from https://www.boost.org/users/download/

**Build fails on older systems:**
- Try using an older CUDA version (11.8 for maximum compatibility)
- Ensure GCC version is compatible with CUDA version

---

### Verifying Your Build

After building, verify the miner works:

```bash
# List available devices
./satori-kawpowminer --list-devices

# Show version and capabilities
./satori-kawpowminer --version

# Benchmark mode (tests mining without connecting to pool)
./satori-kawpowminer -U -M
```

## Optimizing Your Satori Mining Setup

### Best Settings for Different GPUs

Since Satori starts with a 1GB DAG, you can optimize for efficiency rather than just raw hashrate:

#### NVIDIA Optimization (MSI Afterburner)
```
GTX 1060/1070/1080:
- Power Limit: 75-80%
- Core Clock: -100 MHz
- Memory Clock: +500 MHz
- Expected: 12-24 MH/s

RTX 3060/3070/3080:
- Power Limit: 70-75%
- Core Clock: -200 MHz
- Memory Clock: +1000 MHz
- Expected: 25-45 MH/s

RTX 4070/4080/4090:
- Power Limit: 65-70%
- Core Clock: -250 MHz
- Memory Clock: +1200 MHz
- Expected: 40-65 MH/s
```

#### AMD Optimization (AMD Software)
```
RX 580/590:
- Core: 1150 MHz
- Memory: 2000 MHz
- Power: -20%
- Expected: 10-14 MH/s

RX 6700 XT/6800 XT:
- Core: 1200 MHz
- Memory: 2100 MHz
- Power: -15%
- Expected: 25-35 MH/s
```

### Multi-GPU Mining Configuration

```bash
# List all available GPUs
./satori-kawpowminer --list-devices

# Use specific CUDA devices (0,1,2 are device indices)
./satori-kawpowminer -U --cuda-devices 0,1,2 -P http://user:pass@127.0.0.1:8420

# Mix CUDA and OpenCL devices
./satori-kawpowminer -X --cuda-devices 0,1 --opencl-devices 0 -P http://user:pass@127.0.0.1:8420

# Set different intensity per GPU
./satori-kawpowminer -U --cuda-devices 0,1 --cuda-grid-size 8192,4096 -P http://user:pass@127.0.0.1:8420
```

### Monitoring and Management

#### Enable API for Remote Monitoring
```bash
# Start miner with API enabled on port 3333
./satori-kawpowminer -U --api-bind 3333 -P http://user:pass@127.0.0.1:8420

# Query stats from another terminal or remote machine
echo '{"id":1,"jsonrpc":"2.0","method":"miner_getstat1"}' | nc 127.0.0.1 3333

# Get detailed stats
echo '{"id":1,"jsonrpc":"2.0","method":"miner_getstatdetail"}' | nc 127.0.0.1 3333
```

#### Linux Systemd Service (Auto-start on boot)
Create `/etc/systemd/system/satori-miner.service`:
```ini
[Unit]
Description=Satori KAWPOW Miner
After=network.target

[Service]
Type=simple
User=yourusername
WorkingDirectory=/path/to/satori-kawpowminer
ExecStart=/path/to/satori-kawpowminer/satori-kawpowminer -U -P http://user:pass@127.0.0.1:8420
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
```

Enable and start:
```bash
sudo systemctl enable satori-miner
sudo systemctl start satori-miner
sudo systemctl status satori-miner
```

## Intel GPU Troubleshooting

If your Intel GPU is not detected:

### Linux:
```bash
# Install Intel OpenCL runtime
sudo apt-get install intel-opencl-icd beignet-opencl-icd

# Verify OpenCL installation
clinfo

# Add user to video group (may be required)
sudo usermod -a -G video $USER
# Log out and back in for group change to take effect
```

### Windows:
1. Download Intel Driver & Support Assistant from Intel's website
2. Update to latest Intel Graphics drivers
3. Intel OpenCL runtime is included with modern drivers
4. Use `satori-kawpowminer --list-devices` to verify detection

### Common Issues:
- If Intel GPU not showing: Try `--opencl-platform 1` or `--opencl-platform 2`
- For integrated graphics with dedicated GPU: Disable dedicated GPU in Device Manager to test Intel GPU alone
- Performance tip: Intel GPUs share system RAM, ensure adequate memory allocation in BIOS

ProgPoW can be tuned using the following parameters.  The proposed settings have been tuned for a range of existing, commodity GPUs:

* `PROGPOW_PERIOD`: Number of blocks before changing the random program
* `PROGPOW_LANES`: The number of parallel lanes that coordinate to calculate a single hash instance
* `PROGPOW_REGS`: The register file usage size
* `PROGPOW_DAG_LOADS`: Number of uint32 loads from the DAG per lane
* `PROGPOW_CACHE_BYTES`: The size of the cache
* `PROGPOW_CNT_DAG`: The number of DAG accesses, defined as the outer loop of the algorithm (64 is the same as Ethash)
* `PROGPOW_CNT_CACHE`: The number of cache accesses per loop
* `PROGPOW_CNT_MATH`: The number of math operations per loop

The value of these parameters has been tweaked to use 0.9.4 specs with a PROGPOW_PEROD of 3 to fit the blockchain's blocktimes.  See [this medium post](https://medium.com/@ifdefelse/progpow-progress-da5bb31a651b) for details.

| Parameter             | 0.9.2 | 0.9.3 | 0.9.4 |
|-----------------------|-------|-------|--------|
| `PROGPOW_PERIOD`      | `50`  | `10`  |  `3`   |
| `PROGPOW_LANES`       | `16`  | `16`  |  `16`  |
| `PROGPOW_REGS`        | `32`  | `32`  |  `32`  |
| `PROGPOW_DAG_LOADS`   | `4`   | `4`   |  `4`   |
| `PROGPOW_CACHE_BYTES` | `16x1024` | `16x1024` | `16x1024` |
| `PROGPOW_CNT_DAG`     | `64`  | `64`  | `64`  |
| `PROGPOW_CNT_CACHE`   | `12`  | `11`  | `11`  |
| `PROGPOW_CNT_MATH`    | `20`  | `18`  | `18`  |

Epoch length = 12000 blocks

## Maintainers & Authors

[![Discord](https://img.shields.io/badge/discord-join%20chat-blue.svg)](https://discord.gg/uvyuqWm)

The list of current and past maintainers, authors and contributors to the satori-kawpowminer project.
Ordered alphabetically. [Contributors statistics since 2015-08-20].

| Name                  | Contact                                                      |     |
| --------------------- | ------------------------------------------------------------ | --- |
| Hans Schmidt          | [@hans-schmidt](https://github.com/hans-schmidt)             | --- |
| Jeremy Anderson       | [@Blondfrogs](https://github.com/Blondfrogs)                 | --- |
| Traysi                | [@traysi](https://github.com/traysi)                         | --  |
| Andrea Lanfranchi     | [@AndreaLanfranchi](https://github.com/AndreaLanfranchi)     | ETH: 0xa7e593bde6b5900262cf94e4d75fb040f7ff4727 |
| EoD                   | [@EoD](https://github.com/EoD)                               |     |
| Genoil                | [@Genoil](https://github.com/Genoil)                         |     |
| goobur                | [@goobur](https://github.com/goobur)                         |     |
| Marius van der Wijden | [@MariusVanDerWijden](https://github.com/MariusVanDerWijden) | ETH: 0x57d22b967c9dc64e5577f37edf1514c2d8985099 |
| Paweł Bylica          | [@chfast](https://github.com/chfast)                         | ETH: 0x8FB24C5b5a75887b429d886DBb57fd053D4CF3a2 |
| Philipp Andreas       | [@smurfy](https://github.com/smurfy)                         |     |
| Stefan Oberhumer      | [@StefanOberhumer](https://github.com/StefanOberhumer)       |     |
| ifdefelse             | [@ifdefelse](https://github.com/ifdefelse)                   |     |
| Won-Kyu Park          | [@hackmod](https://github.com/hackmod)                       | ETH: 0x89307cb2fa6b9c571ab0d7408ab191a2fbefae0a |
| Ikmyeong Na           | [@naikmyeong](https://github.com/naikmyeong)                 |     |


## Contribute

All bug reports, pull requests and code reviews are very much welcome.


## License

Licensed under the [GNU General Public License, Version 3](LICENSE).


## F.A.Q

### Satori-Specific Questions

### Q: Why should I mine Satori from day one?
**A:** As a brand new blockchain, Satori offers several advantages:
- **Low DAG Size**: Starting at just 1GB means even 2GB GPUs can mine efficiently
- **Lower Difficulty**: Early network difficulty will be much lower than established chains
- **Fair Launch**: No premine, everyone starts equal
- **Growing DAG**: You have months before the DAG grows beyond 2GB

### Q: How long can my 2GB GPU mine Satori?
**A:** With the DAG starting at 1GB and growing ~8MB per week (every 7,500 blocks):
- 2GB GPUs: Can mine for approximately 3-4 months
- 3GB GPUs: Can mine for approximately 2+ years
- 4GB+ GPUs: Many years of mining ahead

### Q: Which build should I use for my specific GPU?
**A:** Quick reference:
- GTX 660, 670, 680, 690 → CUDA 10.2 build
- GTX 780, Titan → CUDA 11.8 build
- GTX 970, 1060, 1070, 1080 → Standard build (CUDA 12.9.1)
- RTX 2070, 3080, 4090 → CUDA 13.0 build
- Any AMD GPU → OpenCL build

### Q: Direct mining vs Pool mining - which is better for Satori?
**A:**
- **Direct Solo Mining**: Best if you have 50+ MH/s or want to support network decentralization
- **Pool Mining**: Recommended for consistent payouts with lower hashrate
- **Note**: Early in the network, solo mining may be more profitable due to low difficulty

### Q: How do I know if I found a block?
**A:** When solo mining, check your node:
```bash
./satori-cli getmininginfo
# Look for "blocks" count increasing
./satori-cli listtransactions
# Look for "immature" or "generate" transactions
```

## General Mining F.A.Q

### Why is my hashrate with Nvidia cards on Windows 10 so low?

The new WDDM 2.x driver on Windows 10 uses a different way of addressing the GPU. This is good for a lot of things, but not for KAWPOW mining.

* For Kepler GPUs: I actually don't know. Please let me know what works best for good old Kepler.
* For Maxwell 1 GPUs: Unfortunately the issue is a bit more serious on the GTX750Ti, already causing suboptimal performance on Win7 and Linux. Apparently about 4MH/s can still be reached on Linux, which could still be profitable for Satori mining, considering the relatively low power draw.
* For Maxwell 2 GPUs: There is a way of mining at Win7/8/Linux speeds on Win10, by using older drivers. Try driver version 472.12 or older for better performance.
* For Pascal GPUs: You have to use the latest WDDM 2.1 compatible drivers in combination with Windows 10 Anniversary edition in order to get the full potential of your Pascal GPU.

### Why is a GTX 1080 slower than a GTX 1070?

Because of the GDDR5X memory, which can't be fully utilized for KAWPOW mining (yet).

### Are AMD cards also affected by slowdowns with increasing DAG size?

Only GCN 1.0 GPUs (78x0, 79x0, 270, 280), but in a different way. You'll see that on each new epoch (30K blocks), the hashrate will go down a little bit.

### Can I still mine Satori with my 2GB GPU?

**YES!** Since Satori is a NEW blockchain starting with a 1GB DAG, any GPU with 2GB+ VRAM can mine efficiently from day one. This is a unique opportunity as most other KAWPOW chains already have DAGs over 3GB. Your 2GB GPU will work for approximately 3-4 months before the DAG grows too large.

### What are the optimal launch parameters?

The default parameters are fine in most scenario's (CUDA). For OpenCL it varies a bit more. Just play around with the numbers and use powers of 2. GPU's like powers of 2.

### What does the `--cuda-parallel-hash` flag do?

[@davilizh](https://github.com/davilizh) made improvements to the CUDA kernel hashing process and added this flag to allow changing the number of tasks it runs in parallel. These improvements were optimised for GTX 1060 GPUs which saw a large increase in hashrate, GTX 1070 and GTX 1080/Ti GPUs saw some, but less, improvement. The default value is 4 (which does not need to be set with the flag) and in most cases this will provide the best performance.

### What is satori-kawpowminer's relationship with [Genoil's fork]?

[Genoil's fork] was the original source of this version, but as Genoil is no longer consistently maintaining that fork it became almost impossible for developers to get new code merged there. In the interests of progressing development without waiting for reviews this fork should be considered the active one and Genoil's as legacy code.

### Can I CPU Mine?

No.

### CUDA GPU order changes sometimes. What can I do?

There is an environment var `CUDA_DEVICE_ORDER` which tells the Nvidia CUDA driver how to enumerates the graphic cards.
The following values are valid:

* `FASTEST_FIRST` (Default) - causes CUDA to guess which device is fastest using a simple heuristic.
* `PCI_BUS_ID` - orders devices by PCI bus ID in ascending order.

To prevent some unwanted changes in the order of your CUDA devices you **might set the environment variable to `PCI_BUS_ID`**.
This can be done with one of the 2 ways:

* Linux:
    * Adapt the `/etc/environment` file and add a line `CUDA_DEVICE_ORDER=PCI_BUS_ID`
    * Adapt your start script launching satori-kawpowminer and add a line `export CUDA_DEVICE_ORDER=PCI_BUS_ID`

* Windows:
    * Adapt your environment using the control panel (just search `setting environment windows control panel` using your favorite search engine)
    * Adapt your start (.bat) file launching satori-kawpowminer and add a line `set CUDA_DEVICE_ORDER=PCI_BUS_ID` or `setx CUDA_DEVICE_ORDER PCI_BUS_ID`. For more info about `set` see [here](https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/set_1), for more info about `setx` see [here](https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/setx)

### nvrtc64_102_0.dll not found...

```text
Error: The code execution cannot be processed because nvrtc64_102_0.dll was not found.
or
error while loading shared libraries: libnvrtc.so.10.2: cannot open shared object file: No such file or directory
```

You have to upgrade your Nvidia drivers. Install cuda 10.2.


[Amazon S3 is needed]: https://docs.travis-ci.com/user/uploading-artifacts/
[cpp-ethereum]: https://github.com/ethereum/cpp-ethereum
[Contributors statistics since 2015-08-20]: https://github.com/EchelonTechnologyGroup/satori-kawpowminer/graphs/contributors?from=2015-08-20
[Genoil's fork]: https://github.com/Genoil/cpp-ethereum
[Releases]: https://github.com/EchelonTechnologyGroup/satori-kawpowminer/releases
