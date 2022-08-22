# GPT-2

You can run the model step by step as follows. 
The dataset and the dependencies are all set after "bash install.sh". 
Go to "How to run" directly.

## Download the dataset
```bash
mkdir ~/data
cd ~/data
wget https://s3.amazonaws.com/research.metamind.io/wikitext/wikitext-2-raw-v1.zip
unzip wikitext-2-raw-v1.zip
```
**Note**: the default location of the dataset is ~/data, and the dataset for GPT2 is in ~/data/wikitext-2-raw


## Install dependencies
```bash
bash run_prepare.sh
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