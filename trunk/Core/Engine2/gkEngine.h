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
#ifndef _gkEngine_h_
#define _gkEngine_h_

#include "gkCommon.h"
#include "gkMathUtils.h"
#include "OgreSingleton.h"



class gkEngine : public Ogre::Singleton<gkEngine>
{
public:

    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void tick(gkScalar rate) = 0;
    };


public:
    gkEngine(gkUserDefs *otherDefs = 0);
    ~gkEngine();

    static gkEngine& getSingleton();
    static gkEngine* getSingletonPtr();

    void initialize(bool autoCreateWindow = true);
    void finalize(void);
    bool isInitialized(void) {return m_initialized;}
    void run(void);
    void initializeWindow(void);


    void setActiveScene(gkScene *sc);

    // access to user defined parameters
    gkUserDefs& getUserDefs(void);
    void requestExit(void);

    gkBlendFile* loadBlendFile(const gkString& blend, const gkString& inResource = GK_DEF_GROUP);
    void loadResources(const gkString &name);

    void addDebugProperty(gkVariable *prop);
    void removeDebugProperty(gkVariable *prop);

    static gkScalar getStepRate();
    static gkScalar getTickRate();
    static gkScalar getAnimRate();


    // tick update hook
    GK_INLINE void setListener(Listener *listener) { m_listener = listener; }


private:


    // private interface
    class Private;
    Private*                m_private;
    friend class Private;


    Ogre::Root*             m_root;
    Ogre::RenderWindow*     m_window;
    bool                    m_initialized, m_ownsDefs;
    gkUserDefs*             m_defs;
    Listener*               m_listener;

    static gkScalar         m_tickRate;
    static gkScalar         m_animRate;
};



#endif//_gkEngine_h_
