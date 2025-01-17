#pragma once

#include "ECS/entitiesTemplateStorage.hpp"
#include "ECS/systemsQueue.hpp"
#include "Scenes/sceneManager.hpp"
#include "AI/aiManager.hpp"

namespace ph{

void parseScene(EntitiesTemplateStorage&, entt::registry&,
                const std::string& sceneFileName, SystemsQueue&, AIManager&, SceneManager&);

}

