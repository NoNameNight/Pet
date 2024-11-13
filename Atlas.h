#ifndef ATLAS_H
#define ATLAS_H

#include "Util.h"
// #include <graphics.h>

class Atlas
{
public:
    Atlas() = default;
    ~Atlas() = default;

    void load(const QString& path_template, int num)
    {
        m_img_list.clear();
        m_img_list.resize(num);

        char file_path[256] = { 0 };
        for (int i = 0; i < num; ++i)
        {
            memset(file_path, 0, 256);
            sprintf_s(file_path, path_template.toStdString().c_str(), i + 1);
            // loadimage(&m_img_list[i], path_file);
            m_img_list[i].load(file_path);
        }
    }

    void clear()
    {
        m_img_list.clear();
    }

    int getSize() const
    {
        return static_cast<int>(m_img_list.size());
    }

    IMAGE* getImage(int idx)
    {
        if (idx < 0 || idx >= m_img_list.size())
        {
            return nullptr;
        }

        return &m_img_list[idx];
    }

    void addImage(const IMAGE& img)
    {
        m_img_list.emplace_back(img);
    }
private:
    std::vector<IMAGE> m_img_list;
};

#endif // ATLAS_H
