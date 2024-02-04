#ifndef BASE_H
#define BASE_H

#include "geomod.h"    
#include "constantes.h"
#include "robot.h"

namespace base {
	
	typedef std::vector<robot::Robot*> roboTab;
	
	enum Base_Errors {NB_VAL,READ_BASE_INFO};
	
	class Base {
        
	public:
	    Base(geomod::Point p1, double ress, int p, int f, int t, int c); 
        Base(); 
        ~Base();
 
		//Lecture des bases
        Base readBase(std::string line, int& state);
        
        //Délègue la lecture des robots au module robot
        void readRobots(std::string line, int& state);
	    
	    //Mise à jours de l'état de lecture
	    void laterState(int& state);
	    
	    //Vérifie que chaque robot de la base à un uid unique
	    void unique_id(unsigned int uid);
	    
	    //Vérifie la superposition des bases
	    bool base_overlap(); 
	    
	    void addRobot(robot::Robot* r); 
	    
	    void getPosition(geomod::Point& p1) {p1 = position;}
	    
	    void getRobots(int& p, int& f, int& t, int& c) {p = nbP; f = nbF; t = nbT; c = nbC;};
	    
	    void get_roboList(roboTab& tab) {tab = roboList;}
        
	private:
	    geomod::Point position;   
	    double ressource;  
	    
	    int nbP;
	    int nbF;
	    int nbT;
	    int nbC; 
	    
	    //Collection hétérogène 
	    roboTab roboList;      
    };
    
    //Lecture du nombre de bases
    void readNbb(std::string line, int& state);
 
    void error(Base_Errors code);
    
    void ending(bool end);
}
#endif

