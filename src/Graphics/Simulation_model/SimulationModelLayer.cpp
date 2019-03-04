#include "SimulationModelLayer.h"
#include "../../Input/HWEventReceiver.h"
#include "Cameras/AllCameras.h"
#include "../../Physics/External/GroundPlane.h"

#include <ISceneNode.h>
#include <ISceneManager.h>
#include <IVideoDriver.h>

namespace Graphics {

	SimulationModelLayer::SimulationModelLayer(irr::video::IVideoDriver& vidDriver, irr::scene::ISceneManager& sceneManager, float windowAspect) :
		mVidDriver(vidDriver),
		mSceneManager(sceneManager),
		mGroundModel(vidDriver)
	{ 
		mLightSystem = std::make_unique<LightSystem>(vidDriver, sceneManager);
		mF9Model = std::make_unique<F9Model>(sceneManager);
	}

	void SimulationModelLayer::update(const chrono::Vector& currentCamPos_world, const Physics::F9_DSS& f9, float dt) {
		mF9Model->update(currentCamPos_world, f9, dt);
		mLightSystem->update(currentCamPos_world);
	}

	void SimulationModelLayer::render(const chrono::Vector& currentCamPos_world) {
		mSceneManager.drawAll();

		mGroundModel.render(currentCamPos_world);
	}

}