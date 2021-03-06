#   Project libJsonX
#   Copyright (C) 2015  tania@df9ry.de
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as
#   published by the Free Software Foundation, either version 3 of the
#   License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#
#   You should have received a copy of the GNU Affero General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
ifeq (,$(filter _%,$(notdir $(CURDIR))))
include target.mk
else
#----- End Boilerplate

VPATH = $(SRCDIR)

CXXFLAGS =	-std=c++11 -pedantic -Wall -g -shared -fPIC \
			-fmessage-length=0 -fexceptions -pthread \
			-I$(SRCDIR)/../libJsonX \
			-I$(SRCDIR)/../libStringUtil
			

LDXFLAGS =	-std=c++11 -pedantic -Wall -g -shared -fPIC \
			-fmessage-length=0 -fexceptions -pthread \
			-L../../libJsonX/_$(_CONF) \
			-L../../libStringUtil/_$(_CONF)

OBJS     =  Channel.o \
			ChannelProxy.o \
			Configuration.o \
			Environment.o \
			LoadableObject.o \
			Logger.o \
			Plugin.o \
			Timer.o \
			TimerManager.o \
			UUID.o
			
LIBS     =  -lJsonX -lStringUtil -lpthread -luuid -ldl

TARGET   =	libFreeAX25Runtime.so

$(TARGET):	$(OBJS)
	$(CXX) $(LDXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<	
	
all: $(TARGET)
	cp ../../libB64/_$(_CONF)/libB64.so .
	cp ../../libJsonX/_$(_CONF)/libJsonX.so .
	cp ../../libStringUtil/_$(_CONF)/libStringUtil.so .
	echo "Build OK"
	
doc: $(DOCDIR)
	doxygen ../doxygen.conf
	( cd ../_doc/latex && make )
	
install:
	sudo cp libFreeAX25Runtime.so /usr/local/lib/libFreeAX25Runtime.so.0.1.0
	( cd /usr/local/lib && sudo chown root:staff libFreeAX25Runtime.so.0.1.0               )
	( cd /usr/local/lib && sudo chmod 0755       libFreeAX25Runtime.so.0.1.0               )
	( cd /usr/local/lib && sudo ln -sf libFreeAX25Runtime.so.0.1.0 libFreeAX25Runtime.so.0 )
	( cd /usr/local/lib && sudo ln -sf libFreeAX25Runtime.so.0.1.0 libFreeAX25Runtime.so   )
	
#----- Begin Boilerplate
endif
