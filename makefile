
CScript:=g++ -c $< -o $@ -I.
LinkScrpt:=g++ -o $@ $^ -I.

HFiles:=$(wildcard *.h)
CCFiles:=$(wildcard *.cc)
ObjFiles:=$(CCFiles:%.cc=%.o)

shudu:$(ObjFiles)
	$(LinkScrpt)
	
$(CCFiles):%.cc $(HFiles)
	$(CScript)
	

	

