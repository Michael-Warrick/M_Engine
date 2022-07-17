#include "../headers/definitions.hpp"

class UI
{
public:
	void Init(GLFWwindow* window);
	void Prepare();
	void Render(GLuint colorTextureID);
	void Destroy();

private:
	string Shortcutter(string shortcut);
	void MenuBar();
	void SceneView(GLuint colorTextureID);
	void HierarchyView();
	void AssetBrowser();
	void FileManager();
	void Inspector();
};

