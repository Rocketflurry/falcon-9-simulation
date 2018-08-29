#include "Merlin1DVac.h"

namespace Physics {
	namespace Hardware {

		Merlin1DVac::Merlin1DVac(GF::CoordTransform3D merlinToStage) :
			Engine(merlinToStage)
		{
			setTypeSpecificParams();
		}

		void Merlin1DVac::setTypeSpecificParams() {
			mThrustMagnitude = 934000.0; //934000.0
			mMass_comp = { 1100.0, {0.0, -2.5, 0.0 } };
			mPeakMassFlowRate = 273.68;
			mThrottleMin = 0.39;
			mThrottleMax = 1.0;
			mExpansionRatio = 165.0;

			updateProperties();
		}

	}
}