#include <fstream>
#include <sstream>
#include <iostream>

#include <string>

#include "simulation.h"
#include "base.h"
#include "gisement.h"
#include "geomod.h"

using namespace std;


enum All_States{NBG,NBB,FIELD_INFO,BASE_INFO,RESSOURCE,NBP,NBF,NBT,NBC,P_ROBOT, F_ROBOT, T_ROBOT, C_ROBOT};

namespace {
	int state(NBG);
    gisement::Gisement newField;           
    base::Base newBase;
};

void simulation::Simulation::lecture( char * nom_fichier) {
	
    string line;
    ifstream fichier(nom_fichier); 
    
    if(!fichier.fail()) 
    {
        while(getline(fichier >> ws,line)) { 
			  
			// Cleanup----------------------
			size_t u;
			if (line[0] == '#')  continue;
			
			if (line[line.size()-1] == 'r' or line[line.size()-1] == 'n') 
				line.replace(line.size()-2,line.size(),"");
				
			if (line.size()== 0) continue;
				
			for (size_t i(0); i < line.size(); i++) {
				
				if(line[i]=='#') {
					
					u = i;  
			        line.replace(u,line.size(), "");    
			    }
		    }
		    //-------------------------------
		    this->decodage_ligne(line);   
	    }

	}
	else error(READ_OPENING);	
}

void simulation::Simulation::decodage_ligne(string line) {
	
	double x,y;
	base::Base base1;
    geomod::Point p;
    
	switch (state) {
		
		case NBG:
			gisement::caseNbg(line,state);  break;
		
		case NBB:
			base::readNbb(line,state);  break;
	
		case FIELD_INFO:
			newField.caseFields(line,state); break;
		
		case BASE_INFO: 
			newBase = base1.readBase(line,state);
			newBase.getPosition(p);
			p.getPoint(x,y);
			gisement::field_base_overlap(x,y); break;
        
		default: newBase.readRobots(line,state); break;  
		
     }
}

void simulation::Simulation::update_voisin(base::Base b1, base::Base b2) {
	
	base::roboTab tab1;
	base::roboTab tab2;
    base::roboTab link;
	
	geomod::Point position1;
	geomod::Point position2;
	
	bool belongs;
	
	b1.get_roboList(tab1);
	b2.get_roboList(tab2);
	
	for (size_t k(0); k < tab1.size(); ++k) {
		
		for  (size_t p(0); p < tab2.size(); ++p) {
			
			position1 = tab1[k]->get_Position();
			position2 = tab2[p]->get_Position();
			link = tab1[k]->getLink();
		
			if (geomod::point_cercle(position1,position2,rayon_comm)) {
				
				belongs = false;
				
				for (size_t n(0); n < link.size(); ++n) {
				
					if (link[n] == tab2[p])
						belongs = true;
				}		
				if (belongs == true) 
					link.push_back(tab2[p]);
			}
			else {
				for (size_t n(0); n < link.size(); ++n) {
					
					if (link[n] == tab2[p]) {
						swap(link[n],link[link.size()-1]);
						link.pop_back();
					}
				}
			}
		}
	}
}


//For us------------------------------------------------------------------------------------------------------
void simulation::error(Erreur_lecture code) {  
	
	cout <<"ERREUR"<<endl;
	
	switch(code) {
		case READ_OPENING:  cout <<"Erreur d'ouverture du fichier"<<endl; break;
		case READ_ARG:   cout <<"Error ARG"<<endl; break;
	}
    exit(0);
}
//------------------------------------------------------------------------------------------------------------		
