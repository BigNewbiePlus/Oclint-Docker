FROM ubuntu:14.04
MAINTAINER  BigNewbie "dhfang812@163.com"

ENV LANG=C.UTF-8 LC_ALL=C.UTF-8

ENV BASEDIR /usr/src/app/
ENV OCLINT_HOME $BASEDIR/oclint
ENV OCLINT_SCRIPT $OCLINT_HOME/oclint-scripts

# 添加阿里源，网易源下载特别缓慢
#ADD ./sources.list /etc/apt/

# 安装所需库
RUN apt-get update && apt-get install -yq --no-install-recommends \
    ca-certificates \
    unzip \
    curl \
    #python-dev \
    build-essential \
    gcc \
    subversion \
    git \
    lcov \
    libssl-dev \
    python2.7 \
    #python2.7-minimal \
    ninja-build \
    && apt-get --reinstall install -y python-minimal \
    && apt-get clean && rm -rf /var/lib/apt/lists/*
#RUN easy_install argparse
#RUN python -c "import argparse; print argparse"

# 切换到工作目录
WORKDIR $BASEDIR

RUN git clone https://github.com/oclint/oclint.git

# 切换到OCLINT目录
WORKDIR $OCLINT_HOME

RUN git clone https://github.com/oclint/oclint-json-compilation-database.git

WORKDIR $OCLINT_SCRIPT
RUN ./clang checkout && ./countly checkout && ./googleTest checkout

RUN curl -SLO https://cmake.org/files/v3.10/cmake-3.10.0-Linux-x86_64.tar.gz  && \
    tar zxvf cmake-3.10.0-Linux-x86_64.tar.gz -C /usr && \
    ln -s /usr/cmake-3.10.0-Linux-x86_64/bin/* /usr/bin/ && \
    rm -rf cmake-3.10.0-Linux-x86_64.tar.gz  

RUN ./clang build -release && ./countly build && ./googleTest build && ./test 

# 安装vim环境，便于调试编辑，部署可以删除
RUN apt-get update && apt-get install -y vim-gtk


# 生成库
COPY ./oclint-rules /usr/src/app/oclint/oclint-rules

RUN ./build -release && ./bundle -release

