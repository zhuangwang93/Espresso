# LSTM

You can run the model step by step as follows. 
The dataset and the dependencies are all set after "bash install.sh". 
Go to "How to run" directly.


## Download the dataset
```bash
bash getdata.sh 
```
The default location of the dataset is ~/data, and the dataset for LSTM is in ~/data/wikitext-2


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