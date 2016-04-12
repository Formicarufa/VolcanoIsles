#ifndef Button_H
#define Button_H
#include "GraphicsContainer.h"
#include <memory>
#include "Image.h"
#include "Rectangle.h"
#include "MouseMotionHandler.h"
#include "GameState.h"

namespace g
{
	///Click handler needs to be provided using the register_handler member function.
	class Button : public GraphicsContainer, public MouseMotionHandler
	{
	public:

		Button(int x, int y, std::string button_image_name, GameState* state)
			: GraphicsContainer(x, y), enabled_(true),state_(state)
		{
			button_image_ = std::make_unique<Image>(0, 0, button_image_name);
			mouse_over_rectangle_ = std::make_unique<Rectangle>(0, 0, 0, 0, colors::light_grey());
			add_child(mouse_over_rectangle_.get());
			add_child(button_image_.get());
			mouse_over_rectangle_->set_visible(false);
			state_->addMouseMotionHandler(button_image_.get(), this);
		}

		bool enabled() const
		{
			return enabled_;
		}

		void set_enabled(bool enabled)
		{
			enabled_ = enabled;
			if (enabled_ == false)
			{
				button_image_->set_alpha(100);
			}
			else
			{
				button_image_->set_alpha(255);
			}
		}
		void mouse_over() override
		{
			if (!enabled_) return;
			auto width = button_image_->width();
			auto height = button_image_->height();
			mouse_over_rectangle_->set_width(width);
			mouse_over_rectangle_->set_height(height);
			mouse_over_rectangle_->set_visible(true);

		}

		void mouse_out() override
		{
			mouse_over_rectangle_->set_visible(false);
		}


		void add_click_handler(MouseHandler* h) const
		{
			state_->addMouseClickHandler(button_image_.get(), h);
		}
		void remove_handler(MouseHandler* h) const
		{
			state_->removeMouseClickHandler(button_image_.get(), h);
		}
		~Button()
		{
			unregister_mouse_over();
		}
	private:
		std::unique_ptr<Image> button_image_;
		std::unique_ptr<Rectangle> mouse_over_rectangle_;
		bool enabled_;
		GameState* state_;


		void unregister_mouse_over()
		{
			state_->removeMouseMotionHandler(button_image_.get(), this);
		}

	};

}

#endif // Button_H


