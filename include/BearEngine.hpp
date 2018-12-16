#pragma once
#include "BearCore.hpp"
#include "BearGraphics.hpp"
#include "BearSound.hpp"
#include "Box2D/Box2D.h"

#ifdef BEAR_ENGINE_EXPORTS
#define BEARENGINE_API BEARPROJECT_EXPORT
#else
#define BEARENGINE_API BEARPROJECT_IMPORT
#endif


#include "BearCore/BearName.h"
#include "BearCore/BearObject.h"



#include "BearCore/BearObjectManager.h"

#include "BearCore/BearConfig.h"
#include "BearCore/BearIncluder.h"

#include "BearCore/BearCallBack.h"

#include "BearCore/BearEngine.h"
#include "BearCore/BearEditor.h"

#include "BearResource/BearFont.h"
#include "BearResource/BearAnimateArray2D.h"

#include "BearResource/BearResource.h"
#include "BearResource/BearResourceManager.h"

#include "BearRender/BearShader.h"
#include "BearRender/BearSampler.h"
#include "BearRender/BearVertex.h"
#include "BearRender/BearVertexArray.h"
#include "BearRender/BearRender.h"
#include "BearRender/BearViewport.h"

#include "Bear2D/Bear2DPlane.h"
#include "Bear2D/BearTile.h"
#include "Bear2D/BearSprite.h"
#include "Bear2D/BearRenderText.h"
#include "Bear2D/BearSpriteAnimater.h"

#include "BearIO/BearInput.h"

#include "BearLevel/BearObjectLevel.h"
#include "BearLevel/BearTerrain.h"
#include "BearLevel/BearLevel.h"

#include "BearCore/BearGameController.h"

#include "BearCore/BearConsoleCommand.h"
#include "BearCore/BearConsole.h"

