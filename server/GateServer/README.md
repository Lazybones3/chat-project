ArchLinux下安装开发环境：

```shell
sudo pacman -S clang boost jsoncpp hiredis grpc
```

grpc命令：

```shell
# 生成grpc的头文件和源文件
protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin message.proto
# 生成用于序列化和反序列化的pb文件
protoc -I . --cpp_out=. message.proto
```

安装MySQL Connector/C++，打开[Connector/C++下载地址](https://dev.mysql.com/downloads/connector/cpp/)，操作系统选择Linux-Generic

```shell
cd third_party
wget https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-9.1.0-linux-glibc2.28-x86-64bit.tar.gz
tar -zxvf mysql-connector-c++-9.1.0-linux-glibc2.28-x86-64bit.tar.gz
mv mysql-connector-c++-9.1.0-linux-glibc2.28-x86-64bit mysql-concpp
```
