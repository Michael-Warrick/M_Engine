#include "view.hpp"

void UIView::NavigationBar() 
{
	if (BeginMainMenuBar)
	{
		if (BeginMenu("File"))
		{

			EndMenu();
		}

		if (BeginMenu("Edit"))
		{

			EndMenu();
		}

		if (BeginMenu("Assets"))
		{

			EndMenu();
		}

		if (BeginMenu("GameObject"))
		{

			EndMenu();
		}

		if (BeginMenu("Component"))
		{

			EndMenu();
		}

		if (BeginMenu("View"))
		{

			EndMenu();
		}

		if (Begin("Tools"))
		{

			EndMenu();
		}

		EndMainMenuBar();
	}
}