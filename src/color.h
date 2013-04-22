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


        void brighten()
        {
            prev_r=r;
            prev_g=g;
            prev_b=b;
            prev_a=a;
            a+=0.1;
        }

        void brighten(float alpha)
        {
            prev_r=r;
            prev_g=g;
            prev_b=b;
            prev_a=a;
            a+=alpha;
        }

        void darken()
        {
            prev_r=r;
            prev_g=g;
            prev_b=b;
            prev_a=a;
            a-=0.1;
        }

        void darken(float alpha)
        {
            prev_r=r;
            prev_g=g;
            prev_b=b;
            prev_a=a;
            a-=alpha;
        }


        void set(float red, float green, float blue)
        {
            prev_r=r;
            prev_g=g;
            prev_b=b;
            prev_a=a;
            r=red;
            g=green;
            b=blue;

        }

        void set(float red, float green, float blue, float alpha)
        {
            prev_r=r;
            prev_g=g;
            prev_b=b;
            prev_a=a;
            r=red;
            g=green;
            b=blue;
            a=alpha;

        }

        void set(color c)
        {
            prev_r=r;
            prev_g=g;
            prev_b=b;
            prev_a=a;
            r=c.r;
            g=c.g;
            b=c.b;
        }

        void undo()
        {
            r=prev_r;
            g=prev_g;
            b=prev_b;
            a=prev_a;
        }

        color()
        {

        }

        color(float red, float green, float blue)
        {
            r=red;
            g=green;
            b=blue;
        }

        color(float red, float green, float blue, float alpha)
        {
            r=red;
            g=green;
            b=blue;
            a=alpha;
        }

    };//color with red, green, blue
const color RED(1.0,0.0,0.0,0.5);
const color YELLOW(1.0,1.0,0.0,1.0);
const color GREEN(0.0,1.0,0.0,0.5);
const color BLUE(0.0,0.0,1.0,0.0);
const color BLACK(0.0,0.0,0.0,0.0);
const color WHITE(1.0,1.0,1.0,0.0);
