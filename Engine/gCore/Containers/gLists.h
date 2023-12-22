#pragma once

#include "gCore.h"
#include "gModel.h"
#include "gLogger.h"

#include "vector" 

class CORE_API ObjectList {

public:



    ObjectList() = default;

    ~ObjectList() = default;

    ObjectList(const  ObjectList&) = delete;

    ObjectList& operator=(const  ObjectList&) = delete;


    int ModelIndex = -1;

    static  ObjectList& getInstance() {
        static  ObjectList instance;  
        return instance;
    }

    int getModelIndex() const;

    void setModelIndex(int index);

    


    std::vector<Model> loadedModels;
    std::vector<int> selectedModelIndices;
    std::vector<Model> displayedModels;
    std::string saveDirectory;



};