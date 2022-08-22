# BERT
We fine-tune a pretrained BERT model on [SQuAD v1.1](https://rajpurkar.github.io/SQuAD-explorer/) dataset. Our script is based on [this nvidia repo](https://github.com/NVIDIA/DeepLearningExamples/tree/master/PyTorch/LanguageModeling/BERT). 
The dataset is already in the dataset folder. 
The checkpoint needs to be placed in `./dataset/checkpoint`, which can be downloaded from [NGC](https://ngc.nvidia.com/catalog/models/nvidia:bert_pyt_ckpt_large_qa_squad11_amp/files).

You can run the model step by step as follows. 
The dataset and the dependencies are all set after "bash install.sh". 
Go to "How to run" directly.

## Install Dependencies
```bash
pip3 install nvidia-pyindex
pip3 install nvidia-dllogger 

git clone https://github.com/NVIDIA/apex
cd apex
git checkout d6b5ae5d04f531ff862f651e67f241fef88fd159
pip install -v --disable-pip-version-check --no-cache-dir --global-option="--cpp_ext" --global-option="--cuda_ext" ./
```
**Note**: comment out the version check in apex setup.py if the CUDA version and PyTorch is incompatible

## Dowload model checkpoint
```bash
cd ./dataset/checkpoint
wget --content-disposition https://api.ngc.nvidia.com/v2/models/nvidia/bert_pyt_ckpt_base_qa_squad11_amp/versions/19.09.0/zip -O bert_pyt_ckpt_base_qa_squad11_amp_19.09.0.zip
sudo apt install unzip
unzip bert_pyt_ckpt_base_qa_squad11_amp_19.09.0.zip
cd ../../ && mkdir -p results
```

## How to run
**Note**: Make sure it runs on NVLink-based GPU machines.
Set ifname in run_espresso.sh and run_baseline.sh.

ifname: the network interface card name, e.g., eth0, eth2

```bash
export DMLC_PS_ROOT_URI="ip"
export DMLC_NUM_WORKER=WORKERS
export DMLC_WORKER_ID=WORKER_ID
```

DMLC_PS_ROOT_URI: the IP address of the root GPU machine

WORKERS: the number of GPU machines in the training

ID: the id of a machine. machines have distinct IDs that start from 0


### Espresso
Run on each machine
```bash
bash run_espresso.sh
```

### Baselines
Run on each machine
```bash
bash run_baseline.sh
``` 