#include "sample_scene.h"


void SampleScene::initialize() {

	dxe::DxEngine& engine = dxe::DxEngine::getInstance();

	dxe::Camera2D::SharedPtr main_camera = dxe::Camera2D::create<dxe::Camera2D>();
	main_screen_ = createScreenToScene("main_screen", main_camera, engine.getWindowWidth(), engine.getWindowHeight() - 64);

	dxe::CollisionObject::create<dxe::CollisionObject>()->addCollisionRect("rect", dxe::CollisionRect::create(500, 32, t2k::Vector3(0, 200, 0)));

	dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(32, 32);
	rect->is_correct_ = true;
	rect->correct_space_.up_ = 0.0f;
	player_ = dxe::PhysicsObject::create<dxe::PhysicsObject>();
	player_->addCollisionRect("rect", rect);

	dxe::Sprite::createFromFile("graphics/test.jpg")->render_position_from_camera_ = 0.5f;

	dxe::AnimationSprite::SharedPtr anim = dxe::AnimationSprite::create<dxe::AnimationSprite>();
	anim->registAnimation("down", t2k::Texture::createVectorFromFile("graphics/c1_anim_down.png", 4, 4, 1, 32, 48));
	anim->play("down", 1.0f, true);

	player_->pushChild(anim);

	rect_renderer_ = dxe::RectRenderer::create(100, 100, t2k::Color());

}

void SampleScene::lateUpdate() {

	rect_renderer_->transform_.rotation_ += t2k::toRadian(1);

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_H)) {
		dxe::CollisionManager::getInstance().is_render_debug_area_ ^= true;
	}

	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_C)) {
		main_screen_->getCamera2D()->render_scale_ += 0.01f;
	}
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_X)) {
		main_screen_->getCamera2D()->render_scale_ -= 0.01f;
	}

	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_W)) {
		main_screen_->getCamera2D()->transform_.position_ += (t2k::Vector3::UP * 5);
	}
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_S)) {
		main_screen_->getCamera2D()->transform_.position_ += (t2k::Vector3::DOWN * 5);
	}
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_A)) {
		main_screen_->getCamera2D()->transform_.position_ += (t2k::Vector3::LEFT * 5);
	}
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_D)) {
		main_screen_->getCamera2D()->transform_.position_ += (t2k::Vector3::RIGHT * 5);
	}

	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_UP)) {
		player_->addForceFrame(t2k::Vector3::UP * 5);
	}
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_LEFT)) {
		player_->addForceTime(t2k::Vector3::LEFT * 50);
	}
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_RIGHT)) {
		player_->addForceTime(t2k::Vector3::RIGHT * 50);
	}

}
