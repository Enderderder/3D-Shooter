//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : AssetMgr.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef ASSETMGR_H
#define ASSETMGR_H

// OpenGL Library Include
#include <glew.h>
#include <freeglut.h>

class CAssetMgr
{
public:
	// Singleton Methods
	static CAssetMgr* GetInstance();
	static void DestroyInstance();

	// Member Functions
	void InitializeAssets();
	GLuint GetTextureID(const char* _name) const;
	GLuint GetProgramID(const char* _name) const;

	void BindTexture(const char* _path, GLuint& _id);

private:
	// Make singleton by set the constructor inside private
	CAssetMgr();
	~CAssetMgr();

	// Make this class non-copyable
	CAssetMgr(const CAssetMgr& _kr) = delete;
	CAssetMgr& operator= (const CAssetMgr& _kr) = delete;

protected:
	// Singleton Object
	static CAssetMgr* s_pAssetMgr;

private:
	// Member Variables
	
	// Texture ID
	GLuint m_texTITANFALL;

	// Program ID
	GLuint m_programBlinnPhong;
	GLuint m_programModelBlinnPhong;
	GLuint m_programText;
};

#endif // !ASSETMGR_H