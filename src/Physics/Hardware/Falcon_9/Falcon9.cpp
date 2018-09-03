#include "Falcon9.h"

namespace Physics {
	namespace Hardware {

		Falcon9::Falcon9() :
			ILaunchVehicle({ "LC-39A" })
		{
			assemble();
			//mSurfaceLocation.setGPSPosition({ 53.826687, -2.419171, 0.0 });
			mSurfaceLocation.setGPSPosition({ 0.0, 0.0, 0.0 });
		}

		void Falcon9::update(double t, double dt) {
			mStage1.update(t, dt);
			mStage2.update(t, dt);
			
			ILaunchVehicle::update(t, dt);
		}

		void Falcon9::checkInput(double dt) {
			using namespace GF;
			
			mStage1.checkInput_temp(dt);

			//Basic stage separation just disconnects both stages and doesn't apply any force.
			//TODO: Implement separation mechanism 
			if (Input::isKeyReleased(GLFW_KEY_ENTER)) {
				mSubBodies[0].disconnect();
				mSubBodies[1].disconnect();
			}

			//Reconnects both stages together, and moves the launch vehicle into its inertial state
			if (Input::isKeyPressed(GLFW_KEY_G)) {
				mState.reset();
				glm::dvec3 vehiclePosition = { 0.0, 0.0, 0.0 };
				glm::dmat4 vehicleRotation = glm::rotate(glm::radians(0.0), glm::dvec3(1.0, 0.0, 0.0));
				mState.setObjectToParentTransform({ vehiclePosition, vehicleRotation });

				mStage1.getState().reset();
				mStage2.getState().reset();

				mSubBodies[0].disconnect();
				mSubBodies[1].disconnect();
				addBody(mStage1);
				addBody(mStage2, glm::dvec3(0.0, 45.76182, 0.0));
			}

			if (Input::isKeyPressed(GLFW_KEY_HOME))
				mState.setAngularVelocity_world(glm::dvec3(0.0));
		}

		void Falcon9::assemble() {
			addBody(mStage1);
			addBody(mStage2, glm::dvec3(0.0, 45.76182, 0.0));
		}

	}
}