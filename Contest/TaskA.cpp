
class IOWrapper{
public:
    IOWrapper() = delete;

    IOWrapper(IOWrapper const& other) = delete;

    IOWrapper(IOWrapper && other)
    {
        data = other.data;
        other.data = kNullHandle;
    }

    IOWrapper(handle_t const& handle)
    {
        data = handle;
    }

    IOWrapper& operator=(IOWrapper const& other) = delete;

    IOWrapper& operator=(IOWrapper && other)
    {
        data = other.data;
        other.data = kNullHandle;
    }

    IOWrapper & operator=(handle_t const& handle)
    {
        data = handle;
    }

    void Write(const std::string& content)
    {
        raw_write(data, content);
    }

    ~IOWrapper()
    {
        if(data != kNullHandle)
            raw_close(data);
    }

private:
    handle_t data;
};
