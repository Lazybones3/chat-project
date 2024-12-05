ArchLinux下安装开发环境：man

```shell
sudo pacman -S clang boost jsoncpp hiredis grpc
```

安装MySQL Connector/C++，打开[下载地址](https://downloads.mysql.com/archives/c-cpp/)，操作系统选择Linux-Generic

```shell
cd third_party
wget https://downloads.mysql.com/archives/get/p/20/file/mysql-connector-c%2B%2B-9.0.0-linux-glibc2.28-x86-64bit.tar.gz
tar -zxvf mysql-connector-c++-9.0.0-linux-glibc2.28-x86-64bit.tar.gz
mv mysql-connector-c++-9.0.0-linux-glibc2.28-x86-64bit mysql-concpp
```