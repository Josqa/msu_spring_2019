#include <iostream>
#include <string>
#include <cstdint>
#include <utility>

using namespace std;

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(ostream &out)
    : out_(out){}
    template <class T>
    Error save(T &object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(forward<ArgsT>(args)...);
    }
    
private:
    ostream& out_;
    template <class T, class... ArgsT>
    Error process(T x, ArgsT... args)
    {
        save(x);
        out_ << Separator;
        return process(forward<ArgsT>(args)...);
    }
    template <class T>
    Error process(T x)
    {
        save(x);
        return Error::NoError;
    }
    void save(bool x)
    {
        out_ << (x ? "true" : "false");
    }
    void save(uint64_t x)
    {
        out_ << x;
    }
};

class Deserializer
{
public:
    explicit Deserializer(istream &in)
    : in_(in){}
    template <class T>
    Error load(T &object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(forward<ArgsT>(args)...);
    }
private:
    istream& in_;
    template <class T, class... ArgsT>
    Error process(T &x, ArgsT&&... args)
    {
        if(!load(x))
            return Error::CorruptedArchive;
        return process(forward<ArgsT>(args)...);
    }
    template <class T>
    Error process(T &x)
    {
        if(!load(x))
            return Error::CorruptedArchive;
        return Error::NoError;
    }
    bool load(bool &x)
    {
        string buf;
        in_ >> buf;
        if(buf == "true")
        {
            x = true;
            return true;
        }
        else if(buf == "false")
        {
            x = false;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool load(uint64_t &x)
    {
        string buf;
        in_ >> buf;
        try
        {
            if(buf[0] == '-') return false;
            x = stoull(buf);
        }catch(exception &e)
        {
            return false;
        }
        return true;
    }
};
