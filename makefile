#file: Makefile
#
# test program for CMS RPC
#
# 14/01/14  Created by Y.Benhammou


DAQ_HOME_DIR = /home/gifdaq/Desktop/daq20120525
DAQ_BIN_DIR = $(DAQ_HOME_DIR)/bin
DAQ_INC_DIR = $(DAQ_HOME_DIR)/include
DAQ_SRC_DIR = $(DAQ_HOME_DIR)/src
DAQ_OBJ_DIR = $(DAQ_HOME_DIR)/obj


# ROOT_INC = /cern/root/include
ROOT_INC  = $(ROOTSYS)/include
#ROOT_INC = /var/software/root/include
ROOTLIBS     := $(shell root-config --libs)

LFLAGS     = -L$(DAQ_HOME_DIR)/lib -L/usr/lib \
             $(ROOTLIBS) 
             
	 
CFLAGS     = -ggdb -fPIC -DLINUX -Wall -funsigned-char \
             -I$(DAQ_INC_DIR) -I$(ROOT_INC)


all: daq

daq: 	v1718.o v1190a.o daq.o
	g++ $(CFLAGS) $(DAQ_OBJ_DIR)/v1718.o \
	$(DAQ_OBJ_DIR)/daq.o \
	$(DAQ_OBJ_DIR)/v1190a.o \
        -o $(DAQ_BIN_DIR)/daq \
        $(LFLAGS)  \
        -l CAENVME -l curses 

daqV: 	v1718.o v2718.o v1190a.o v1290a.o v1290n.o tmc.o v792.o v560.o v262.o parameter.o PracticalSocket.o daqV.o
	g++ $(CFLAGS) $(DAQ_OBJ_DIR)/v1718.o \
	$(DAQ_OBJ_DIR)/v2718.o \
	$(DAQ_OBJ_DIR)/daqV.o \
	$(DAQ_OBJ_DIR)/v1190a.o \
	$(DAQ_OBJ_DIR)/v1290a.o \
	$(DAQ_OBJ_DIR)/v1290n.o \
	$(DAQ_OBJ_DIR)/v792.o \
	$(DAQ_OBJ_DIR)/tmc.o \
	$(DAQ_OBJ_DIR)/v560.o \
	$(DAQ_OBJ_DIR)/v262.o \
	$(DAQ_OBJ_DIR)/parameter.o \
	$(DAQ_OBJ_DIR)/PracticalSocket.o\
        -o $(DAQ_BIN_DIR)/daqV \
        $(LFLAGS)  \
        -l CAENVME -l curses 

daqRoot: 	v1718.o v2718.o v1190a.o v1290a.o v1290n.o tmc.o v792.o v560.o v262.o parameter.o PracticalSocket.o daqRoot.o
	g++ $(CFLAGS) $(DAQ_OBJ_DIR)/v1718.o \
	$(DAQ_OBJ_DIR)/v2718.o \
	$(DAQ_OBJ_DIR)/daqRoot.o \
	$(DAQ_OBJ_DIR)/v1190a.o \
	$(DAQ_OBJ_DIR)/v1290a.o \
	$(DAQ_OBJ_DIR)/v1290n.o \
	$(DAQ_OBJ_DIR)/v792.o \
	$(DAQ_OBJ_DIR)/tmc.o \
	$(DAQ_OBJ_DIR)/v560.o \
	$(DAQ_OBJ_DIR)/v262.o \
	$(DAQ_OBJ_DIR)/parameter.o \
	$(DAQ_OBJ_DIR)/PracticalSocket.o\
        -o $(DAQ_BIN_DIR)/daqRoot \
        $(LFLAGS)  \
        -l CAENVME -l curses 

daqDemo: 	parameter.o daqDemo.o
	g++ $(CFLAGS) $(DAQ_OBJ_DIR)/daqDemo.o \
	$(DAQ_OBJ_DIR)/parameter.o \
        -o $(DAQ_BIN_DIR)/daqDemo \
        $(LFLAGS)

tdcdaq:	parameter.o vmefun.o vme.o v767.o v560.o tdcdaq.o 
	g++ $(CFLAGS) $(DAQ_OBJ_DIR)/parameter.o $(DAQ_OBJ_DIR)/vmefun.o $(DAQ_OBJ_DIR)/vme.o \
	$(DAQ_OBJ_DIR)/v560.o $(DAQ_OBJ_DIR)/tdcdaq.o\
	$(DAQ_OBJ_DIR)/v767.o\
        -o $(DAQ_BIN_DIR)/daq \
        $(LFLAGS) `/home/atlas2/cern/pro/bin/cernlib` \
        -I/home/atlas2/cern/pro/lib -lg2c $(ROOTLIBS)

clean:
	-rm $(DAQ_BIN_DIR)/daq
	-rm $(DAQ_OBJ_DIR)/*.o

remove:
	-rm $(DAQ_BIN_DIR)/daq
	-rm $(DAQ_OBJ_DIR)/*.o


daq.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/daq.cxx -o $(DAQ_OBJ_DIR)/daq.o

daqV.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/daqV.cxx -o $(DAQ_OBJ_DIR)/daqV.o

daqRoot.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/daqRoot.cxx -o $(DAQ_OBJ_DIR)/daqRoot.o

daqDemo.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/daqDemo.cxx -o $(DAQ_OBJ_DIR)/daqDemo.o

tdcdaq.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/tdcdaq.cxx -o $(DAQ_OBJ_DIR)/tdcdaq.o


vme.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/vme.cxx -o $(DAQ_OBJ_DIR)/vme.o

vmefun.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/vmefun.cxx -o $(DAQ_OBJ_DIR)/vmefun.o

parameter.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/parameter.cxx -o $(DAQ_OBJ_DIR)/parameter.o

v560.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v560.cxx -o $(DAQ_OBJ_DIR)/v560.o


v1718.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v1718.cxx -o $(DAQ_OBJ_DIR)/v1718.o

v2718.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v2718.cxx -o $(DAQ_OBJ_DIR)/v2718.o

v767.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v767.cxx -o $(DAQ_OBJ_DIR)/v767.o

v792.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v792.cxx -o $(DAQ_OBJ_DIR)/v792.o

v262.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v262.cxx -o $(DAQ_OBJ_DIR)/v262.o

tmc.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/tmc.cxx -o $(DAQ_OBJ_DIR)/tmc.o
v1190a.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v1190a.cxx -o $(DAQ_OBJ_DIR)/v1190a.o
v1290a.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v1290a.cxx -o $(DAQ_OBJ_DIR)/v1290a.o
v1290n.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v1290n.cxx -o $(DAQ_OBJ_DIR)/v1290n.o
v551.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/v551.cxx -o $(DAQ_OBJ_DIR)/v551.o

clear_v550.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/clear_v550.cxx -o $(DAQ_OBJ_DIR)/clear_v550.o


PracticalSocket.o:
	g++ -c $(CFLAGS) $(DAQ_SRC_DIR)/PracticalSocket.cxx -o $(DAQ_OBJ_DIR)/PracticalSocket.o
