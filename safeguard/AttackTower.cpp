#include "AttackTower.h"

using namespace sf;



std::shared_ptr<Entity> AttackTower::create_tower() {
	auto tower = Engine::GetActiveScene()->makeEntity();
	tower->addTag("attack_tower");
	auto spritec = tower->addComponent<SpriteComponent>();
	auto tex = Resources::get<Texture>("towers.png");
	spritec->setTexture(tex);
	spritec->getSprite().setTextureRect(sf::IntRect(13, 180, 50, 50));
	spritec->getSprite().setScale(sf::Vector2f(2.0f, 2.0f));

	
	return tower;	
}



std::shared_ptr<Entity> AttackTower::create_tower_bullet(Entity* tower, sf::Vector2f direction)
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addTag("bullet");

	//The bullet appears from the tower
	Vector2f pos = tower->getPosition() + sf::Vector2f(LevelSystem::getTileSize() / 2, LevelSystem::getTileSize() / 2);
	e->setPosition(pos);

	auto s = e->addComponent<SpriteComponent>(); //create the bullet sprite component

	auto tex1 = Resources::get<Texture>("enemies.png");

	s->setTexture(tex1);
	s->getSprite().setTextureRect(sf::IntRect(32 * 38, 32 * 22, 32, 32));
	s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

	auto p = e->addComponent<PhysicsComponent>(true, Vector2f(1.0f, 1.0f));
	p->getBody()->SetBullet(true);


	direction.y *= -1;
	auto b = e->addComponent<BulletComponent>(tower, direction, 1000.0f);
	b->setBulletAir(false);
	

	//reset the firerate back to the default fire rate
	_firerate = _baseFireRate;

	return e;

}

bool AttackTower::getShootsAirEnemies()
{
	return this->_shootsAirEnemies;
}

int AttackTower::getMaxUpgradeLevel()
{
	return this->_maxUpgradeLevel;
}

void AttackTower::visualUpgrade(std::shared_ptr<Entity> entity)
{
	if (this->_upgradeLevel == 2) {
		entity->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(sf::IntRect(59, 182, 50, 50));
	}
	else if (this->_upgradeLevel == 3) {
		entity->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(sf::IntRect(147, 182, 50, 50));
	}
	else if (this->_upgradeLevel == 4) {
		entity->get_components<SpriteComponent>()[0]->getSprite().setTextureRect(sf::IntRect(277, 182, 50, 50));
	}	
}
