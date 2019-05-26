#ifndef MICKEY_GAME_H
#define MICKEY_GAME_H

#include <iostream>

#include "pong.h"
#include "graph.h"
#include <Windows.h>

namespace mickey{
	
	class game{
		constexpr static int WIN_WIDTH	= 700;
		constexpr static int WIN_HEIGHT	= WIN_WIDTH / 1.618;

		constexpr static int PONG_WIN_WIDTH		= WIN_WIDTH - 50;
		constexpr static int PONG_WIN_HEIGHT	= WIN_HEIGHT - 50;

		

	public:
		game(){
			grp = new graph(WIN_WIDTH, WIN_HEIGHT, "Pong MANN", 100, 10);
			pong = new pong::pong(
				(WIN_WIDTH - PONG_WIN_WIDTH) / 2,
				(WIN_HEIGHT - PONG_WIN_HEIGHT) / 2,
				PONG_WIN_WIDTH,
				PONG_WIN_HEIGHT
			);
		}

		void main_loop(){
			while(true){
				if(GetAsyncKeyState(VK_UP)){
					pong->move(pong::wc_pad::right, pong::mv_dir::up);
					std::cout << "UP for right\n";
				}else if(GetAsyncKeyState(VK_DOWN)){
					pong->move(pong::wc_pad::right, pong::mv_dir::down);
					std::cout << "DOWN for right\n";
				}
				
				if(GetAsyncKeyState(VK_SHIFT)){
					pong->move(pong::wc_pad::left, pong::mv_dir::up);
					std::cout << "UP for left\n";
				}else if(GetAsyncKeyState(VK_CONTROL)){
					pong->move(pong::wc_pad::left, pong::mv_dir::down);
					std::cout << "DOWN for left\n";
				}

				if(GetAsyncKeyState(VK_ESCAPE)){
					std::cout << "exit\n";
					break;
				}
				Sleep(30);
			}
		}

		~game(){
			if(grp)	delete grp;
		}

	private:
		graph* grp = nullptr;
		pong::pong* pong = nullptr;
	};
}


#endif // MICKEY_GAME_H
