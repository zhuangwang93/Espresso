export BYTEPS_NCCL_LINK=SHARED
python3 setup.py install --user
cd byteps/torch 
pip3 install -r requirements.txt

pip3 install nvidia-pyindex
pip3 install nvidia-dllogger 

git clone https://github.com/NVIDIA/apex
cd apex
git checkout d6b5ae5d04f531ff862f651e67f241fef88fd159
pip install -v --disable-pip-version-check --no-cache-dir --global-option="--cpp_ext" --global-option="--cuda_ext" ./
cd ..

sudo apt-get update && sudo apt-get install libgl1 -y
pip3 install opencv-python
sudo apt install unzip

echo "download dataset for LSTM"
mkdir ~/data
cd examples/lstm
bash getdata.sh

echo "download model checkpoint for BERT-base"
cd ../BERT
cd ./dataset/checkpoint
wget --content-disposition https://api.ngc.nvidia.com/v2/models/nvidia/bert_pyt_ckpt_base_qa_squad11_amp/versions/19.09.0/zip -O bert_pyt_ckpt_base_qa_squad11_amp_19.09.0.zip
unzip bert_pyt_ckpt_base_qa_squad11_amp_19.09.0.zip
cd ../../ && mkdir -p results


echo "download dataset for GPT-2"
cd ~/data
wget https://s3.amazonaws.com/research.metamind.io/wikitext/wikitext-2-raw-v1.zip
unzip wikitext-2-raw-v1.zip


echo "download dataset for VGG16 and ResNet101"
cd ~/data
wget https://s3.amazonaws.com/fast-ai-imageclas/imagewang.tgz
tar xf imagewang.tgz


echo "download dataset for UGATIT"
cd ~/data 
gdown 1xOWj1UVgp6NKMT3HbPhBbtq2A4EDkghF
mkdir selfie2anime && unzip selfie2anime.zip -d selfie2anime