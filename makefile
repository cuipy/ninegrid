
HFiles:=$(wildcard *.h)
CCFiles:=$(wildcard *.cc)
ObjFiles:=$(CCFiles:%.cc=%.o)

shudu:$(ObjFiles)
	g++ -o $@ $^ 
	
$(ObjFiles):%.o:%.cc $(HFiles)
	g++ -Wall -O3 -D_REENTRANT -c $< -o $@
	
.PHONY:clean
clean:
	rm -f shudu $(ObjFiles)
	

