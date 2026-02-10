#include "kengine/systems/character_animation.hpp"
#include <string>
#include <type_traits>
#include "entt/entity/group.hpp"
#include "entt/entity/storage.hpp"
#include "entt/entity/utility.hpp"
#include "kengine/components/character_animation.hpp"
#include "kengine/components/body2d.hpp"
#include "kengine/components/animation_player.hpp"
#include "kengine/topdown/body.hpp"

namespace kengine
{
namespace system
{
  CharacterAnimation::CharacterAnimation() {}

  void CharacterAnimation::update (entt::registry& registry, const double dt)
  {
    registry.group<component::CharacterAnimation> (entt::get<component::Body2D, component::AnimationPlayer>)
        .each ([this, &registry] (auto entity, auto& char_anim, auto& body, auto& anim) {
          std::string animation_name = "";
          switch (body.Body->state)
          {
            case kengine::topdown::BodyState::IDLE:
              animation_name.append ("idle-");
              break;
            case kengine::topdown::BodyState::MOVING:
              animation_name.append ("walking-");
              break;
            default:
              break;
          }

          // If we have defined a animation (BodyState is IDLE or MOVING)
          if (!animation_name.empty())
          {
            if (body.Body->direction & kengine::topdown::BodyDirection::LEFT)
            {
              animation_name.append (1, 'l');
            }
            else if (body.Body->direction & kengine::topdown::BodyDirection::RIGHT)
            {
              animation_name.append (1, 'r');
            }
            else if (body.Body->direction & kengine::topdown::BodyDirection::TOP)
            {
              animation_name.append (1, 't');
            }
            else if (body.Body->direction & kengine::topdown::BodyDirection::BOTTOM)
            {
              animation_name.append (1, 'b');
            }
            anim.current = animation_name;
          }
        });
  }
} // namespace system
} // namespace kengine