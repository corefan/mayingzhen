#include "ShaderProgram.h"
#include "PrePareShaderSource.h"

namespace ma
{	
	IMPL_OBJECT(ShaderProgram,Resource)

	ShaderProgram::ShaderProgram()
	{
	}
	
	ShaderProgram::~ShaderProgram()
	{
	}

	void ShaderProgram::RegisterAttribute()
	{
		ACCESSOR_ATTRIBUTE(ShaderProgram, "VSFile", GetVSFile, SetVSFile, const char*, NULL, AM_DEFAULT);
		ACCESSOR_ATTRIBUTE(ShaderProgram, "PSFile", GetPSFile, SetPSFile, const char*, NULL, AM_DEFAULT);
		ACCESSOR_ATTRIBUTE(ShaderProgram, "ShaderMacro", GetShaderMacro, SetShaderMacro, const char*, NULL, AM_DEFAULT);
	}

	void ShaderProgram::BindUniform()
	{
		for (UINT i = 0; i < m_arrUniform.size(); ++i)
		{
			m_arrUniform[i]->Bind();		
		}
	}

	void ShaderProgram::Reload()
	{
		m_arrUniform.clear();
		m_eResState = ResUnLoad;

		CreateFromFile(m_strVSFile.c_str(),m_strPSFile.c_str(),m_shaderMacro.c_str());
	}

	void ShaderProgram::CreateFromFile(const char* vshPath, const char* fshPath, const char* defines/* = NULL*/)
	{
		if (m_eResState == ResInited)
		{
			ASSERT(m_strVSFile == vshPath);
			ASSERT(m_strPSFile == fshPath);
			ASSERT(m_shaderMacro == defines);
			return;
		}

		m_strVSFile = vshPath ? vshPath : "";
		m_strPSFile = fshPath ? fshPath : "";
		m_shaderMacro = defines ? defines: "";

		m_eResState = ResLoaded;

		GetRenderSystem()->ShaderStreamComplete(this);
	}

	void ShaderProgram::RT_StreamComplete()
	{
		std::string strPath = GetRenderSystem()->GetShaderPath();

		std::string strPathVS = strPath + m_strVSFile + ".vert";
		std::string strPathFS = strPath + m_strPSFile + ".frag";
	
		std::string strVshSource = PrePareShaderSource(strPathVS.c_str(),m_shaderMacro.c_str());
		std::string strFshSource = PrePareShaderSource(strPathFS.c_str(),m_shaderMacro.c_str());

		CreateFromSource(strVshSource.c_str(), strVshSource.length(), 
			strFshSource.c_str(), strFshSource.length());

		ParseUniform();
		
		for (UINT i = 0; i < m_arrUniform.size(); ++i)
		{
			GetParameterManager()->UseDefaultBing(m_arrUniform[i].get());
		}
		
		m_eResState = ResInited;
	}


	Uniform* ShaderProgram::GetUniform(const char* name) const
	{
		ASSERT(name);
		if (name == NULL)
			return NULL;

		for (UINT i = 0; i < m_arrUniform.size(); ++i)
		{
			if (strcmp(name,m_arrUniform[i]->GetName()) == 0)
			{
				return m_arrUniform[i].get();
			}
		}
		
		return NULL;
	}

	Uniform* ShaderProgram::GetUniform(UINT index) const
	{
		return m_arrUniform[index].get();
	}

	UINT ShaderProgram::GetUniformCount() const
	{
		return m_arrUniform.size();
	}

	const char* ShaderProgram::GetVSFile() const
	{
		return m_strVSFile.c_str();
	}

	void ShaderProgram::SetVSFile(const char* pszVSFile)
	{
		m_strVSFile = pszVSFile ? pszVSFile : "";
	}

	const char*	ShaderProgram::GetPSFile() const
	{
		return m_strPSFile.c_str();
	}

	void ShaderProgram::SetPSFile(const char* pszPSFile)
	{
		m_strPSFile = pszPSFile ? pszPSFile : "";
	}

	const char*	ShaderProgram::GetShaderMacro() const
	{
		return m_shaderMacro.c_str();
	}

	void ShaderProgram::SetShaderMacro(const char* pszMacro)
	{
		m_shaderMacro = pszMacro ? pszMacro : "";
	}

	Uniform* ShaderProgram::AddUniform(const char* pName)
	{
		Uniform* pUnifrom = new Uniform();
		pUnifrom->SetName(pName);
		m_arrUniform.push_back(pUnifrom);
		return pUnifrom;
	}

}
