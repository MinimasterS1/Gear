#include "gLists.h"

int ObjectList::getModelIndex() const
{
    return ModelIndex;
}

void ObjectList::setModelIndex(int index)
{
    
    if (index >= 0 && index < loadedModels.size()) 
    {
       ModelIndex = index;
    }
    
}

