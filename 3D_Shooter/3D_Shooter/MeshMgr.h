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

class CMeshMgr
{
public:
	// Singleton Methods
	static CMeshMgr& GetInstance();
	static void DestroyInstance();

	// Member Functions
	void InitialiseMeshes();
	CMesh* GetCubeMesh() const;


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
};

#endif // !MESHMGR_H