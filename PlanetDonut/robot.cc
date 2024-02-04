#include <sstream>

#include <string>

#include "constantes.h"
#include "robot.h"
#include "message.h"

enum States{P_ROBOT = 9, F_ROBOT = 10, T_ROBOT = 11, C_ROBOT = 12, BASE_INFO = 3};

static int p,f,t,c,b;
static bool rc_confirm(false);

using namespace std;

//Lecture----------------------------------------------------------------------------------------------
void robot::Prospection::casePR(string line,int& state, unsigned int& uid1) {
	
	string att, ret, fou;
	istringstream info(line);
	
	nextState(state);
	
	if (!(info >> uid >> dp >> x >> y >> xb >> yb >> att >>ret >> fou))  error(ROBOT);
	
	atteint = check_bool(att);
    retour = check_bool(ret);
	found = check_bool(fou);
	
	uid1 = uid;
	
	if(found==true) info >> xg >> yg >> rayong >> capaciteg;
    
}

void robot::Forage::caseFR(string line,int& state,unsigned int& uid1) {
	
	istringstream info(line);
	string att;
    
    nextState(state);
    
	if (!(info >> uid >> dp >> x >> y >> xb >> yb >> att)) error(ROBOT);

	atteint = check_bool(att);
	
	uid1 = uid;
}  

void robot::Transport::caseTR(string line, int& state, unsigned int& uid1) {
    
	istringstream info(line);
	string att, ret;
	
    nextState(state);
    
	if (!(info >> uid >> dp >> x >> y >> xb >> yb >> att >> ret)) error(ROBOT);
	
	atteint = check_bool(att);
	retour = check_bool(ret);
	
	uid1 = uid;
}	

bool robot::Communication::caseCR(string line,int& state, unsigned int& uid1, geomod::Point pos_base) {
    
    bool finish;
	double Xb,Yb;
	bool rc_test;
	istringstream info(line);
	string att;
	
	pos_base.getPoint(Xb,Yb);
	
	if (!(info >> uid >> dp >> x >> y >> xb >> yb >> att)) error(ROBOT);
	
    atteint = check_bool(att);
    
    uid1 = uid;
    
    geomod::Point pos_rc(x,y);
    rc_test = rc_center(pos_base,pos_rc);
    
    finish = lastState(state,rc_test,Xb,Yb);
    
    return finish;
}
//-----------------------------------------------------------------------------------------------------



//Constructeurs/Destructeurs----------------------------------------------------------------------------------------
robot::Robot::Robot(): uid(0), dp(0), x(0), y(0), xb(0), yb(0), atteint(false) {}
robot::Robot::Robot(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint)
	:uid(Uid),dp(Dp),x(X),y(Y),xb(Xb), yb(Yb), atteint(Atteint) {}
robot::Robot::~Robot() {
	for (auto robo: liste_adj) 
		delete robo;
}
	
robot::Prospection::Prospection(): Robot(), xg(0), yg(0), rayong(0), capaciteg(0), retour(false), found(false) {}
robot::Prospection::Prospection (unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint,bool Retour, bool Found)
    :Robot(Uid,Dp,X,Y,Xb,Yb,Atteint),retour(Retour),found(Found) {}  

robot::Forage::Forage() {}
robot::Forage::Forage(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint)
	:Robot(Uid,Dp,X,Y,Xb,Yb,Atteint) {}

robot::Transport::Transport(): Robot(), retour(false) {}
robot::Transport::Transport(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint,bool Retour)
    :Robot(Uid,Dp,X,Y,Xb,Yb,Atteint), retour(Retour) {}	
        
robot::Communication::Communication() {}
robot::Communication::Communication(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint)
    :Robot(Uid,Dp,X,Y,Xb,Yb,Atteint) {}	
    
//-----------------------------------------------------------------------------------------------------



//Autres-----------------------------------------------------------------------------------------------
bool robot::rc_center(geomod::Point pos_base, geomod::Point pos_rc) {
	
	double X,Y,x,y;
	pos_base.getPoint(X,Y);
	pos_rc.getPoint(x,y);
	
	if (geomod::test_egalite(pos_base,pos_rc)) {
		return true;
	}
	return false;
}	

bool robot::check_bool(string val) {
    
	if(val == "false") return false;
	if(val == "true") return true;
	return 0;
}

void robot::setPFTCB(int nbp, int nbf, int nbt, int nbc, int nbb) {
    
	p = nbp;
	f = nbf;
	t = nbt;
	c = nbc;
	b = nbb;
}

void robot::nextState(int& state) {
    
    if (p == 1 or state != P_ROBOT) {
        state = F_ROBOT;
        
        if (f == 0) {
            state = T_ROBOT;
            
            if (t == 0) {
                state = C_ROBOT;
                return;
            }
            else t -= 1;
            return;
        }
        else f -= 1;
        return;
    }
    else p -= 1;
}

bool robot::lastState(int& state, bool rc_test, double x, double y) {
	
	if (rc_test == true) rc_confirm = true;
	if (c == 1) {
		
		if(rc_confirm == false) {
			
			cout<<message::missing_robot_communication(x,y);
			exit(0);
		}
		
		else rc_confirm = false;
		
		if (b > 1) 
			state = BASE_INFO;
			
        else return true;
	}
	
	else {
		c -= 1;
		state = C_ROBOT;
    }
    
    return false;
}
	
void robot::error(Robot_Errors code) {
    
	cout <<"ERREUR"<<endl;
	switch (code) {
		case ROBOT:  cout << "Erreur de lecture Robot "<<endl; break;
	}
	exit(0);
}

void robot::Robot::get_uid(unsigned int& id) { 
	id = uid;
}
//-----------------------------------------------------------------------------------------------------
