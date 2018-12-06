#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearMaterial
	{
		BEAR_CLASS_NO_COPY(BearMaterial);
	public:
		enum ShaderType
		{
			ST_Matrix=0,
			ST_Texture,
			ST_R,
			ST_RG,
			ST_RGB,
			ST_RGBA,
		};
		enum Shader
		{
			S_Pixel,
			S_Vertex,
		};
		static BearMaterial*Create(const bchar*px, const bchar*vs);
		~BearMaterial();
		void appendValue(const char*name,Shader shader,ShaderType shader_type,bsize id);
		void set();
		template<class C>
		inline void setValue(bsize id,const C&value)
		{
			setValue(id,(void*)&value);
		}
	protected:
		BearMaterial(const bchar*px, const bchar*vs);
	private:
	
		void setValue(bsize id,void*data);
		struct Value
		{

			Shader shader;
			ShaderType shader_type;
			char name[64];
		};
		BearCore::BearMap<bsize,Value> m_textures;
		BearVertexShader*m_vertex_shader;
		BearPixelShader *m_pixel_shader;
	};
};