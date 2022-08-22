#!/bin/bash

# set DMLC_PS_ROOT_URI with the IP address of the root GPU machine and ifname with the NIC name
ifname="eth0"
export DMLC_PS_ROOT_URI="10.188.181.156"
export DMLC_NUM_WORKER=$1
export DMLC_WORKER_ID=$2

# BERT-base
cd BERT/
bash run_baseline.sh ${ifname} | tee -a ../bert_log
bash run_espresso.sh ${ifname} | tee -a ../bert_log

# GPT-2
cd ../gpt-2/
bash run_prepare.sh
bash run_baseline.sh ${ifname} | tee -a ../gpt2_log
bash run_espresso.sh ${ifname} | tee -a ../gpt2_log


# UGATIT
cd ../ugatit/
bash run_baseline.sh ${ifname} | tee -a ../ugatit_log
bash run_espresso.sh ${ifname} | tee -a ../ugatit_log