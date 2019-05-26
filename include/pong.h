#ifndef MICKEY_PONG_H
#define MICKEY_PONG_H

#include <graphics.h>

namespace mickey{
    namespace pong{
        struct thing{
            int x, y;

            virtual void draw()=0;

            void erase(){
                setfillstyle(SOLID_FILL, BLACK);
                draw();
                setfillstyle(SOLID_FILL, WHITE);
            }

            void move(int d_x, int d_y){
                erase();
                set_loc(x + d_x, y + d_y);
                draw();
            }

            void set_loc(int _x, int _y){
                x = _x;
                y = _y;
            }
        };

        struct ball: thing{
            int r;

            ball(int _x, int _y): r(5){
                x = _x;
                y = _y;
            }

            void draw() override{
                fillellipse(x, y, r, r);
            }
        };

        enum struct wc_pad{
            right, left
        };

        enum struct mv_dir{
            up, down
        };

        struct paddle: thing{
            int w, h;

            paddle(int _x, int _y): w(10), h(30){
                x = _x;
                y = _y;
            }

            void draw() override{
                bar(x, y, w+x, h+y);
            }
        };

        struct pong{
            int x, y, w, h;
            paddle* l_pad;
            paddle* r_pad;
            ball* bal;

            pong(int _x, int _y, int _w, int _h):
            x(_x), y(_y), w(_w), h(_h){
                rectangle(x, y, x+w, y+h);
                l_pad = new paddle(x+20, y+h/2);
                r_pad = new paddle(x+w-30, y+h/2);
                bal = new ball(x+w/2, y+h/2);

                init_draw();
            }
            void init_draw(){
                l_pad->draw();
                r_pad->draw();
                bal->draw();
            }

            void move(wc_pad wc, mv_dir dir){
                paddle* temp = (wc == wc_pad::left) ? l_pad : r_pad;

                switch(dir){
                case mv_dir::up:
                    if(temp->y > y+5)
                        temp->move(0, -5);
                    break;
                case mv_dir::down:
                    if(temp->y+temp->h < y+h-5)
                        temp->move(0, 5);
                    break;
                }
            }
        };
    }
}
#endif // MICKEY_PONG_H