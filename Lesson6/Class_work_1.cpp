
class Handler{
public:
    virtual void* data()=0;

    virtual void const* data() const = 0;

};

template<typename T>
class UniHandler: public Handler{
public:
    void* data() override {return static_cast<void*>(&value); }

    //void const* data() override const {return static_cast<void const*>(&value); }

private:
    T value;
};

int main()
{
    return 0;
}
