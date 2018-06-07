#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes

#include "../Dependencies\glew\glew.h"
#include "../Dependencies\freeglut\freeglut.h"
#include "../Dependencies\soil\SOIL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\quaternion.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "ModelMesh.h"
#include "Camera.h"

class CModel
{
public:
	/*  Functions   */
	// Constructor, expects a filepath to a 3D model.
	CModel(std::string path);

	// Draws the model, and thus all its meshes
	void Render(CCamera* camera, GLuint _program);

private:
	/*  Model Data  */
	vector<ModelMesh> meshes;
	string directory;
	vector<MeshTexture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

	/*  Functions   */
	// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string path);

	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);

	ModelMesh processMesh(aiMesh* mesh, const aiScene* scene);

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	GLint TextureFromFile(const char* path, string directory);
};

