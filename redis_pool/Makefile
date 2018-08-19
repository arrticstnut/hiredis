#----------------------------------------------
#注意：
#头文件要以.h结尾
#源文件要以.cc结尾
#----------------------------------------------

#头文件目录
INC_DIR:= \
	./ \
	./include \

#源文件目录
SRC_DIR:= \
	./ \
	./src/ \

#头文件
INCD:= $(wildcard $(addsuffix *.h,$(INC_DIR)))

#源文件
SRCS:= $(wildcard $(addsuffix *.cc,$(SRC_DIR)))

OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= -lhiredis -ljson

CXX:=g++

CXXFLAGS:= -Wall -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./example.exe


$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)
$(OBJS):$(INCD)

clean:
	#	rm -rf $(EXE)
	rm -rf $(OBJS)
