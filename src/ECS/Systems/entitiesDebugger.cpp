#include "pch.hpp"
#include "entitiesDebugger.hpp"
#include "ECS/Components/aiComponents.hpp"
#include "ECS/Components/charactersComponents.hpp"
#include "ECS/Components/graphicsComponents.hpp"
#include "ECS/Components/physicsComponents.hpp"
#include "ECS/Components/debugComponents.hpp"
#include "ECS/Components/objectsComponents.hpp"

// NOTE:
// This code is strictly exploratory and it lacks most of components
// Later we'll probably generate this code 
// by doing metaprogramming prepass on components

extern bool debugWindowOpen;

namespace ph::system {

void EntitiesDebugger::update(float dt)
{
	if(debugWindowOpen && ImGui::BeginTabItem("entities debugger"))
	{
		ImGui::BeginChild("entities:", ImVec2(300, 0), true);
		mRegistry.each([this](auto entity)
		{
			char label[50];
			if(const auto* debugName = mRegistry.try_get<component::DebugName>(entity))
			{
				sprintf(label, "%u - %s", entity, debugName->name);
			}
			else
			{
				sprintf(label, "%u", entity);
			}

			if(ImGui::Selectable(label, mSelected == entity))
			{
				mSelected = entity;
			}
		});
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("components view");
		ImGui::Text("Components view:");

		if(mRegistry.valid(mSelected))
		{
			if(const auto* zombie = mRegistry.try_get<component::Zombie>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("Zombie:");
				ImGui::Text("pathmode: (view is not supported)");
				ImGui::Text("currentDirectionVector: %f, %f", zombie->currentDirectionVector.x, zombie->currentDirectionVector.y);
				ImGui::Text("timeFromStartingThisMove: %f", zombie->timeFromStartingThisMove);
				ImGui::Text("timeFromLastGrowl: %f", zombie->timeFromLastGrowl);
				ImGui::Text("timeToMoveToAnotherTile: %f", zombie->timeToMoveToAnotherTile);
			}

			if(const auto* slowZombieBehaviour = mRegistry.try_get<component::SlowZombieBehavior>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("SlowZombieBehavior:");
				ImGui::Text("coolDownTime: %f", slowZombieBehaviour->coolDownTime);
			}

			if(const auto* health = mRegistry.try_get<component::Health>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("Health:");
				ImGui::Text("healthPoints: %f", health->healthPoints);
				ImGui::Text("maxHealthPoints: %f", health->maxHealthPoints);
			}

			if(mRegistry.has<component::Player>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("Player");
			}

			if(const auto* rq = mRegistry.try_get<component::RenderQuad>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("RenderQuad:");
				ImGui::Text("texture: %p", rq->texture);
				ImGui::Text("shader: %p", rq->shader);
				ImGui::Text("rotation origin: %f, %f", rq->rotationOrigin.x, rq->rotationOrigin.y);
				ImGui::Text("color: %u, %u, %u, %u", rq->color.r, rq->color.g, rq->color.b, rq->color.a);
				ImGui::Text("rotation: %f", rq->rotation);
				ImGui::Text("z: %u", rq->z);
			}

			if(const auto* tr = mRegistry.try_get<component::TextureRect>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("TextureRect %i, %i, %i, %i", tr->x, tr->y, tr->w, tr->h);
			}

			if(const auto* grc = mRegistry.try_get<component::GroundRenderChunk>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("GroundRenderChunk");
				ImGui::Text("bounds: %f, %f, %f, %f", grc->bounds.x, grc->bounds.y, grc->bounds.w, grc->bounds.h);
				ImGui::Text("textureRect: %f, %f, %f, %f", grc->textureRect.x, grc->textureRect.y, grc->textureRect.w, grc->textureRect.h);
				ImGui::Text("z: %u", grc->z);
			}

			if(const auto* rc = mRegistry.try_get<component::RenderChunk>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("RenderChunk");
				ImGui::Text("quads: (view is not supported)");
				ImGui::Text("lightWalls: (view is not supported)");
				ImGui::Text("quadsBounds: %f, %f, %f, %f", rc->quadsBounds.x, rc->quadsBounds.y, rc->quadsBounds.w, rc->quadsBounds.h);
				ImGui::Text("lightWallsBounds: %f, %f, %f, %f", rc->lightWallsBounds.x, rc->lightWallsBounds.y, rc->lightWallsBounds.w, rc->lightWallsBounds.h);
				ImGui::Text("z: %u", rc->z);
				ImGui::Text("rendererID: %u", rc->rendererID);
			}

			if(const auto* io = mRegistry.try_get<component::IndoorOutdoorBlend>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("IndoorOutdoorBlend");
				ImGui::Text("outdoor: %f", io->outdoor);
				ImGui::Text("outdoorDarkness: %f", io->outdoorDarkness);
				ImGui::Text("indoorAlpha: %f", io->indoorAlpha);
			}

			if(const auto* ob = mRegistry.try_get<component::OutdoorBlend>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("OutdoorBlend");
				ImGui::Text("darkness: %f", ob->darkness);
			}

			if(const auto* ib = mRegistry.try_get<component::IndoorBlend>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("IndoorBlend");
				ImGui::Text("alpha: %f", ib->alpha);
			}

			if(const auto* br = mRegistry.try_get<component::BodyRect>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("BodyRecy");
				ImGui::Text("pos: %f, %f", br->x, br->y);
				ImGui::Text("size: %f, %f", br->w, br->h);
			}

			if(const auto* kin = mRegistry.try_get<component::Kinematics>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("Kinematics");
				ImGui::Text("vel: %f %f", kin->vel.x, kin->vel.y);
				ImGui::Text("acceleration: %f %f", kin->acceleration.x, kin->acceleration.y);
				ImGui::Text("friction: %f", kin->friction);
				ImGui::Text("defaultFriction: %f", kin->defaultFriction);
				ImGui::Text("frictionLerpSpeed: %f", kin->frictionLerpSpeed);
			}

			if(const auto* cs = mRegistry.try_get<component::CharacterSpeed>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("CharacterSpeed");
				ImGui::Text("speed: ", cs->speed);
			}
			
			if(mRegistry.has<component::StaticCollisionBody>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("StaticCollisionBody");
			}

			if(const auto* mscb = mRegistry.try_get<component::MultiStaticCollisionBody>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("MultiStaticCollisionBody");
				ImGui::Text("rects: (view is not supprted)");
				ImGui::Text("sharedBounds: %f, %f, %f, %f", mscb->sharedBounds.x, mscb->sharedBounds.y, mscb->sharedBounds.w, mscb->sharedBounds.h);
			}

			if(const auto* kcb = mRegistry.try_get<component::KinematicCollisionBody>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("KinematicCollisionBody");
				ImGui::Text("mass: %f", kcb->mass);
				ImGui::Text("staticallyMovedUp: %i", kcb->staticallyMovedUp);
				ImGui::Text("staticallyMovedDown: %i", kcb->staticallyMovedDown);
				ImGui::Text("staticallyMovedLeft: %i", kcb->staticallyMovedLeft);
				ImGui::Text("staticallyMovedRight: %i", kcb->staticallyMovedRight);
			}

			if(const auto* ioba = mRegistry.try_get<component::IndoorOutdoorBlendArea>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("IndoorOutdoorBlendArea");
				using component::IndoorOutdoorBlendArea;
				switch(ioba->exit)
				{
					case IndoorOutdoorBlendArea::Left: ImGui::Text("exit: Left"); break;
					case IndoorOutdoorBlendArea::Right: ImGui::Text("exit: Right"); break;
					case IndoorOutdoorBlendArea::Top: ImGui::Text("exit: Top"); break;
					case IndoorOutdoorBlendArea::Down: ImGui::Text("exit: Down"); break;
					default: ImGui::Text("exit: Error!!! (you probably just didn't click checkbox in tiled)");
				}
			}

			if(const auto* gate = mRegistry.try_get<component::Gate>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("Gate");
				ImGui::Text("id: %u", gate->id);
				ImGui::Text("previouslyOpen: %u", gate->previouslyOpen);
				ImGui::Text("open: %u", gate->open);
			}

			if(const auto* pressurePlate = mRegistry.try_get<component::PressurePlate>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("PressurePlate");
				ImGui::Text("puzzleId: %u", pressurePlate->puzzleId);
				ImGui::Text("id: %u", pressurePlate->id);
				ImGui::Text("isPressed: %u", pressurePlate->isPressed);
			}

			if(const auto* p = mRegistry.try_get<component::Puzzle>(mSelected))
			{
				ImGui::Separator();
				ImGui::BulletText("Puzzle");
				ImGui::Text("id: %u", p->id); 
			}
		}

		ImGui::EndChild();
		ImGui::EndTabItem();
	}
}

}