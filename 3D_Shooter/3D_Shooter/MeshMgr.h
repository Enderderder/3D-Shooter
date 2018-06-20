//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : MeshMgr.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

#ifndef MESHMGR_H
#define MESHMGR_H

// Forward Declare
class CMesh;
class CCubeMap;

// Enum Declare
enum EMESH
{
	CUBE,
	SPHERE,
	MENUCUBEMAP,
	GAMECUBEMAP
};

class CMeshMgr
{
public:
	// Singleton Methods
	static CMeshMgr* GetInstance();
	static void DestroyInstance();

	// Member Functions
	void InitializeMeshes();
	CMesh* GetMesh(EMESH) const;
	CCubeMap* GetCubeMap(EMESH) const;

private:
	// Make singleton by set the constructor inside private
	CMeshMgr();
	~CMeshMgr();

	// Make this class non-copyable
	CMeshMgr(const CMeshMgr& _kr) = delete;
	CMeshMgr& operator= (const CMeshMgr& _kr) = delete;

protected:
	// Singleton Object
	static CMeshMgr* s_pMeshMgr;

private:
	CMesh* m_cCubeMesh;
	CMesh* m_cSphereMesh;

	CCubeMap* m_MenuCubeMap;
	CCubeMap* m_GameCubemap;
};

#endif // !MESHMGR_H