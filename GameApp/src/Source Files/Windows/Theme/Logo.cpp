#include "..\..\..\Header Files\Windows\Theme\Logo.h"


Logo::Logo(bool relativeToCamera)
{
	this->relative = relativeToCamera;
	regionDimension = Vector2f(0, 0);
	viewSize = Controller::getViewSize();
}

Logo::~Logo()
{
}

void Logo::clear()
{
	regionDimension = Vector2f(0, 0);
}

Vector2f Logo::renderRegion(Vector2f logo)
{
	Vector2f container = Vector2f(viewSize.x, viewSize.y*0.3f); // Set Region Container.
	regionDimension = logo;
	Vector2f position = Vector2f(ceil((container.x - logo.x) / 2), ceil(viewSize.y * 0.3f + regionDimension.y));
	if (relative) {
		return  position + Controller::getCameraOffset();
	}
	return  position;
}

Vector2f Logo::getRegionDimension()
{
	return regionDimension;
}
