#ifndef MICK_GRAPH
#define MICK_GRAPH

#include <string>
#include <tuple>
#include "graphics.h"

namespace mickey{
	class graph{
	public:
		graph(int w, int h, std::string title="mick", int x=50, int y=10):
		width(w), height(h), is_open(true){
			half_x = w/2;
			half_y = h/2; 
			initwindow(w, h, title.c_str(), x, y);
		}

		graph() : gd(DETECT), is_open(true){
			initgraph(&gd, &gm, NULL);
			this->width = getmaxx();
			this->height = getmaxy();
			this->half_x = this->width/2;
			this->half_y = this->height/2;
		}

		void close(){
			if(is_open){
				closegraph();
				is_open = false;
			}
		}

		std::tuple<int, int> get_dim(){	return std::make_tuple(this->width, this->height);	}
		inline int get_dim_width(){	return this->width;	}
		inline int get_dim_height(){	return this->height;	}
		
		void clear(){
			cleardevice();
		}

		~graph(){	this->close();	}

	private:
		int gd, gm, width, height, half_x, half_y;
		bool is_open;

	};
}

#endif