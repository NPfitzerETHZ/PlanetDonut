# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc simulation.cc base.cc robot.cc gisement.cc geomod.cc message.cc gui.cc graphic.cc
OFILES = projet.o simulation.o base.o robot.o gisement.o geomod.o message.o gui.o graphic.o

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet




