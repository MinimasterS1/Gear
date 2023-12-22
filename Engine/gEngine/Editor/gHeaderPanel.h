#pragma once


#include "gEditor.h"
#include "Engine/gEngine/gObject.h"
#include "gContentBorwser.h"

class ENGINE_API HeaderPanel : public EditorAPI

{

public:

	void DrawHeaderPanel();

	enum SelectedTab {
		NONE,
		LEVEL,
		MATERIAL,
		PARTICLE,
		ANIMATION
	};

	SelectedTab currentTab = LEVEL;


	enum FileType {
		FILE_PART,
		FILE_LVL,
		FILE_MAT,

	};

	FileType currentFileType = FILE_PART;

	SelectedTab GetCurrentTab() const {
		return currentTab;
	}


	void SetCurrentTab(SelectedTab tab);

private:

	bool ShowLoadFileDialog = false;
	bool ShowSaveFileDialog = false;




};