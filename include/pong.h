#ifndef MICKEY_PONG_H
#define MICKEY_PONG_H

#include <graphics.h>

namespace mickey{
    namespace pong{
        struct bound{
            int l, t, r, b;
        };

        struct thing{
            int x, y;
            bound rect{0 ,0, 0, 0}; 

            virtual void draw()=0;
            virtual void norm_loc()=0;  // Normalize rectangle according to location given

            void erase(){
                setfillstyle(SOLID_FILL, BLACK);
                draw();
                // rectangle(rect.l, rect.t, rect.r, rect.b);
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
                norm_loc();
            }

            inline bool check_coll(thing* tng){
                // check if left with the other
                if(this->rect.r >= tng->rect.l && this->rect.r <= tng->rect.r){
                    if(this->rect.t >= tng->rect.t && this->rect.t <= tng->rect.b)
                        return true;
                    return false;
                }
                if(this->rect.l <= tng->rect.r && this->rect.l >= tng->rect.l){
                    if(this->rect.t >= tng->rect.t && this->rect.t <= tng->rect.b)
                        return true;
                    return false;
                }
                // printf("Right pad{%d %d %d %d}\t", this->rect.l, this->rect.t, this->rect.r, this->rect.b);
                // printf("Right tng{%d %d %d %d}\n", tng->rect.l, tng->rect.t, tng->rect.r, tng->rect.b);
                return false;
            }
            ~thing(){};
        };

        struct ball: thing{
            int r;
            float sx{5.0f}, sy{5.0f};

            ball(int _x, int _y): r(5){
                set_loc(_x, _y);
            }

            void set_speed(float _x, float _y){
                sx = _x;
                sy = _y;
            }

            void advance(){
                move(sx, sy);
            }

            void draw() override{
                fillellipse(x, y, r, r);
            }

            void norm_loc() override{
                rect = {x-r, y-r, x+r, y+r};
            }
        };

        enum struct wc_pad{ right, left };  // which paddle
        enum struct mv_dir{ up, down    };  // paddle move direction

        struct paddle: thing{
            int w, h;

            paddle(int _x, int _y): w(10), h(30){
                set_loc(_x, _y);
            }

            void draw() override{
                bar(x, y, w+x, h+y);
            }

            void norm_loc() override{
                rect = {x, y, x+w, y+h};
            }
        };

        struct pong{
            int x, y, w, h;
            paddle* l_pad;
            paddle* r_pad;
            ball* bal;
            bool stop_play = false;

            pong(int _x, int _y, int _w, int _h):
            x(_x), y(_y), w(_w), h(_h){
                rectangle(x, y, x+w, y+h);
    			setcolor(BLACK);
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
                    if(temp->rect.t > y+5)
                        temp->move(0, -5);
                    break;
                case mv_dir::down:
                    if(temp->rect.b < y+h-5)
                        temp->move(0, 5);
                    break;
                }
            }
            void move_ball(){
                ball* temp = bal;
                if(temp->rect.t <= y+5 || temp->rect.b >= y+h-5)
                    temp->set_speed(bal->sx, -bal->sy);
                if( temp->rect.r <= x+15 ||
                    temp->rect.l >= x+w-15)
                    stop_play = true;

                if( bal->check_coll(l_pad) ||
                    bal->check_coll(r_pad))
                    temp->set_speed(-bal->sx, bal->sy);
                bal->advance();
            }
            // ~pong(){
            //     if(l_pad)   delete l_pad;
            //     if(r_pad)   delete r_pad;
            //     if(bal)     delete bal;
            // }
        };
    }
}
#endif // MICKEY_PONG_H