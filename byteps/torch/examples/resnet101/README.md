# ResNet101


## Download the dataset
```bash
cd ~/data
# we use a small dataset from ImageNet
wget https://s3.amazonaws.com/fast-ai-imageclas/imagewang.tgz
tar xf imagewang.tgz
```
The default location of the dataset is ~/data, and the dataset for VGG16 and ResNet101 is in ~/data/imagewang

## How to run
**Note**: Make sure the dataset is in the right location. Set DMLC_PS_ROOT_URI and ifname in run_espresso.sh and run_baseline.sh.
Make sure it runs on PCIe-only GPU machines.

DMLC_PS_ROOT_URI: the IP address of the root GPU machine

ifname: the network interface card name, e.g., eth0, eth2


### Espresso
Run on each machine
```bash
bash run_espresso.sh WORKERS ID
```
WORKERS is the number of machines in the training

ID is the id of a machine. machines have distinct IDs

**An example**:
Suppose there are four GPU machines, then WORKERS=4 and ID is from 0-3. 
The ID of the root GPU machine is 0.
The command on each GPU machine is
```bash
bash run_espresso.sh 4 ID
```


### Baselines
Run on each machine
```bash
bash run_baseline.sh WORKERS ID
``` 

**An example**:
Suppose there are four GPU machines, then WORKERS=4 and ID is from 0-3. 
The ID of the root GPU machine is 0.
The command on each GPU machine is
```bash
bash run_baseline.sh 4 ID
```
