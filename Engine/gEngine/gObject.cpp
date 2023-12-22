#include "gObject.h"

SceneObject::SceneObject()
{

}

SceneObject::~SceneObject()
{

}

SceneObject::SceneObject(Model model): model(model), Position(0.0f), Rotation(0.0f), Scale(1.0f), HighlightColor(1.0f, 1.0f, 1.0f, 1.0f),
    BaseColor(0.0f, 0.0f, 1.0f), TextureOffsetX(0.0f), TextureOffsetY(0.0f), TextureScale(1.0f)
{
    modelShader = Shader("../Shaders/model_load_vs.vs", "../Shaders/model_load_fs.fs");
    
}

void SceneObject::setPosition(const glm::vec3& pos) { { Position = pos; } }

glm::vec3 SceneObject::getPosition() const{ { return Position; } }

void SceneObject::setRotation(const glm::vec3& rot) { { Rotation = rot; } }

glm::vec3 SceneObject::getRotation() const { { return Rotation; } }

void SceneObject::setScale(const glm::vec3& s) { { Scale = s; } }

glm::vec3 SceneObject::getScale() const { { return Scale; } }

glm::mat4 SceneObject::getTransform() const {  glm::mat4 transform = glm::mat4(1.0f); transform = glm::translate(transform, Position);
                                                    transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
                                                    transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
                                                    transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
                                                    transform = glm::scale(transform, Scale);

                                                return transform;
    
}

void SceneObject::AddObject(const SceneObject& object) { objects.push_back(object); }

void SceneObject::Draw(Camera& camera, int SCR_WIDTH, int SCR_HEIGHT) { Draw(camera, SCR_WIDTH, SCR_HEIGHT, modelShader); }

void SceneObject::setObjectName(const std::string& name) { ObjectName = name; }

void SceneObject::setObjectID(const int& ID) { ObjectID = ID; }

const std::string& SceneObject::getObjectName() const { return ObjectName; }

const int& SceneObject::getObjectID() const { return ObjectID; }

std::string SceneObject::getObjectInfo() const
{
  std::string objectInfo = "Object: " + ObjectName + "\n" +
   "Position: (" + std::to_string(Position.x) + ", " +
    std::to_string(Position.y) + ", " +
      std::to_string(Position.z) + ")\n" +
       "Rotation: (" + std::to_string(Rotation.x) + ", " +
        std::to_string(Rotation.y) + ", " +
         std::to_string(Rotation.z) + ")\n" +
         "Scale: (" + std::to_string(Scale.x) + ", " +
          std::to_string(Scale.y) + ", " +
          std::to_string(Scale.z) + ")";
   return objectInfo;
   
}

glm::mat4 SceneObject::getModelMatrix() const { return getTransform(); }

void SceneObject::setMeshTextures(unsigned int newTextureID)
{
    if (hasMeshes()) 
    {
        std::vector<Texture> newTextures;
        newTextures.push_back(Texture{ newTextureID, "TextureType" });
        model.setMeshTextures(newTextures);
      }

}

bool SceneObject::hasMeshes() const { return !model.meshes.empty(); }

void SceneObject::setHighlightColor(const glm::vec4& color) { HighlightColor = color; }
    
glm::vec4 SceneObject::getHighlightColor() const { return HighlightColor; }
   
void SceneObject::setTextureOffsetX(const float moveX) { TextureOffsetX = moveX; }
   
float SceneObject::getTextureOffsetX() const { return TextureOffsetX; }

void SceneObject::setTextureOffsetY(const float moveY) { TextureOffsetY = moveY; }
   
float SceneObject::getTextureOffsetY() const { return TextureOffsetY; }
    
void SceneObject::setTextureScale(const float scale) { TextureScale = scale; }
   
float SceneObject::getTextureScale() const { return TextureScale; }
  
/// //////////////////////////////////////////////////////////////////

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::AddObject(const SceneObject& object) { objects.push_back(object); }

void Scene::LogSceneObjectsInfo() const { for (const SceneObject& object : objects) { std::string objectInfo = object.getObjectInfo(); LOG.Log(Logger::LogLevel::Save, objectInfo.c_str(), NULL); } }
    
Scene& Scene::Instance()
{
   
        static Scene instance;
        return instance;
 
}
