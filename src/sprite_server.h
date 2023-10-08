#include <vector>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/texture.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/rid.hpp>

namespace godot {

class SpriteServerCpp : public Node2D
{
    GDCLASS(SpriteServerCpp, Node2D)

public:
    static void _bind_methods();

public:
	SpriteServerCpp();
    virtual ~SpriteServerCpp();

	void _ready();

	void _process(float delta);

    void clear();

    struct ServerSpriteCpp {
        RID rid;
        Vector2 position = {0.0f, 0.0f};
        Vector2 velocity = {0.0f, 0.0f};
    };

    int get_count() const { return (int)sprites.size(); }
    void set_spawn(bool value) { spawn = value; }
    bool get_spawn() const { return spawn; }

private:
    bool spawn = false;
    float angle = 0.0f;
    Ref<Texture2D> texture;
    std::vector<ServerSpriteCpp> sprites;
};

}
