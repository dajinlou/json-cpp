# 先创建build目录
if [ ! -d "./buildtest" ];then
    mkdir buildtest
fi
cd ./build
rm * -rf &&
cmake .. &&
make -j4
