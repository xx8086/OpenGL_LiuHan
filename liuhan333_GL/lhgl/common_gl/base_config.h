#ifndef BASE_CONFIG_H
#define	BASE_CONFIG_H

#define MSG_BUFFER_LEN (1024)
#define MAX_FILENAME_LEN (512)

#define FALSE_RT(a,t) if(!a){return t;}

#define DELETE_PTR(p) \
if(nullptr != p) \
{\
    delete p;\
    p = nullptr;\
}

#define DELETE_ARRAY_PTR(p) \
if(nullptr != p) \
{\
    delete [] p;\
    p = nullptr;\
}

#endif