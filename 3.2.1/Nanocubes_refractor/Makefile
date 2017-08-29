CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Nanocubes_refractor.o

LIBS =

TARGET =	Nanocubes_refractor.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
