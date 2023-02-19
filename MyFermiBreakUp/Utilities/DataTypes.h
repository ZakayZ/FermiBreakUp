//
// Created by Artem Novikov on 07.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_DATATYPES_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_DATATYPES_H_

#include <CLHEP/Vector/LorentzVector.h>

using FermiInt = int;
using FermiFloat = double;

using LorentzVector = CLHEP::HepLorentzVector;
using Vector3 = CLHEP::Hep3Vector;
using ParticleMomentum = Vector3;

class FermiPhaseSpaceDecay; /// TODO

//class FermiConfigurationList; /// Calculates probabilities of breaking up into 1..Max particles and stores it
//
//class FermiConfiguration; /// Have information about break up into K particles and stores particles
//
//class FermiSplitter; /// splits nucleus into possible fractions
//
//class FermiIntegerPartititon; /// gives all partitions of integer N
//
//class FragmentsPool; /// table values for particles
//
//class FermiPhaseSpaceDecay; /// class for Phase Space Calculations
//
//class FermiBreakUp; /// Calls break up function of a nucleus

#endif //FERMIBREAKUP_MYFERMIBREAKUP_DATATYPES_H_
