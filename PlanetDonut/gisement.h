#include <iostream>

#ifndef GISEMENT_H
#define GISEMENT_H

namespace gisement{
	
    enum Gisement_Errors{READ_FIELD_INFO,NB_VAL,FIELD_OVERLAP};

    void error(Gisement_Errors);

    class Gisement{
        
    public:
        Gisement(double xl, double yl, double ray,double cap) {x=xl; y=yl; rayon=ray; capacite=cap;}    
        Gisement() {};
        
        //Lecture de gisement
        void caseFields(std::string line, int& state);
        
        //Vérifi la superposition des gisments
        void field_overlap();     
        
        void getRayon(double& r) {r = rayon;}
        
        void getX(double& X) {X=x;}
        
        void getY(double& Y) {Y=y;}                                  

    private:
        double x, y,rayon, capacite;
    };
    
    //Lecture du nombre de gisements
    void caseNbg(std::string line, int& state);
 
	//Vérifie la superpostion gisement-base
    void field_base_overlap(double base_x, double base_y); 

}
#endif
