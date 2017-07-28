
#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include "Particle.h"
#include <vector>
#include <HamsterAPIClientCPP/Hamster.h>

#define NUM_OF_PARTICALES 350
#define TRY_TO_BACK 20
#define TOP_PARTICALES 80
#define BAD_PARTICALES 80


using namespace std;
using namespace HamsterAPI;

//this class manage all the particals in the map
class LocalizationManager {

private:

	Hamster *hamster;
	OccupancyGrid *ogrid;
	vector<Particle *> particles;

	//return back the particales which out of the free cells range to free cells range
	bool returnBackOutOfRangeParticle(Particle *particle);

	//update the particale's belief
	double updateBelief(Particle *particle);

	//create a random particale
	void createRandomParticle(Particle *particle);

	//close the bad particale near to a particale with a high belief
	void createNeighborParticales(Particle *prevP,  Particle *newP);

	double randNumberFactor(int level);
	double randNumberFactorYaw(int level);

	void SortParticles();
	void GenerateNearTopParticle(Particle *targetParticle);
	void GenerateNearParticle(Particle *targetParticle, Particle *sourceParticle);




public:

	//constructor
	LocalizationManager( OccupancyGrid *ogrid, Hamster *hamster);

	//getter
	vector<Particle *> getParticles() const;

	//print the particale's vector
	void printParticles() ;

	//create new random particals on the map
	void setRandomParticalesOnMap();

	//move the particales according to the robot's movement
	void moveParticales(double deltaX, double deltaY, double deltaYaw);

	void resampleParticles();

	Particle * GetBestParticle();

	//distructor
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
