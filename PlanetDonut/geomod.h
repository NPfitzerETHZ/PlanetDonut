#ifndef GEOMOD_H
#define GEOMOD_H

namespace geomod {
	
	class Point {                                                    
	public:
	    Point() : X(0), Y(0) {}
	    Point(double x, double y) : X(x), Y(y) {}
	    void setPoint(double x, double y);                                 
	    void getPoint(double& x, double& y);                                	                                  
	    void normalise();  
		                                                      
	private:
	    double X;	
	    double Y;
    }; 

    class Vector {                                       
	public:
	    Vector() : vX(0), vY(0) {}
        void setVect(double x, double y);
	    void getVect(double& x, double& y);     
	                            
	private:
	    double vX;
	    double vY;
    };
    
    void setterMax(double x);
    void getterMax(double& m, double& e);
    
    bool equal_zero (double val);
    
    //Normalisation de coordonnée et de point 2D                 
    void normalise (double& x, double& y); 
    
    //Norme et Coordonnées d'un vecteur (Surcharge)
    double vecteur (Point p1, Point p2, Vector& vect_min); 
    double vecteur(geomod::Point p1, geomod::Point p2);
    
    //Test d’égalité de 2 points
    bool test_egalite (Point p1, Point p2);	   
    
    //Test d’appartenance d’un point à un cercle
    bool point_cercle (Point p1, Point c1, double r);	
    
    //Test d’intersection de deux cercles
    bool intersection_cercles(Point centre_c1, Point centre_c2, double r1, double r2);  
    
    //Vérifie si le cercle déborde de l'autre côté de l'espace 2D
    bool cercle_dessin();  

}               
#endif
