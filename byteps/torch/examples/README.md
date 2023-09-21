# End-to-end training throughput

## How to run

`run_nvlink_models.sh` and `run_pcie_models.sh` are two scripts to run the experiments for E1 (NVLink-based experiments) and E2 (PCIe-only experiments)

Set ifname and DMLC_PS_ROOT_URI in the two scripts.

ifname: the network interface card name, e.g., eth0, eth2

DMLC_PS_ROOT_URI: the IP address of the root machine. Any machine involved in training can serve as the root machine and its ID is 0.

For E1, run the command on each NVLink-based GPU machines 
```bash
bash run_nvlink_models.sh WORKERS ID
```

For E2, run the command on each PCIe-only GPU machines
```bash
bash run_pcie_models.sh WORKERS ID
```

WORKERS: the number of GPU machines in the training

ID: the id of a machine. machines have distinct IDs that start from 0 to WORKERS-1

## Results

The results of model training throughput with different systems are logged in model_log. 
The metrics are `images/sec` or `tokens/sec`.
Check the logs after the completion of training.


## For trace of time gaps

Add the following environment variables in Shell scripts

```bash
export BYTEPS_TRACE_ON=1
export BYTEPS_TRACE_START_STEP=10
export BYTEPS_TRACE_END_STEP=20
export BYTEPS_TRACE_DIR=trace
```

Make sure there is a folder named `trace/0/` and then run the training without applying compression algorithms. Extract the time gaps with `byteps/torch/examples/json_parser.py` and remember to change the input file in json_parse.py.
