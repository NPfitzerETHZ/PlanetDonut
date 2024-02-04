#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

const double dim_max(1000.);                    // km
const double rayon_min(50.);                    // km
const double rayon_max(150.);                   // km
const double display_rayon_robot(0.15);         // km
const double rayon_base(1);                     // km
const double rayon_comm(300.);                  // km

const double deltaD(5.);                        // km
const double maxD_prosp(10 * dim_max);          // km
const double maxD_forage(1.42 * dim_max);       // km
const double maxD_transp(5 * dim_max);          // km
const double maxD_com(1.42 * dim_max);          // km
const unsigned int max_robots(3);               // km

const double iniR(1000);                        // ktonne
const double finR(10*iniR);                     // ktonne
const double deltaR(iniR/4.);                   // ktonne
const double cost_repair(0.0005);               // ktonne/km
const double cost_prosp(iniR/100.);             // ktonne
const double cost_forage(iniR/10.);             // ktonne
const double cost_transp(iniR/10.);             // ktonne
const double cost_com(iniR/1000.);              // ktonne

const unsigned max_line(200);

#endif // CONSTANTES_H_INCLUDED
