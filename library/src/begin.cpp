#include <begin.h>

rtnmsp::Begin* rtnmsp::Begin::singleinstance = nullptr;

rtnmsp::Begin* rtnmsp::Begin::createBegin()
{
    if ( singleinstance == nullptr )
    {
        singleinstance = new Begin();
    }
    return singleinstance;
}

void rtnmsp::Begin::findObjectsFile(string imagepath, string backgroundpath, int x, int y, int width, int height)
{
    panmsp::ACommand *starter = new panmsp::SingleImage(imagepath, backgroundpath, x, y, width, height);
    starter -> execute();
    delete starter;
}

void rtnmsp::Begin::findObjectsFolder(string folderpath, string backgroundpath, int x, int y, int width, int height)
{
    panmsp::ACommand *starter = new panmsp::MultipleImages(folderpath, backgroundpath, x, y, width, height);
    starter->execute();
    delete starter;
}

void rtnmsp::Begin::findObjectsCamera(string videopath, string backgroundpath, int framerate)
{

}