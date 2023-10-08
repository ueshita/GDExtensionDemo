#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class SpriteCpp : public Sprite2D
{
    GDCLASS(SpriteCpp, Sprite2D)

public:
    static void _bind_methods();

public:
	SpriteCpp() = default;
    virtual ~SpriteCpp() = default;

	void _process(float delta);

    void set_velocity(Vector2 _velocity) { velocity = _velocity; }

    Vector2 get_velocity() const { return velocity; }

private:
    Vector2 velocity = {0.0f, 0.0f};
};

}
