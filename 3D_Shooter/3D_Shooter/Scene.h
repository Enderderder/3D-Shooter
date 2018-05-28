#ifndef _SCENE_H
#define _SCENE_H

// Forward Declaration
enum ESCENES; 

class CScene
{
public:
	CScene() = default;
	CScene(ESCENES _eSceneNum);
	~CScene();

	void InitialiseScene();
	void RenderScene();
	void UpdateScene();
};

#endif // !_SCENE_H