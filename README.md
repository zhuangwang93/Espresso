# Reproduce Espresso Experiments

This repository contains the system code and scripts that help run the Espresso experiments from our EuroSys '23 paper.

## Prerequisites

- CUDA == 11.1
- PyTorch == 1.8.0
- NCCL >= 2.8.3

## What machines?

All of our experiments require multiple GPU machines.
We expect each GPU machine has eight V100 GPUs and the GPU memory is 32GB.
NVLink-based (100Gbps TCP) and PCIe-only (25Gbps TCP) GPU machines are needed for Figure 11 and Figure 12. 
If resources are not available, it is fine to perform experiments with 4 GPU machines and use 25Gbps TCP for NVLink-based experiments. 
It is also fine to perform PCIe-only experiments on NVLink-based machines with export NCCL_P2P_DISABLE=1


## Installation

Install Espresso on each GPU machine.

```bash
# In case you need to install PyTorch
pip3 install torch==1.8.0+cu111 torchvision==0.9.0+cu111 torchaudio==0.8.0 -f https://download.pytorch.org/whl/torch_stable.html

git clone https://github.com/zhuangwang93/Espresso.git --recursive
cd Espresso

# install dependencies and datasets for training
bash install.sh
```

## AE file

Follow the instructions in [espresso_EuroSys_AE.pdf](https://github.com/zhuangwang93/Espresso/blob/master/espresso_EuroSys_AE.pdf) to reproduce the experimental results in our paper.


## End-to-end training throughput

The DNN models used by Espresso are in [examples](https://github.com/zhuangwang93/Espresso/tree/master/byteps/torch/examples). 
There are six DNN models and each of them has a folder under examples/

Follow the instructions in each example to reproduce the experiments results in Figure 11 and Figure 12.


## Compression strategy selection time

Follow the instruction in [scheduler](https://github.com/zhuangwang93/Espresso/tree/master/byteps/torch/mergeComp/scheduler) to reproduce the experiments results in Table 4 and Table 5.
