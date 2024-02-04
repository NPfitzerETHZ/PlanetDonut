#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include "base.h"

namespace simulation {
	
	enum Erreur_lecture {READ_OPENING,READ_ARG};
	
	class Simulation {	
    public:
		
	    void lecture(char * nom_fichier);
	    
	    void decodage_ligne(std::string line); 
	    
	    void update_voisin(base::Base b1, base::Base b2);
	};
	
	void error(Erreur_lecture code);
}    
#endif

