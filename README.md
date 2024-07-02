# 聊天项目

本项目是学习B站大佬[恋恋风辰zack](https://space.bilibili.com/271469206)的全栈聊天项目，感谢UP主的无私奉献，大家喜欢的可以去他的主页多多点赞！

他的代码：https://gitee.com/secondtonone1/llfcchat

grpc命令：

```shell
protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=$MY_INSTALL_DIR/grpc/bin/grpc_cpp_plugin message.proto
protoc -I . --cpp_out=. message.proto
```
