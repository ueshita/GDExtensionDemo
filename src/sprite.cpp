#include "sprite.h"

namespace godot {

void SpriteCpp::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_velocity", "velocity"), &SpriteCpp::set_velocity);
	ClassDB::bind_method(D_METHOD("get_velocity"), &SpriteCpp::get_velocity);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "velocity"), "set_velocity", "get_velocity");
}

void SpriteCpp::_process(float delta)
{
    Vector2 position = get_position();
	position += velocity * delta;
    set_position(position);

	if (position.x < 0.0) {
		velocity.x = -velocity.x;
    } else if (position.x > 1280.0) {
		velocity.x = -velocity.x;
    }
	if (position.y < 0.0) {
		velocity.y = -velocity.y;
    } else if (position.y > 720.0) {
		velocity.y = -velocity.y;
    }
}

}
