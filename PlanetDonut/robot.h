#ifndef ROBOT2_H
#define ROBOT2_H

#include <iostream>

#include <string>
#include <vector>

#include "geomod.h"

namespace robot {

	enum Robot_Errors{ROBOT};
	
//=============================
    class Robot{	
    public:
        Robot(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint); 
        Robot();
        ~Robot();
        
        void get_uid(unsigned int& id);  
        geomod::Point get_Position() { return geomod::Point(x,y); }
        std::vector<Robot*> getLink() {return liste_adj;}

    protected:
		std::vector<Robot*> liste_adj;
        unsigned int uid;
        double dp;
        double x, y, xb, yb;
        bool atteint;

};

//-----------------------------
    class Prospection: public Robot{
    public:
        Prospection (unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint,bool Retour, bool Found);
        Prospection();
        
        void casePR(std::string line,int& state,unsigned int& uid1);

    private:
		double xg,yg;
		double rayong, capaciteg;
        bool retour,found;
};

//-----------------------------
    class Forage: public Robot{
    public:
        Forage(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint);
        Forage();
        
        void caseFR(std::string line,int& state,unsigned int& uid1);
 
    private:
};

//-----------------------------
    class Transport: public Robot{
    public:
        Transport(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint,bool Retour);
        Transport();
        
        void caseTR(std::string line,int& state,unsigned int& uid1);

    private:
        bool retour;

};

//-----------------------------
    class Communication: public Robot{
    public:
        Communication(unsigned Uid, double Dp,double X,double Y,double Xb,double Yb,bool Atteint);
        Communication();
        
		bool caseCR(std::string line,int& state,unsigned int& uid1,geomod::Point pos_base);

    private:
};


bool rc_center(geomod::Point pos_base, geomod::Point pos_rc);

bool check_bool(std::string val);

//Mise à jours de l'état de lecture
void nextState(int& state);

//Définition de l'état après la lecture du dernier robot de communication d'une base
bool lastState(int& state, bool rc_test, double x, double y);

void setPFTCB(int nbp, int nbf, int nbt, int nbc, int nbb);

void error(Robot_Errors code);
}

#endif
