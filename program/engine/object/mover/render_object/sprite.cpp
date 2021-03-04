#include "../../../screen.h"
#include "../camera2d.h"
#include "sprite.h"


namespace dxe {

	void Sprite::render(std::shared_ptr<Screen> screen) {
		setBlendMode();

		t2k::Transform t = getWorldTransform();
		t2k::Transform ct = screen->getCamera2D()->getWorldTransform();
		float crs = screen->getCamera2D()->render_scale_;
		int sw = screen->getWidth() >> 1;
		int sh = screen->getHeight() >> 1;
		int rx = sw + (int)((t.position_.x - ct.position_.x * render_position_from_camera_) * crs);
		int ry = sh + (int)((t.position_.y - ct.position_.y * render_position_from_camera_) * crs);
		float scl = t.scale_ * crs;
		if (is_flip_x_) t.rotation_ += t2k::toRadian(180);

		// スクリーン範囲外ならば描画しない
		if (!t2k::isIntersectRect(t2k::Vector3((float)rx, (float)ry, 0), (int)(texture_->getWidth() * scl), (int)(texture_->getHeight() * scl), screen->getPosition() + t2k::Vector3((float)sw, (float)sh, 0), sw << 1, sh << 1)) return;

		DrawRotaGraph(rx, ry, scl, t.rotation_, texture_->getImage(), true, is_flip_x_ ^ is_flip_y_);
	}

	Sprite::SharedPtr Sprite::createFromTexture(t2k::Texture::SharedPtr texture) {
		Sprite::SharedPtr ptr = Sprite::create<Sprite>();
		ptr->texture_ = texture;
		return ptr;
	}

	Sprite::SharedPtr Sprite::createFromFile(const std::string& file_path) {
		Sprite::SharedPtr ptr = Sprite::create<Sprite>();
		ptr->texture_ = t2k::Texture::createFromFile(file_path);
		return ptr;
	}

}
