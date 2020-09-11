FROM centos:7

RUN mkdir /workspace
WORKDIR /workspace

RUN yum --enablerepo=extras --assumeyes install centos-release-scl
RUN yum update --assumeyes && yum install --assumeyes \
    make \
    gcc \
    CUnit-devel \
    doxygen \
    graphviz \
    valgrind \
    rpm-build
