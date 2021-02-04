FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install -y git build-essential cmake clang libssl-dev wget \
    g++ python-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev \
    libwebsocketpp-dev \
    libx11-dev libglu1-mesa-dev mesa-common-dev freeglut3-dev
    #c++
    #websocketpp
    #websocketpp
    #physx build用
#cmakeの準備  
RUN apt remove cmake -y
RUN wget https://cmake.org/files/v3.18/cmake-3.18.4-Linux-x86_64.sh
RUN chmod +x cmake-3.18.4-Linux-x86_64.sh
RUN yes y| ./cmake-3.18.4-Linux-x86_64.sh
RUN mv cmake-3.18.4-Linux-x86_64 /opt
RUN ln -s /opt/cmake-3.18.4-Linux-x86_64/bin/* /usr/bin

#wineの準備
RUN apt-get update && apt-get install -y wine-stable
RUN dpkg --add-architecture i386 && apt-get update && apt-get install -y wine32

RUN apt-get update && apt-get upgrade -y

#boostの準備
RUN wget -O boost_1_74_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.74.0/boost_1_74_0.tar.gz/download
RUN tar xzvf boost_1_74_0.tar.gz
RUN cd boost_1_74_0 && ./bootstrap.sh --prefix=/usr/local/bin
RUN cd boost_1_74_0 && ./b2
RUN cd boost_1_74_0 && ./b2 install