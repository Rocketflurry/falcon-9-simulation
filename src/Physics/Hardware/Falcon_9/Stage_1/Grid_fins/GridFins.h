#ifndef PHYSICS_HARDWARE_FALCONGRIDFINS_H
#define PHYSICS_HARDWARE_FALCONGRIDFINS_H
#pragma once

#include "GridFin.h"
#include "Physics/Hardware/Common/Core/StageComponentGroup.h"

namespace Physics {
	namespace Hardware {
		
		class GridFins : public StageComponentGroup {
		private:
			glm::dvec3
				mTotalCentrePressure_stage,
				mTotalForce_world,
				mTotalTorque_stage;

			double mTotalArea = 0.0;

		public:
			GridFins();
			~GridFins() = default;

			void update(double dt/* , double fluidDensity, glm::dvec3 flowVelocity_stage */);

			double getTotalArea() const { return mTotalArea; }
			glm::dvec3 getCentrePressure_stage() const { return mTotalCentrePressure_stage; }
			glm::dvec3 getTotalForce_world() const { return mTotalForce_world; }
			glm::dvec3 getTotalTorque_stage() const { return mTotalTorque_stage; }

		private:
			void updateAllFins(double dt/* , double fluidDensity, glm::dvec3 flowVelocity_stage */) const;
			void updateTotalForce_world();
			void updateTotalTorque_stage();

		};

	}
}

#endif
