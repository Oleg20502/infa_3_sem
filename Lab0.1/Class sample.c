

int main()
{
    class Segment{
    private:
            int begin, end;
    public:
        //Segment(): begin(0), end(0){}
        Segment(): Segment(0){}
        //Segment(int point): begin(point), end(point){}
        Segment(int point): Segment(point, point){}
        Segment(int begin, int end): begin(begin), end(end){}
        int set_length()
        {
            return end-begin;
        }
    };
    return 0;
}
