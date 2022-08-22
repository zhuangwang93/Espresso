# Espresso


Espresso is a genenral framework built upon BytePS to support compression-enabled data-paralle distributed training. 
It is the first work to holistically consider the search space for gradient compression, such as when to compress tensors, what types of compute resources for compression, and how to choose communication primitives after compression.


## Prerequisites

- CUDA == 11.1
- PyTorch == 1.8.0
- NCCL >= 2.8.3

## Installation

```bash
# In case you need to install PyTorch
pip3 install torch==1.8.0+cu111 torchvision==0.9.0+cu111 torchaudio==0.8.0 -f https://download.pytorch.org/whl/torch_stable.html

git clone https://github.com/zhuangwang93/Espresso.git
cd Espresso
git submodule update --init

export BYTEPS_NCCL_LINK=SHARED
python3 setup.py install --user
cd byteps/torch

pip3 install -r requirements.txt
```

## AE file

Follow the instructions in [espresso_EuroSys_AE.pdf](https://github.com/zhuangwang93/Espresso/blob/master/espresso_EuroSys_AE.pdf) to reproduce the experimental results in our paper.


## Examples
The DNN models supported by Espresso are in [examples](https://github.com/zhuangwang93/Espresso/tree/master/byteps/torch/examples). 
There are six DNN models used in the evaluation and each of them has a folder under examples/
Following the instructions in each example to reproduce the experiments results.
