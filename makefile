OBJ= main.o GraphData.o Log.o LogDAO.o GraphDAO.o LogsChecker.o Heure.o
COMP=g++
COMPFLAG = -Wall -std=c++11

analog: $(OBJ)
	$(COMP) $(COMPFLAG) -o analog $(OBJ)
main.o: main.cpp GraphData.h GraphDAO.h Log.h LogDAO.h LogsChecker.h Heure.h
	$(COMP) $(COMPFLAG) -c main.cpp
Heure.o: Heure.h
	$(COMP) $(COMPFLAG) -c Heure.cpp
GraphData.o: GraphData.h GraphData.cpp Log.h LogsChecker.h Heure.h
	$(COMP) $(COMPFLAG) -c GraphData.cpp
Log.o: Log.h Log.cpp GraphData.h
	$(COMP) $(COMPFLAG) -c Log.cpp
LogsChecker.o: LogsChecker.h LogsChecker.cpp Log.h Heure.h
	$(COMP) $(COMPFLAG) -c LogsChecker.cpp
LogDAO.o: LogDAO.h LogDAO.cpp Log.h
	$(COMP) $(COMPFLAG) -c LogDAO.cpp
GraphDAO.o: GraphDAO.h GraphDAO.cpp GraphData.h
	$(COMP) $(COMPFLAG) -c GraphDAO.cpp
clean: 
	rm $(OBJ)
