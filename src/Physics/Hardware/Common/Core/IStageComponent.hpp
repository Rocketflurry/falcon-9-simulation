#ifndef PHYSICS_HARDWARE_ISTAGECOMPONENT_H
#define PHYSICS_HARDWARE_ISTAGECOMPONENT_H
#pragma once

#include <PhysicsFramework/Mass.h>
#include <PhysicsFramework/InertiaTensor.h>
#include <GraphicsFramework/CoordTransform3D.h>

namespace Physics {
	namespace Hardware {

		class IStageComponent {
			friend class StageComponentGroup;
		public:
			enum class CoordSpace { component, stage };

		protected:
			Mass mMass_comp;
			InertiaTensor mCMInertia_comp;
			GF::CoordTransform3D mCompToStage;

		public:
			IStageComponent(GF::CoordTransform3D compToStage = GF::CoordTransform3D(), Mass mass_comp = Mass(), InertiaTensor CMInertia_comp = InertiaTensor()) :
				mMass_comp(mass_comp),
				mCMInertia_comp(CMInertia_comp),
				mCompToStage(compToStage)
			{ }

			virtual ~IStageComponent() = default;

			Mass getMass(CoordSpace space) {
				if (space == CoordSpace::component)
					return mMass_comp;
				else if (space == CoordSpace::stage)
					return Mass(mMass_comp.getValue(), mCompToStage.toParentSpace(mMass_comp.getCentre()));
				else
					return Mass();
			}

			//This function is able to return the complete inertia of the component in stage space
			InertiaTensor getInertia_stage(glm::dvec3 stageCentreMass_stage) {
				InertiaTensor cmInertia_stageRotation = mCMInertia_comp.afterRotation(mCompToStage.getLocalToParent_rotation());

				return 
					InertiaTensor::parallelAxis(
						cmInertia_stageRotation, 
						mMass_comp.getValue(), 
						mCompToStage.toParentSpace(mMass_comp.getCentre()) - stageCentreMass_stage
					);
			}

			const GF::CoordTransform3D& getCompToStageTransform() const { return mCompToStage; }
			double getMassValue() const { return mMass_comp.getValue(); }

		};

	}
}

#endif
