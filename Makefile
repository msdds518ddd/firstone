###########################################  
#Makefile for simple programs  
########################################### 
SYSPATH=/home/ddd/yema-b62-gc_n331/firmware/rootfs
CROSS_COMPILE=$(SYSPATH)/output/host/usr/bin/arm-linux-gnueabihf-
ROOTFS=$(SYSPATH)/output/staging
outpath = /mnt/hgfs/ubuntu_share/download
userfile =


TARGET = main
OBJS = \
	main.o


CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
INC = \
	-I$(ROOTFS)/usr/include

FLAGS = -DLINUX -DEGL_API_FB -fPIC -O3 -fno-strict-aliasing -fno-optimize-sibling-calls -g -O2 -fPIC -Wall -W -Wno-unused-parameter
CFLAGS += $(INC) $(FLAGS)
CXXFLAGS += $(INC) -fpermissive $(FLAGS)
LIBS = -lstdc++ -lm -lGLESv2 -lEGL -ldl -lg2d -pthread -lpng -ljpeg -lfreetype -lassimp
LIBS += -L./ -lxtdcore
LDFLAGS = $(LIBS)

$(TARGET): $(OBJS)  
	$(CC) $(LDFLAGS) $(OBJS) $(userfile) -o $(TARGET)
	cp $(TARGET) $(outpath) 

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

.PRONY:clean  
clean:  
	@echo "Removing linked and compiled files......"  
	rm -f *.d *.o *~ $(OBJS) $(TARGET) $(LIBTARGET)
