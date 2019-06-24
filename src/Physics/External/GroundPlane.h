#ifndef PHYSICS_EXTERNAL_GROUNDPLANE_H
#define PHYSICS_EXTERNAL_GROUNDPLANE_H
#pragma once

#include <core/ChVector.h>
#include <physics/ChBody.h>

namespace chrono {
    class ChSystemNSC;
}

namespace Physics {
    namespace External {

        class GroundPlane {
        private:
            static const chrono::Vector mPos_world;
            static const float mThickness;
            chrono::ChSystemNSC& mSystemHandle;
            std::shared_ptr<chrono::ChBody> mBody;

        public:
            GroundPlane(chrono::ChSystemNSC& systemHandle);
            ~GroundPlane() = default;

            static const chrono::Vector& getPos_world();
        
        };

    }
}

#endif // PHYSICS_EXTERNAL_GROUNDPLANE_H
