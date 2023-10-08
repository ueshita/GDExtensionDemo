#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "sprite_server.h"

namespace godot {

SpriteServerCpp::SpriteServerCpp()
{
}

SpriteServerCpp::~SpriteServerCpp()
{
	clear();
}

void SpriteServerCpp::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("clear"), &SpriteServerCpp::clear);
	ClassDB::bind_method(D_METHOD("get_count"), &SpriteServerCpp::get_count);
	ClassDB::bind_method(D_METHOD("set_spawn", "spawn"), &SpriteServerCpp::set_spawn);
	ClassDB::bind_method(D_METHOD("get_spawn"), &SpriteServerCpp::get_spawn);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "spawn"), "set_spawn", "get_spawn");
}

void SpriteServerCpp::_ready()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		set_process(false);
	}
	texture = ResourceLoader::get_singleton()->load("res://icon.svg");
}

void SpriteServerCpp::_process(float delta)
{
	auto rs = RenderingServer::get_singleton();

	if (spawn) {
		// Spawn phase
		for (int i = 0; i < 10; i++) {
			auto sprite = ServerSpriteCpp();
			sprite.rid = rs->canvas_item_create();
			rs->canvas_item_set_parent(sprite.rid, get_canvas_item());
			rs->canvas_item_set_draw_index(sprite.rid, (int)sprites.size());
			Rect2 rect = Rect2(0, 0, texture->get_width(), texture->get_height());
			rs->canvas_item_add_texture_rect(sprite.rid, rect, texture->get_rid());

			float speed = 200.0f;
			float direction = angle + i * (UtilityFunctions::deg_to_rad(360.0f)) / 10.0f;
			sprite.position = Vector2(640, 360);
			sprite.velocity = Vector2(cos(direction), sin(direction)) * speed;
			sprites.emplace_back(sprite);
		}
		angle += UtilityFunctions::deg_to_rad(2);
	}

	// Update phase
	for (auto& sprite : sprites) {
		sprite.position += sprite.velocity * delta;
		
		if (sprite.position.x < 0.0) {
			sprite.velocity.x = -sprite.velocity.x;
		} else if (sprite.position.x > 1280.0) {
			sprite.velocity.x = -sprite.velocity.x;
		}
		if (sprite.position.y < 0.0) {
			sprite.velocity.y = -sprite.velocity.y;
		} else if (sprite.position.y > 720.0) {
			sprite.velocity.y = -sprite.velocity.y;
		}

		Transform2D sprite_transform = Transform2D(0.0, Vector2(0.25, 0.25), 0.0, sprite.position);
		rs->canvas_item_set_transform(sprite.rid, sprite_transform);
	}
}

void SpriteServerCpp::clear()
{
	auto rs = RenderingServer::get_singleton();

	for (auto& sprite : sprites) {
		rs->free_rid(sprite.rid);
	}
	sprites.clear();
}

}
