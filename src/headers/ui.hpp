#include "../headers/definitions.hpp"

class UI
{
public:
	void Init(GLFWwindow* window);
	void Prepare();
	void Render(unsigned int colorBuffer);
	void Destroy();

private:
	string Shortcutter(string shortcut);
	
	void MenuBar();
	void SceneView(unsigned int colorBuffer);
	void HierarchyView();
	void AssetBrowser();
	void FileManager();
	void Inspector();
};

