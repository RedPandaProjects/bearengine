#include "BearEngine.hpp"


BearEngine::BearSpriteAnimater::BearSpriteAnimater(const BearName & type) :BearObject(type, 0), m_animate_array(0), m_pause(0), m_sampler(NNull), m_shader(NDefault, NDefault), Rotation(0), Rect(0, 0, 1, 1)
{
	m_shader.SetBlend(BearShader::BF_SRC_ALPHA, BearShader::BF_INV_SRC_ALPHA);
	m_sampler.SetFilter(BearSampler::SF_MAG_LINEAR_MIP_POINT);
	m_sampler.SetMode(BearSampler::SM_BORDER);
}

BearEngine::BearSpriteAnimater::~BearSpriteAnimater()
{
	if (m_animate_array)GResourceManager->Destroy(m_animate_array);
}

void BearEngine::BearSpriteAnimater::Play(const bchar * name, bool loop)
{
	if (m_animate_array == 0)return;
	m_current_animation = m_animate_array->get()->Animations.find(name);
	m_current_cut = m_current_animation->second.cuts.begin();
	m_timer = 0;
}

void BearEngine::BearSpriteAnimater::SetPause(bool pause)
{
	if (m_animate_array == 0)return;
	m_pause = pause;
}

bool BearEngine::BearSpriteAnimater::IsPause() const
{
	if (m_animate_array == 0) return false;
	return m_pause;
}

bool BearEngine::BearSpriteAnimater::IsStop() const
{
	if (m_animate_array == 0) return true;
	return m_current_animation == m_animate_array->get()->Animations.end();
}

void BearEngine::BearSpriteAnimater::Stop() 
{
	if (m_animate_array == 0)return;
	m_current_animation = m_animate_array->get()->Animations.end();
}

void BearEngine::BearSpriteAnimater::SetAnimateArray(const BearName & name)
{
	if (m_animate_array)GResourceManager->Destroy(m_animate_array);
	m_animate_array = GResourceManager->GetAnimateArray2D(name);
	m_sampler.SetTexture(m_animate_array->get()->GetTextureName());
}

void BearEngine::BearSpriteAnimater::Destroy()
{
	BEAR_OBJECT_DESTROY(BearSpriteAnimater);
}

void BearEngine::BearSpriteAnimater::Update(float time)
{
	if (m_animate_array == 0)return;
	if (m_current_animation == m_animate_array->get()->Animations.end())return;
	if (!m_pause)m_timer += time ;
	if (m_timer > m_current_animation->second.delay&&m_current_cut != m_current_animation->second.cuts.end())
	{
		m_current_cut++;
		m_timer = 0;
	}
	else
	{
		if(!m_pause)
		m_timer += time * 1000;
	}
	if (m_current_cut == m_current_animation->second.cuts.end()  )
	{
		if (m_loop)
		{
			m_timer = 0;
			m_current_cut = m_current_animation->second.cuts.begin();
		}
		else
		{
			m_current_animation = m_animate_array->get()->Animations.end();
			return;
		}
	}
	GRender->SetShader(m_shader);
	GRender->SetPixel(0, m_sampler);

	m_matrix.BuildIdentity();

	m_matrix = m_matrix * BearCore::BearMatrix().Scale(m_current_cut->SpriteSize.x, m_current_cut->SpriteSize.y, 0);
	m_matrix = m_matrix * BearCore::BearMatrix().RotateZ(Rotation);
	m_matrix = m_matrix * BearCore::BearMatrix().Translation(Position.x + ((Size.x - m_current_cut->SpriteSize.x) / 2), Position.y + (Size.y - m_current_cut->SpriteSize.y), 0);
	//m_matrix = m_matrix * GRender->GetOthro();

	/*BearGraphics::BearRenderInterface::SetItemToVertexShader("matrix", m_matrix);
	/BearGraphics::BearRenderInterface::SetItemToVertexShader("uv", m_current_cut->TextureUV);*/
//	G2DPlane->Update(time);

}

void BearEngine::BearSpriteAnimater::Save(BearCore::BearOutputStream * stream)
{
}

void BearEngine::BearSpriteAnimater::Load(const BearCore::BearInputStream * stream)
{
}
