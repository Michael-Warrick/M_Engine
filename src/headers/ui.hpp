#include "../headers/definitions.hpp"

class UI
{
public:
	void Init(GLFWwindow* window);
	void Prepare();
	void Render();
	void Destroy();
private:
	void MenuBar();
	void SceneView();
	void HierarchyView();
	void AssetBrowser();
	void FileManager();
	void Inspector();
};
