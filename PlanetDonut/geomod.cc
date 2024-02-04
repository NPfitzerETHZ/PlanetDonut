#include "geomod.h"
#include <iostream>
#include <cmath>
                 
using namespace std;
                             
namespace {
	double epsilon_zero;
	double maxi;                                       
}

	
//===========================================================================================================================================================================

void geomod::Point::normalise() {                           

	if (abs(X) < maxi and abs(Y) < maxi)            
		return;	

    
	if (abs(X) >= maxi or abs(Y) >= maxi) {     
		
		if (X < 0 and Y < 0) {
			X = X + 2*maxi;
			Y = Y + 2*maxi;
			return;
		}
			
		if (X > 0 and Y > 0) {
			X = X - 2*maxi;
			Y = Y - 2*maxi;
			return;
		}
			
		if (X > 0 and Y < 0) {
			X = X - 2*maxi;
			Y = Y + 2*maxi;
			return;
		}
		
		if (X < 0 and Y > 0){
			X = X + 2*maxi;
			Y = Y - 2*maxi;	
			return;
		}
		 
	}	 
}

void geomod::normalise(double& x, double& y) {	
		
	geomod::Point p;
	p.setPoint(x,y);
	p.normalise();
	p.getPoint(x,y);	
}

double geomod::vecteur(geomod::Point p1, geomod::Point p2, geomod::Vector& vect_min) {	
	
	double distance(0);
	double distance_temporaire(0);
	
	double x1(0);
	double y1(0);
	double x2(0);
	double y2(0);
	
	p1.getPoint(x1,y1);
	p2.getPoint(x2,y2);
	
	double vect_minX(x2-x1);
	double vect_minY(y2-y1);
	
	distance = sqrt(pow((x2-x1),2)+ pow((y2-y1),2));
	
	double d1;
	double d2;
					
	for (int kx=-1; kx<2;kx++){
		
		for (int ky=-1; ky<2;ky++){
			 
			 d1 = ((2*kx*maxi)+x2-x1);
			 d2 = ((2*ky*maxi)+y2-y1);
			 distance_temporaire= sqrt(pow(d1,2)+pow(d2,2));	
										 
			 if (distance_temporaire<distance){
				  distance = distance_temporaire;
				  vect_minX = d1;
				  vect_minY = d2;
		     }
			
		}
	}
		
	vect_min.setVect(vect_minX,vect_minY);
    return distance;												 
}


//===========================================================================================================================================================================


double geomod::vecteur(geomod::Point p1, geomod::Point p2) {
    
	geomod::Vector vect_min; 
	double distance;
	distance = vecteur(p1,p2,vect_min);
	return distance;
}

bool geomod::equal_zero(double val) {
	
	if (val < epsilon_zero)
		return true;
		
	else  
		return false;
}

bool geomod::test_egalite(Point p1, Point p2){
	 
	if(vecteur(p1,p2)<epsilon_zero)	
		return true;
		
	else 
		return false;	
}

bool geomod::point_cercle(Point p1, Point c1, double r) {
	                              
	double n = vecteur(p1,c1);                
	
	if (n < r - epsilon_zero) 
		return true;

	else 
		return false;
}

bool geomod::intersection_cercles(geomod::Point centre_c1, geomod::Point centre_c2, double r1, double r2) {
	
	geomod::Vector vect_min;  
	                                
	double n = vecteur(centre_c1,centre_c2,vect_min);
	if (n == 0 and r1 == 0 and r2 == 0) 
	    return true;
	
	if (n < r1 + r2 - epsilon_zero)
		return true;
		
	else 
		return false;
}
	  	
void geomod::setterMax (double x) {
	 
    maxi = abs(x);                  
    epsilon_zero = pow(10,-10)*maxi;
}
    
void geomod::getterMax (double& m , double& e) {
	
	e = epsilon_zero;                 
	m = maxi;	                      
}  

//Méthodes setter et getter des classess Point et Vector
void geomod::Point::setPoint(double x, double y)   {X = x; Y = y;}	
void geomod::Point::getPoint(double& x, double& y) {x = X; y = Y;} 

void geomod::Vector::setVect(double x, double y)   { vX = x; vY = y;}	                                
void geomod::Vector::getVect(double& x, double& y) { x = vX; y = vY;} 
