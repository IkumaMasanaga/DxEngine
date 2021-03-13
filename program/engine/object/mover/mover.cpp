#include "mover.h"


namespace dxe {

	bool Mover::isExistence(Mover::SharedPtr transform) const {
		Mover::SharedPtr check = getChild(0);
		if (!check) return false;
		if (check == transform) return true;
		if (check->isExistence(transform)) return true;
		check = check->getNext();
		if (!check) return false;
		if (check == transform) return true;
		return check->isExistence(transform);
	}

	Mover::SharedPtr Mover::getFront() {
		if (!getPrev()) return std::dynamic_pointer_cast<Mover>(shared_from_this());
		return getPrev()->getFront();
	}

	Mover::SharedPtr Mover::getBack() {
		if (!getNext()) return std::dynamic_pointer_cast<Mover>(shared_from_this());
		return getNext()->getBack();
	}

	Mover::SharedPtr Mover::getChild(const int count) const {
		if (child_.expired()) return nullptr;
		Mover::SharedPtr ptr = child_.lock();
		for (int i = 0; i < count; ++i) {
			if (!ptr) return nullptr;
			ptr = ptr->getNext();
		}
		return ptr;
	}

	int Mover::getChildCount() const {
		if (child_.expired()) return 0;
		Mover::SharedPtr ptr = child_.lock();
		int ret = 0;
		while (ptr) {
			ptr = ptr->getNext();
			++ret;
		}
		return ret;
	}

	void Mover::setWorldTransform(const t2k::Vector3& position, const float rotation, const float scale) {
		if (!getParent()) {
			transform_.position_ = position;
			transform_.rotation_ = rotation;
			transform_.scale_ = scale;
			return;
		}
		t2k::Transform wt = getWorldTransform();
		transform_.scale_ = scale / wt.scale_;
		transform_.rotation_ = rotation - wt.rotation_;
		transform_.position_ += toLocalPosition(position - wt.position_);
	}

	t2k::Transform Mover::getWorldTransform() const {
		if (!getParent()) return transform_;
		t2k::Transform ret;
		t2k::Transform pt = parent_.lock()->getWorldTransform();
		ret.position_ = pt.position_ + (t2k::Matrix::getRelativePosition(transform_.position_, pt.rotation_) * pt.scale_);
		ret.rotation_ = pt.rotation_ + transform_.rotation_;
		ret.scale_ = pt.scale_ * transform_.scale_;
		return ret;
	}

	t2k::Vector3 Mover::toLocalPosition(const t2k::Vector3& world_position) {
		if (!getParent()) return world_position;
		return t2k::Matrix::getRelativePosition(parent_.lock()->toLocalPosition(world_position), -parent_.lock()->transform_.rotation_) / parent_.lock()->transform_.scale_;
	}

	void Mover::pushChild(Mover::SharedPtr child) {
		Mover::SharedPtr m = std::dynamic_pointer_cast<Mover>(shared_from_this());
		if (child->isExistence(m)) {
			warningMassage("’Ç‰Á‚µ‚æ‚¤‚Æ‚µ‚½Transform‚ÌŽq‹Ÿ‚ÉŽ©g‚ª‘¶Ý‚µ‚Ä‚¢‚Ü‚·");
			return;
		}
		child->popParent();
		child->transform_.position_ = t2k::Matrix::getRelativePosition(child->transform_.position_ - transform_.position_, -transform_.rotation_) / transform_.scale_;
		child->transform_.rotation_ -= transform_.rotation_;
		child->transform_.scale_ /= transform_.scale_;
		child->parent_ = m;
		if (getChild(0)) {
			child->prev_ = child_.lock()->getBack();
			child_.lock()->getBack()->next_ = child;
		}
		else {
			child_ = child;
		}
	}

	void Mover::popParent() {
		Mover::SharedPtr parent = getParent();
		if (!parent) return;
		t2k::Transform wt = getWorldTransform();
		transform_.position_ = wt.position_;
		transform_.rotation_ = wt.rotation_;
		transform_.scale_ = wt.scale_;
		if (getPrev()) {
			prev_.lock()->next_ = next_;
			if (getNext()) next_.lock()->prev_ = prev_;
		}
		else {
			parent->child_ = next_;
			if (getNext()) next_.lock()->prev_.reset();
		}
		parent_.reset();
	}

	void Mover::destroyWithChild() {
		Mover::SharedPtr child = getChild(0);
		while (child) {
			child->destroy();
			child = child->getNext();
		}
		destroy();
	}

}
