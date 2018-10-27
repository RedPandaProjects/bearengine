#include "BearCore.hpp"
#ifdef BEAR_ENGINE_EXPORTS
#define BEARENGINE_API BEARPROJECT_EXPORT
#include "BearGraphics.hpp"
#else
#define BEARENGINE_API BEARPROJECT_IMPORT
#endif

#include "BearResource/BearResource.h"
#include "BearResource/BearResourceWithName.h"
#include "BearResource/BearMultiResource.h"
#include "BearGame/BearObject.h"

#include "BearResource/BearResourcesController.h"

#include "BearRender/BearTexture2D.h"
#include "BearRender/BearVertexShader.h"
#include "BearRender/BearPixelShader.h"
#include "BearRender/BearIndexBuffer.h"
#include "BearRender/BearVertexBuffer.h"

#include "BearMesh/BearMeshObject.h"

#include "BearMaterials/BearMaterial.h"
#include "BearMaterials/BearMaterialInstance.h"
#include "BearMaterials/BearMaterialController.h"
#include "BearMaterials/BearMaterialDefault.h"
#include "BearMaterials/BearMaterialSprite.h"
#include "BearMaterials/BearMaterialSpriteAlpha.h"

#include "BearRender/BearRender.h"
#include "BearRender/BearDevice.h"

#include "Bear2D/BearSprite.h"

/*
#include "Bear2D/BearSprite.h"

#include "BearGame/BearGameFactory.h"
#include "BearGame/BearGameManager.h"

#include "BearLevel/BearLevel.h"

#include "BearPhysics/BearPhysicsWorld.h"
#include "BearPhysics/BearPhysicsShape.h"
#include "BearPhysics/BearPhysicsBody.h"

*/