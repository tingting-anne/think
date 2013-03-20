#ifndef _THINK_VERSION_H_
#define _THINK_VERSION_H_

#ifndef VERSION
#define VERSION "1.00.0"
#endif

namespace THINK
{
  

    static const char _version[] = "LibThink, Version:  " VERSION "  , Build Time: " __DATE__ " " __TIME__;


    class Version
    {
      public:
        Version();
        static const char* getVersion();
    };

}
#endif //_THINK_VERSION_H_ 
