# UGATIT

Our script is based on [Official PyTorch Implementation of UGATIT](https://github.com/znxlwm/UGATIT-pytorch) and you can find the dataset [here](https://drive.google.com/file/d/1xOWj1UVgp6NKMT3HbPhBbtq2A4EDkghF/view).


You can run the model step by step as follows. 
The dataset and the dependencies are all set after "bash install.sh". 
Go to "How to run" directly.

## Download the dataset

```bash
cd ~/data
gdown 1xOWj1UVgp6NKMT3HbPhBbtq2A4EDkghF
mkdir selfie2anime && unzip selfie2anime.zip -d selfie2anime
```
The default location of the dataset is ~/data, and the dataset for UGATIT is in ~/data/selfie2anime


## Install dependencies
```bash
sudo apt-get update && sudo apt-get install libgl1 -y
pip3 install opencv-python
```

## How to run
**Note**: Make sure the dataset is in the right location and it runs on NVLink-based GPU machines.
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