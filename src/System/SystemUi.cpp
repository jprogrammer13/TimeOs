#include <Arduino.h>
#include <System/SystemUi.h>

SystemUi::SystemUi(){};

void SystemUi::registerApplications(std::map<String, Ui *> *_application)
{
    this->application = _application;
}
void SystemUi::registerWatchFaces(std::map<String, Ui *> *_watchFaces)
{
    this->watchFaces = _watchFaces;
}

void SystemUi::setApp(String name)
{
    this->page = (*application)[name];
}
void SystemUi::setWatchface(String name)
{
    this->page = (*watchFaces)[name];
}

void SystemUi::pageRender()
{
    this->page->draw();
}