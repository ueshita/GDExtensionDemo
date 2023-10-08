extends Node2D

@export var spawn: bool = false
var angle = 0.0
var sprites: Array[SpriteGD] = []

func _process(_delta: float) -> void:
	if spawn:
		for i in range(10):
			var sprite: SpriteGD = SpriteGD.new()
			sprite.texture = preload("res://icon.svg")
			sprite.scale = Vector2(0.25, 0.25)
			
			var speed = 200
			var direction = angle + i * (deg_to_rad(360)) / 10
			sprite.position = Vector2(640, 360)
			sprite.velocity = Vector2(cos(direction), sin(direction)) * speed
			add_child(sprite)
			sprites.append(sprite)
		angle += deg_to_rad(2)

func clear() -> void:
	for sprite in sprites:
		sprite.queue_free()
	sprites.clear()

func get_count() -> int:
	return len(sprites)
