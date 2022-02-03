#include "../headers/definitions.hpp"

class UI
{
public:
	void Init(GLFWwindow* window);
	void Prepare();
	void MenuBar();
	void SceneView();
	void Render();
	void Destroy();
private:
	void HierarchyView();
	void AssetBrowser();
	void FileManager();
	void Inspector();
};

