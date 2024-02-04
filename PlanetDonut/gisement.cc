#include <sstream>

#include <string>
#include <vector>

#include "constantes.h"
#include "geomod.h"
#include "message.h"
#include "gisement.h"

enum States{NBB = 1, FIELD_INFO = 2};


using namespace std;

static unsigned int nbG, gi;
static vector <gisement::Gisement> Eg;                           


//Automate de lecture--------------------------------------------
void gisement::caseNbg(string line, int& state) {
    
    istringstream info(line);
    
    if (!(info >> nbG)) error(NB_VAL);
    gi = nbG;
    
    if (nbG >= 1) 
		state = FIELD_INFO;
		
	else state = NBB;
}

void gisement::Gisement::caseFields(string line, int& state) {
     
    istringstream gis(line);
    
    if (!(gis >> x >> y >> rayon >> capacite)) error(READ_FIELD_INFO);
    geomod::normalise(x,y);
    
    this->field_overlap();
    
    if (gi <= 1) {
		
        state = NBB;
        return;
    }
    else {
		
        gi -= 1;
        state = FIELD_INFO;
    }

}



//Vérifications d'erreurs----------------------------------------
void gisement::Gisement::field_overlap() {             
  
   geomod::Point centre(x,y);
    
    for (int i(0); i<Eg.size();i++){
		
        geomod::Point centre1(Eg[i].x,Eg[i].y);
        
        if (geomod::intersection_cercles(centre,centre1,rayon, Eg[i].rayon)){
			
            cout<< message::field_superposition(x,y,Eg[i].x,Eg[i].y);
            exit(0);
        }
    }
    Eg.push_back(*this);
}

void gisement::field_base_overlap(double base_x, double base_y) {

    geomod::Point base_centre(base_x,base_y);
    double gis_rayon, gis_x, gis_y;

    
        for (int i(0); i<Eg.size();i++){
			
            Eg[i].getX(gis_x);
            Eg[i].getY(gis_y);
            Eg[i].getRayon(gis_rayon);
            
            geomod::Point g_centre(gis_x,gis_y);
            
            if (geomod::intersection_cercles(base_centre, g_centre, rayon_base, gis_rayon)){
				
                cout<<message::base_field_superposition(base_x, base_y, gis_x, gis_y);
                exit(0);
            }
    }
}

void gisement::error(Gisement_Errors code) {
	
    switch (code) {
		
        case FIELD_OVERLAP: exit(EXIT_FAILURE);
        case READ_FIELD_INFO:  cout << "4 "<<endl; break;
        case NB_VAL: cout << "5 "<<endl; break;
    }
    exit(0);
}

