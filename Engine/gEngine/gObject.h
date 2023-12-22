#pragma once

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "gCore.h"
#include "Engine/gEngine/gEngineCommon.h"
#include "gModel.h"
#include <glm/glm.hpp>
#include <fstream>
#include "iostream"
#include <filesystem>
#include <vector>

class ENGINE_API SceneObject {
public:

    SceneObject();

    ~SceneObject();

    SceneObject(Model model);
       
    void setPosition(const glm::vec3& pos);

    glm::vec3 getPosition() const;

    void setRotation(const glm::vec3& rot);

    glm::vec3 getRotation() const;

    void setScale(const glm::vec3& s);

    glm::vec3 getScale() const;

    glm::mat4 getTransform() const;

    std::vector<SceneObject> objects;

    void AddObject(const SceneObject& object);

    void Draw(Camera& camera, int SCR_WIDTH, int SCR_HEIGHT);
   
    template <typename ShaderType = Shader>

    void Draw(Camera& camera, int SCR_WIDTH, int SCR_HEIGHT, Shader& shader = modelShader);

    bool hasMeshes() const;

    void setHighlightColor(const glm::vec4& color);

    glm::vec4 getHighlightColor() const;

    void setTextureOffsetX(const float moveX);

    float getTextureOffsetX() const;

    void setTextureOffsetY(const float moveY);

    float getTextureOffsetY() const;

    void setTextureScale(const float scale);

    float getTextureScale() const;

    Model model;

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
    glm::vec3 BaseColor;
   
    std::string ObjectName;
    Shader modelShader;
    Shader  sipmleDepthShader;

    int ObjectID;

    void setObjectName(const std::string& name);

    void setObjectID(const int& ID);

    const std::string& getObjectName() const;

    const int& getObjectID() const;

    std::string getObjectInfo() const;

    glm::mat4 getModelMatrix() const;

    void setMeshTextures(unsigned int newTextureID);


private:

    glm::vec4 HighlightColor;
    float TextureOffsetX;
    float TextureOffsetY;
    float TextureScale;
};

#endif SCENE_OBJECT_H


#ifndef SCENE_H
#define SCENE_H


class ENGINE_API Scene {
public:

    Scene();

    ~Scene();

    std::vector<SceneObject> objects;

    void AddObject(const SceneObject& object);

    void LogSceneObjectsInfo() const;

    static Scene& Instance();


};


#endif SCENE_

template<typename ShaderType>

inline void SceneObject::Draw(Camera& camera, int SCR_WIDTH, int SCR_HEIGHT, Shader& shader)
{
    

        camera.projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 modelMat = getTransform();

        shader.use();
        shader.setMat4("projection", camera.projection);
        shader.setMat4("view", view);
        shader.setMat4("model", modelMat);
        shader.setVec4("highlightColor", HighlightColor);
        shader.setVec3("baseColor", BaseColor);

        glm::mat4 transform = getTransform();
        shader.setMat4("model", transform);
        shader.setFloat("offsetX", TextureOffsetX);
        shader.setFloat("offsetY", TextureOffsetY);
        shader.setFloat("textureScale", TextureScale);

        //  LOG.Log(Logger::LogLevel::DEBUG, "TextureOffset", getTextureOffsetX());

        model.Draw(shader);


    
}
