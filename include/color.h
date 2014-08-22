#ifndef COLOR_H
#define COLOR_H
class color
    {
        private:
        float prev_r;
        float prev_g;
        float prev_b;
        float prev_a;
        public:
        float r;
        float g;
        float b;
        float a;
        void brighten();
        void brighten(float alpha);
        void darken();
        void darken(float alpha);
        void set(float red, float green, float blue);
        void set(float red, float green, float blue, float alpha);
        void set(color c);
        void undo();
        color();
        color(float red, float green, float blue);
        color(float red, float green, float blue, float alpha);

    };//color with red, green, blue
const color RED(1.0,0.0,0.0,0.5);
const color YELLOW(1.0,1.0,0.0,1.0);
const color GREEN(0.0,1.0,0.0,0.5);
const color BLUE(0.0,0.0,1.0,0.0);
const color BLACK(0.0,0.0,0.0,0.0);
const color WHITE(1.0,1.0,1.0,0.0);
#endif // COLOR_H

