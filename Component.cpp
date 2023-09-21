#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* gameObj)
{ 
	m_gameObj = gameObj; 
}
