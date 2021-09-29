FROM ubuntu:18.04 AS ubuntu
LABEL author="apple"
# 用ubuntu国内源替换默认源
RUN rm /etc/apt/sources.list
COPY sources.list /etc/apt/sources.list
RUN apt update
RUN apt-get update
RUN apt install -y build-essential
RUN apt install -y gcc-multilib
RUN apt install -y clang
RUN apt install -y qemu
RUN apt install -y qemu-system
RUN apt install -y qemu-user
RUN apt install -y flex
RUN apt install -y bison
RUN apt-get install -y gcc-arm-linux-gnueabihf
#print()时在控制台正常显示中文
ENV PYTHONIOENCODING=utf-8