#include "Bullet.h"

Bullet::Bullet(float _posX, float _posY, float _moveDirX, float _moveDirY, float _moveSpeed)
{
	bullet.setRadius(5);
	moveDirection.x = _moveDirX;
	moveDirection.y = _moveDirY;
	moveSpeed = _moveSpeed;
	bullet.setPosition(_posX, _posY);
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::GetBounds() const
{
	return bullet.getGlobalBounds();
}

void Bullet::Update()
{
	bullet.move(moveSpeed * moveDirection);
}

void Bullet::Render(sf::RenderTarget* _window)
{
	_window->draw(bullet);
}
