#ifndef COLOR_H
#define COLOR_H

//A color has red, green, blue, and alpha values.
class color
    {
        private:
        float prev_r;//previous red value
        float prev_g;//previous green value
        float prev_b;//previous blue value
        float prev_a;//previous alpha value
        public:
        float r;//red value
        float g;//green value
        float b;//blue value
        float a;//alpha value
        void brighten();//increment the alpha of the color
        void brighten(float alpha);//increase the alpha by given value
        void darken();//decrement the alpha of the color
        void darken(float alpha);//decrease the alpha by given value
        void set(float red, float green, float blue);//set the RGB values
        void set(float red, float green, float blue, float alpha);//set the RGBA values
        void set(color c);//set the color to match the given color
        void undo();//changes the color back to its previous setting
        color();
        color(float red, float green, float blue);
        color(float red, float green, float blue, float alpha);

    };//color with red, green, blue
//below are a bunch of color presets
const color RED(1.0,0.0,0.0);
const color YELLOW(1.0,1.0,0.0);
const color GREEN(0.0,1.0,0.0);
const color BLUE(0.0,0.0,1.0);
const color BLACK(0.0,0.0,0.0);
const color WHITE(1.0,1.0,1.0);
#endif // COLOR_H
