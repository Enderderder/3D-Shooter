/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : ModelMgr.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#ifndef MODELMGR_H
#define MODELMGR_H

// Forward Declare
class CModel;

// Enum Declare
enum EMODEL
{
	TANK,
};

class CModelMgr
{
public:
	// Singleton Methods
	static CModelMgr* GetInstance();
	static void DestroyInstance();

	// Member Functions
	void InitializeModels();
	CModel* GetMesh(EMODEL) const;

private:
	// Make singleton by set the constructor inside private
	CModelMgr();
	~CModelMgr();

	// Make this class non-copyable
	CModelMgr(const CModelMgr& _kr) = delete;
	CModelMgr& operator= (const CModelMgr& _kr) = delete;

protected:
	// Singleton Object
	static CModelMgr* s_pModelMgr;

private:
	CModel* m_cTankModel;

};

#endif // !MODELMGR_H