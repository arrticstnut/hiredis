INC_DIR:= \
	./
#SRC_DIR:= 
#	./src/ \
#	./src/task/ \
#	./src/tcpSer/ \
#	./src/threadPool/ \
#	./src/cacle/ \
#	./src/timer/ \
#	./src/cppjieba/ \
#	./src/configuration/ \

SRCS:=\
	$(wildcard ./*.cc) \

OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= -lhiredis -ljson

CXX:=g++

CXXFLAGS:= -Wall -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./test.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
#	rm -rf $(EXE)
	rm -rf $(OBJS)

