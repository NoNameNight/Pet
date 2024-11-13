#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include "Atlas.h"

class ResourcesManager
{
public:
    static ResourcesManager* instance();

    void load();

    Atlas* findAtlas(const std::string& id) const;
    IMAGE* findImage(const std::string& id) const;
private:
    //static ResourcesManager* manager;
    std::unordered_map<std::string, Atlas*> m_atlas_pool;
    std::unordered_map<std::string, IMAGE*> m_image_pool;
private:
    ResourcesManager();
    ~ResourcesManager();
    void flipImage(IMAGE* src_image, IMAGE* dst_image, int num_h = 1);
    void flipImage(const std::string src_id, const std::string dst_id, int num_h = 1);
    void flipAtlas(const std::string src_id, const std::string dst_id);
};

#endif // RESOURCESMANAGER_H
