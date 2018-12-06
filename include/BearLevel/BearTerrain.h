#pragma
namespace BearEngine
{
	class BEARENGINE_API BearTerrain :public BearObject
	{
		BEAR_OBJECT(BearTerrain);
		BearTerrain(const BearName&type);
		~BearTerrain();
	public:
		void Load(const BearName&name,bsize width,bsize height, const BearName&texture1, const BearName&texture2, const BearName&texture3);
		virtual void Destroy();
		virtual void Update(float time);
	private:
		virtual void Save(BearCore::BearOutputStream*stream);
		virtual void Load(const BearCore::BearInputStream*stream);
		BearShader m_shader;
		BearSampler m_sampler;
		BearGraphics::BearVertexBufferRef VertexBuffer;
		BearGraphics::BearIndexBufferRef IndexBuffer;
		BearGraphics::BearShaderConstantsRef m_texturem_multiplier;
		BearSampler m_samplers[3];
		bool m_is_load;
	};
}