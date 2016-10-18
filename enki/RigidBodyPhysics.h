/*
    Enki - a fast 2D robot simulator
    Copyright (C) 1999-2016 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006-2008 Laboratory of Robotics Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication
    arising from research using this software are asked to add the
    following reference:
    Enki - a fast 2D robot simulator
    http://home.gna.org/enki
    Stephane Magnenat <stephane at magnenat dot net>,
    Markus Waibel <markus dot waibel at epfl dot ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __ENKI_RIGID_BODY_PHYSICS_H
#define __ENKI_RIGID_BODY_PHYSICS_H

#include "System.h"

namespace Enki
{
    class RigidBodyPhysics;

    struct RigidBody: GlobalComponent<RigidBodyPhysics>
    {
        void initPhysics(double dt, RigidBodyPhysics* system) {}
        void finalizePhysics(double dt, RigidBodyPhysics* system) {}
    };

    struct Collider: LocalComponent<RigidBodyPhysics, Collider>
    {
    };

    struct ConvexCylinderCollider: Collider
    {
    };

    struct ConvexPolygonCollider: Collider
    {
    };

    struct HollowCylinderCollider: Collider
    {
    };

    // Note: this should be generalized for polygon
    struct HollowRectangleCollider: Collider
    {
    };
    // struct HollowPolygonCollider: Collider

    struct RigidBodyPhysics: System
    {
        /**
            This phase updates the rigid bodies:
            - apply forces
            - update pose from speed
            - store pose before collision
            - init temporary pose
        */
        typedef GlobalPhase<RigidBodyPhysics, RigidBody> InitPhaseBase;
        struct InitPhase: InitPhaseBase
        {
            using InitPhaseBase::InitPhaseBase;
            virtual void step(double dt);
        };

        typedef LocalPhase<RigidBodyPhysics, Collider, Collider> CollisionPhaseBase;
        /**
            This phase performs object to object collisions using the collider components:
            - update shapes of rigid colliders
            - detect collisions
            - perform rigid body physics
            - update temporary pose in Rigid bodies
        */
        struct CollisionPhase: CollisionPhaseBase
        {
            using CollisionPhaseBase::CollisionPhaseBase;
        };

        typedef GlobalPhase<RigidBodyPhysics, RigidBody> FinalizePhaseBase;
        /**
            This phase finalizes the physics
            - compute deinterlace distance
            - update pose from temporary pose
        */
        struct FinalizePhase: FinalizePhaseBase
        {
            using FinalizePhaseBase::FinalizePhaseBase;
            virtual void step(double dt);
        };

        RigidBodyPhysics(World* world);
    };
} // namespace Enki

#endif // __ENKI_RIGID_BODY_PHYSICS_H