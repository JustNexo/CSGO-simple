#include "clantag.hpp" 
#include <string>

std::string tag = "nexoh00k "; 

void Clantag::ChangeClanTag()
{
    if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
        return;

    if (!g_Configurations.misc_clantag)
        return;

    static size_t lastTime = 0;

    if (GetTickCount64() > lastTime)
    {
        tag += tag.at(0);
        tag.erase(0, 1);

        Utils::SetClantag(tag.c_str());

        lastTime = GetTickCount64() + 650;
    }
}