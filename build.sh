# 先创建build目录
if [ ! -d "./build" ];then
    mkdir build
fi
cd ./build
rm * -rf &&
cmake .. &&
make -j4
