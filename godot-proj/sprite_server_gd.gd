extends Node2D

@export var spawn: bool = false

class ServerSpriteGD extends RefCounted:
	var rid: RID
	var position: Vector2
	var velocity: Vector2

var angle = 0.0
var texture = preload("res://icon.svg")
var sprites: Array[ServerSpriteGD] = []

func _process(delta: float) -> void:
	if spawn:	
		# Spawn phase
		for i in range(10):
			var sprite = ServerSpriteGD.new()
			sprite.rid = RenderingServer.canvas_item_create()
			RenderingServer.canvas_item_set_parent(sprite.rid, get_canvas_item())
			RenderingServer.canvas_item_set_draw_index(sprite.rid, len(sprites))
			var rect = Rect2(0, 0, texture.get_width(), texture.get_height())
			RenderingServer.canvas_item_add_texture_rect(sprite.rid, rect, texture.get_rid())

			var speed = 200
			var direction = angle + i * (deg_to_rad(360)) / 10
			sprite.position = Vector2(640, 360)
			sprite.velocity = Vector2(cos(direction), sin(direction)) * speed
			sprites.append(sprite)
		angle += deg_to_rad(2)

	# Update phase
	for sprite in sprites:
		sprite.position += sprite.velocity * delta
		if sprite.position.x < 0.0:
			sprite.velocity.x = -sprite.velocity.x
		elif sprite.position.x > 1280.0:
			sprite.velocity.x = -sprite.velocity.x
		if sprite.position.y < 0.0:
			sprite.velocity.y = -sprite.velocity.y
		elif sprite.position.y > 720.0:
			sprite.velocity.y = -sprite.velocity.y

		var sprite_transform = Transform2D(0.0, Vector2(0.25, 0.25), 0.0, sprite.position)
		RenderingServer.canvas_item_set_transform(sprite.rid, sprite_transform)

func clear() -> void:
	for sprite in sprites:
		RenderingServer.free_rid(sprite.rid)
	sprites.clear()

func get_count() -> int:
	return len(sprites)
