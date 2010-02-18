/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _gkDynamicsWorld_h_
#define _gkDynamicsWorld_h_


#include "gkObject.h"
#include "gkMathUtils.h"


class btDynamicsWorld;
class btCollisionConfiguration;
class btBroadphaseInterface;
class btDispatcher;
class btConstraintSolver;
class btRigidBody;
class gkRigidBody;
class btTriangleMesh;
class btCollisionShape;
class gkPhysicsDebug;


// Game dynamics world
// TODO, loading via btWorldImporter & bullet serialization
class gkDynamicsWorld : public gkObject
{
public:
    typedef utListClass<gkRigidBody> RigidBodyList;

protected:

    // Parent scene
    gkScene*                    m_scene;

    btDynamicsWorld*            m_dynamicsWorld;
    btCollisionConfiguration*   m_collisionConfiguration;;
    btBroadphaseInterface*      m_pairCache;
    btDispatcher*               m_dispatcher;
    btConstraintSolver*         m_constraintSolver;
    RigidBodyList               m_bodies;
    gkPhysicsDebug*             m_debug;


    // drawing all but static wireframes 
    void localDrawObject(btRigidBody *rb);


    // Notifications for collision callbacks
    void dispatchCollisions(void);


    void preLoadImpl(void);
    void loadImpl(void);
    void unloadImpl(void);

public:
    gkDynamicsWorld(const gkString& name, gkScene *scene, gkObject::Loader *manual = 0);
    virtual ~gkDynamicsWorld();

    // Do one full physics step
    void step(gkScalar tick);

    void createParentChildHierarchy(void);

    // Creates the runtime body.
    // gkRigidBody takes care of setting motion states, as well as
    // applying physics calculations on a gkGameObject level
    gkRigidBody *createRigidBody(gkGameObject *state, gkObject::Loader *manual=0);


    // Gain raw access to the bullet world
    GK_INLINE btDynamicsWorld* getBulletWorld(void) {GK_ASSERT(m_dynamicsWorld); return m_dynamicsWorld;}
    // Access to parent scene
    GK_INLINE gkScene *getScene(void)               {GK_ASSERT(m_scene); return m_scene;}
};

#endif//_gkDynamicsWorld_h_
