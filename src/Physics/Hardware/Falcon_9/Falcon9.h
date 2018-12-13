#ifndef PHYSICS_HARDWARE_FALCON9_H
#define PHYSICS_HARDWARE_FALCON9_H
#pragma once

#include "Physics/Hardware/Common/Core/ILaunchVehicle.h"
#include "Physics/Hardware/Falcon_9/Stage_1/Falcon9Stage1.h"
#include "Physics/Hardware/Falcon_9/Stage_2/Falcon9Stage2.h"
#include "definitions.h"

namespace Physics {
	class DSS;
}

namespace Physics {
	namespace Hardware {

		class Falcon9 : public ILaunchVehicle {
			friend Physics::DSS;
		private:
			Falcon9Stage1 mStage1;
			Falcon9Stage2 mStage2;

		public:
			Falcon9();
			~Falcon9() = default;

			void update(double t, double dt);
			
			Falcon9Stage1& getStage1() { return mStage1; }
			const Falcon9Stage1& getStage1() const { return mStage1; }
			Falcon9Stage2& getStage2() { return mStage2; }
			const Falcon9Stage2& getStage2() const { return mStage2; }

		private:
			virtual void assemble();

		};

	}
}

#endif
