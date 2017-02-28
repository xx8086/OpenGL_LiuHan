#ifndef ENGINE_SINGLETON_H
#define ENGINE_SINGLETON_H


template <class T>
class Singleton
{
public:
    inline static T& get_instance()
    {
        if (!_s_instance_prt)
        {
            _s_instance_prt = new T;
        }
        
        return *_s_instance_prt;
    }

    inline static void destroy_instance()
    {
        if (_s_instance_prt)
        {
            delete _s_instance_prt;
        }
        
        _s_instance_prt = 0;
    }

protected:
    Singleton() {}
    ~Singleton() {}

private:
    static T* _s_instance_prt;	// Instance de la classe

    Singleton(Singleton&);
    void operator =(Singleton&);
};

template <class T> T* Singleton<T>::_s_instance_prt = 0;


#define SINGLE_LH(class_name) \
static class_name * get_lhinstance()\
{\
    return &get_instance();\
}\
\
private:\
    class CGarbo\
    {\
    public:\
        ~CGarbo()\
        {\
            destroy_instance();\
        }\
    };\
\
    static CGarbo Garbo;\

#endif
