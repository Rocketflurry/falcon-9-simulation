#ifndef GRAPHICS_SIMULATIONMODELLAYER_H
#define GRAPHICS_SIMULATIONMODELLAYER_H
#pragma once

#include "Lighting/LightSystem.h"
#include "Models/Falcon_9/F9Model.h"
#include "Models/GroundModel.h"

#include <memory>

namespace irr {
	namespace scene {
		class ISceneNode;
		class ISceneManager;
		class IMeshSceneNode;
	}
	namespace video {
		class IVideoDriver;
	}
}

namespace Physics {
	class F9_DSS;

	namespace External {
		class GroundPlane;
	}
}

namespace Graphics {

	// Only concerned with managing models of entities in the simulation
	class SimulationModelLayer {
	private:
		irr::video::IVideoDriver& mVidDriver;
		irr::scene::ISceneManager& mSceneManager;
		std::unique_ptr<LightSystem> mLightSystem;
		std::unique_ptr<F9Model> mF9Model;
		GroundModel mGroundModel;

	public:
		SimulationModelLayer(irr::video::IVideoDriver& vidDriver, irr::scene::ISceneManager& sceneManager, float windowAspect);
		~SimulationModelLayer() = default;

		void update(const chrono::Vector& currentCamPos_world, const Physics::F9_DSS& f9, float dt);
		void render(const chrono::Vector& currentCamPos_world);

	private:
		void drawGrid(const chrono::Vector& currentCamPos_world);

	};

}

#endif // GRAPHICS_SIMULATIONMODELLAYER_H
