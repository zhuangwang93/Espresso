#!/bin/bash

# set DMLC_PS_ROOT_URI with the IP address of the root GPU machine and ifname with the NIC name
ifname="eth0"
export DMLC_PS_ROOT_URI="10.188.181.156"
export DMLC_NUM_WORKER=$1
export DMLC_WORKER_ID=$2

# VGG16
cd vgg16/
bash run_baseline.sh ${ifname} | tee -a ../vgg16_log
bash run_espresso.sh ${ifname} | tee -a ../vgg16_log

# LSTM
cd ../lstm/
bash run_baseline.sh ${ifname} | tee -a ../lstm_log
bash run_espresso.sh ${ifname} | tee -a ../lstm_log


# ResNet101
cd ../resnet101/
bash run_baseline.sh ${ifname} | tee -a ../resnet101_log
bash run_espresso.sh ${ifname} | tee -a ../resnet101_log