#include "constantes.h"
#include "geomod.h"
#include "simulation.h"

using namespace std;

int main(int argc, char * argv[]) {
    
	simulation::Simulation s;
    geomod::setterMax(dim_max); 
    
	if(argc != 2) simulation::error(simulation::READ_ARG);
	
	s.lecture(argv[1]);	
	
	return 0;  
}

  
