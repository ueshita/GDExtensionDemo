extends Sprite2D
class_name SpriteGD

var velocity := Vector2(0.0, 0.0)

func _process(delta: float) -> void:
	position += velocity * delta
	if position.x < 0.0:
		velocity.x = -velocity.x
	elif position.x > 1280.0:
		velocity.x = -velocity.x
	if position.y < 0.0:
		velocity.y = -velocity.y
	elif position.y > 720.0:
		velocity.y = -velocity.y
