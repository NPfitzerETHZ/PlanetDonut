#include <iostream>
#include <sstream>
#include "base.h"
#include "geomod.h"
#include "gisement.h"
#include "message.h"

enum State{NBB = 1, BASE_INFO = 3,P_ROBOT = 9, F_ROBOT = 10, T_ROBOT = 11, C_ROBOT = 12};

using namespace std;

static unsigned int nbB, b1;
static vector<base::Base> base_tab;

//Automate de lecture -------------------------------------------------------------------------
void base::readNbb(string line, int& state) {

    istringstream info(line);
	if (!(info >> nbB))  error(NB_VAL);
	b1 = nbB;
	state = BASE_INFO; 
}

base::Base base::Base::readBase(string line, int& state) {
	
	double x, y;
	istringstream info(line);

	if (!(info >> x >> y >> ressource >> nbP>> nbF >> nbT >> nbC))  
		error(READ_BASE_INFO);
		
	laterState(state);
	
	if (nbC == 0) {
		
		cout<<message::missing_robot_communication(x,y);
		exit(0);
	}
	
	robot::setPFTCB(nbP,nbF,nbT,nbC,b1); 
	b1 -= 1;	
	 
	position.setPoint(x,y);
	position.normalise();
   
	if(this->base_overlap()) 
		exit(0);
		
	else {
		
        base_tab.push_back(*this);
        return *this;      
	}	
	
}
	
void base::Base::readRobots(string line, int& state) {     
   
    unsigned int uid;
    
	switch (state) {
		
		case P_ROBOT: {
			robot::Prospection* rp(new robot::Prospection);
			rp->casePR(line,state,uid);
			this->unique_id(uid);
			this->addRobot(rp);       break;
		}
		
		case F_ROBOT: {
			robot::Forage* rf (new robot::Forage);
			rf->caseFR(line,state,uid);
			this->unique_id(uid); 
			this->addRobot(rf);       break;
		}
		
		case T_ROBOT: {
			robot::Transport* rt (new robot::Transport);
			rt->caseTR(line,state,uid);
			this->unique_id(uid); 
			this->addRobot(rt);       break;
		}
		
		case C_ROBOT: {
			bool end;
			robot::Communication* rc (new robot::Communication);
			end = rc->caseCR(line,state,uid,this->position);
			this->unique_id(uid);	
			this->addRobot(rc); 
			ending(end);	          break;
		}	
			
		default: exit(0);
    }
}
	
void base::Base::laterState(int& state) {
    
    if (nbP == 0) {
		
        state = F_ROBOT;
        
        if (nbF == 0) {
			
            state = T_ROBOT;
            
            if (nbT == 0) 
                state = C_ROBOT;       
        }  
    }
    else state = P_ROBOT;
    
}



//Verifcation d'erreurs------------------------------------------------------------------------	
void base::Base::unique_id(unsigned int uid) {
	
    for (auto robot1 : roboList) {
		
        unsigned int id(1);
        robot1->get_uid(id);
        
        if (uid == id) {
			
			cout << message::identical_robot_uid(uid);
			exit(0); 
        }
	}
}
	
bool base::Base::base_overlap() {
	
	double x,y,xb,yb;
	position.getPoint(x,y);
	
	for (auto b : base_tab) {
		
		geomod::Point pos;
		b.getPosition(pos);
		
		if (geomod::intersection_cercles(pos,position,rayon_base,rayon_base)) {
			
			pos.getPoint(xb,yb);
			cout <<message::base_superposition(xb,yb,x,y);
			return true;
		}
	}
    return false;
}



//Constructeurs/Destructeur--------------------------------------------------------------------
base::Base:: Base(geomod::Point p1, double ress, int p, int f, int t, int c) : 
    position(p1), ressource(ress), nbP(p), nbF(f), nbT(t), nbC(c) {}   

base::Base::Base() : nbP (0), nbF (0), nbT(0), nbC(0) {
	position.setPoint(0,0);
}

base::Base::~Base() {
	for (auto robo : roboList) 
		delete robo;
}



//Autres---------------------------------------------------------------------------------------
void base::Base::addRobot(robot::Robot* r) {
	
	if (r != nullptr)
		roboList.push_back(r);  
}

void base::error(Base_Errors code) {
	
	cout <<"ERREUR"<<endl;
	switch (code) {
		
		case READ_BASE_INFO:  cout << "Erreur de lecture de la base"<<endl; break;
		
		case NB_VAL: cout << "Erreur de lecture du nombre de bases"<<endl; break;
	}
	exit(EXIT_FAILURE);
}

void base::ending(bool end) {
	
	if (end) {
				cout<<message::success();
				exit(0);
			}		
}
//---------------------------------------------------------------------------------------------
