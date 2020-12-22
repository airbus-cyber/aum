FROM ubuntu:18.04

RUN mkdir /workspace
WORKDIR /workspace

RUN apt-get update && apt-get install -y \
    make \
    pkg-config \
    doxygen \
    graphviz \
    valgrind
