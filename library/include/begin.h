#ifndef _begin_h_
#define _begin_h_

#include <input.h>
#include <exception>
namespace rtnmsp
{
    class Begin
    {
        private:
        static Begin* singleinstance;

        protected:
        Begin() = default;

        public:
        static Begin* createBegin();
        void findObjectsFile(string, string);
        void findObjectsFolder(string, string);
        void findObjectsCamera(string, string, int);
    };
}


#endif
