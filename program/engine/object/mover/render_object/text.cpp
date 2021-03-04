#include "../../../screen.h"
#include "../camera2d.h"
#include "text.h"


namespace dxe {

	void Text::render(std::shared_ptr<Screen> screen) {
		setBlendMode();
		SetFontSize(font_size_);

		t2k::Transform t = getWorldTransform();
		t2k::Transform ct = screen->getCamera2D()->getWorldTransform();
		float rate = render_position_from_camera_;
		int sw = screen->getWidth() >> 1;
		int sh = screen->getHeight() >> 1;
		int cx = sw + (int)(t.position_.x - ct.position_.x * rate);
		int cy = sh + (int)(t.position_.y - ct.position_.y * rate);
		unsigned int size = text_.size();
		
		for (unsigned int i = 0; i < size; ++i) {
			int length = GetDrawStringWidth(text_[i].c_str(), text_[i].length());
			// 揃えモードによって描画開始位置を変動
			int rx = 0;
			if (align_mode_x_ == AlignModeX::LEFT) {
				rx = cx;
			}
			else if (align_mode_x_ == AlignModeX::CENTER) {
				rx = cx - (length >> 1);
			}
			else if (align_mode_x_ == AlignModeX::RIGHT) {
				rx = cx - length;
			}
			int ry = 0;
			if (align_mode_y_ == AlignModeY::TOP) {
				ry = cy + (i * font_size_) + (i * interval_);
			}
			else if (align_mode_y_ == AlignModeY::MIDDLE) {
				ry = cy + (int)(-(font_size_ * size * 0.5f) - (interval_ * (size - 1) * 0.5f) + (i * font_size_) + (i * interval_));
			}
			else if (align_mode_y_ == AlignModeY::BOTTOM) {
				ry = cy + (-font_size_ * size) - (interval_ * (size - 1)) + (i * font_size_) + (i * interval_);
			}

			// Screen範囲外ならば描画しない
			t2k::Vector3 sp = screen->getPosition();
			if (!t2k::isIntersectRectPrimitive((int)(sp.x), (int)(sp.x + (sw << 1)), (int)(sp.y), (int)(sp.y + (sh << 1)), rx, rx + length, ry, ry + font_size_)) continue;

			DrawString(rx, ry, text_[i].c_str(), color_.toInt());
		}

	}
	
	Text::SharedPtr Text::create(const std::string& text) {
		Text::SharedPtr ptr = RenderObject::create<Text>();
		ptr->text_ = t2k::split(text, '\n');
		return ptr;
	}

	Text::SharedPtr Text::createFromFile(const std::string& file_path) {
		FILE* fp = nullptr;
		fopen_s(&fp, file_path.c_str(), "r");
		if (!fp) {
			warningMassage(("テキストファイルを開けませんでした : " + file_path).c_str());
			return nullptr;
		}
		Text::SharedPtr ptr = RenderObject::create<Text>();
		char buff[1024] = { 0 };
		while (fgets(buff, sizeof(buff), fp)) {
			std::string str = buff;
			if (str[str.length() - 1] == '\n') str = str.substr(0, str.length() - 1);
			ptr->text_.emplace_back(str);
			memset(buff, 0, sizeof(buff));
		}
		fclose(fp);
		return ptr;
	}

}
