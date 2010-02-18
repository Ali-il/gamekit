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
#ifndef _gkPhysicsDebug_h_
#define _gkPhysicsDebug_h_


#include "gkCommon.h"
#include "OgreSimpleRenderable.h"
#include "OgreHardwareVertexBuffer.h"
#include "LinearMath/btIDebugDraw.h"

class gkDynamicsWorld;

struct gkDebugVertex 
{
    float v[3];
    unsigned int color;
};


// for debugging / building line lists 
class gkPhysicsDebug : public Ogre::SimpleRenderable, public btIDebugDraw
{
public:
    typedef utArray<gkDebugVertex> Buffer;

public:
    gkPhysicsDebug(gkDynamicsWorld *wo);
    virtual ~gkPhysicsDebug();


    Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;
    Ogre::Real getBoundingRadius(void) const;

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    void draw3dText(const btVector3& location,const char* textString);

    void reportErrorWarning(const char* warningString);
    void setDebugMode(int debugMode);
    int getDebugMode() const;


    // write contents to buffer
    void flush(void);

protected:

    void verifyNode(void);
    void growBuffer(UTsize newSize);

    Ogre::SceneNode*    m_node;
    gkDynamicsWorld*    m_physics;
    Ogre::Real          m_radius;
    Buffer              m_lineBuf;
    Ogre::Vector3       m_bbmin, m_bbmax;
    UTsize              m_bufSize;
    int                 m_flags;

    // main buffer
    Ogre::HardwareVertexBufferSharedPtr m_buffer;
    
};




#endif//_gkPhysicsDebug_h_
