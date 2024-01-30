FROM ubuntu:20.04

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# install c++ and cmake and others

RUN apt-get update && \
    apt-get install -y g++ cmake git wget libexpat1 libexpat1-dev libgtest-dev valgrind

# load clhep
WORKDIR /root

RUN wget https://proj-clhep.web.cern.ch/proj-clhep/dist1/clhep-2.4.7.1.tgz && tar -xvf clhep-2.4.7.1.tgz
RUN cd 2.4.7.1 && mkdir build && cd build && cmake ../CLHEP && make -j10 && make install

# load geant4
WORKDIR /root

RUN wget https://gitlab.cern.ch/geant4/geant4/-/archive/v10.4.3/geant4-v10.4.3.tar.gz && tar -xvf geant4-v10.4.3.tar.gz
RUN cd geant4-v10.4.3/ && mkdir build && cd build && cmake -DGEANT4_BUILD_CXXSTD=17 -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_SYSTEM_CLHEP=ON .. && make -j10 && make install

# build project 

WORKDIR /root
RUN cd /usr/local/bin && . geant4.sh && cd /root && git clone https://github.com/ZakayZ/FermiBreakUp.git && cd FermiBreakUp && git checkout handler && \
   mkdir build && cd build && cmake ../ && make -j10 # VERBOSE=1

# clean up
WORKDIR /root
RUN rm -r clhep-2.3.4.6.tgz geant4-v10.4.3.tar.gz
