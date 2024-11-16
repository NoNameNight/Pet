#include "ResourcesManager.h"

#include <QPainter>
#include <QImage>

struct ImageResInfo
{
    std::string id;
    QString path;
};

struct AtlasResInfo
{
    std::string id;
    QString path;
    int num_frame = 0;
};

bool checkImageValid(IMAGE* image)
{
    return !image->isNull();
}

ResourcesManager *ResourcesManager::instance()
{
    static ResourcesManager manager;
    return &manager;
}

void ResourcesManager::load()
{
    static const std::vector<ImageResInfo> image_info_list ={
        {"pic", R"(resources\pic.png)" }
    };

    static const std::vector<AtlasResInfo> atlas_info_list = {
        {"skadi_start_right", R"(resources\skadi\start\char_1012_skadi2_Start_out%04d.png)", 22},
        {"skadi_skill_2_begin_right", R"(resources\skadi\skill_2_begin\char_1012_skadi2_Skill_2_Begin_out%04d.png)", 82},
        {"skadi_skill_2_loop_right", R"(resources\skadi\skill_2_loop\char_1012_skadi2_Skill_2_Loop_out%04d.png)", 69},
        {"skadi_fall_right", R"(resources\skadi\fall\char_1012_skadi2_Fall_out%04d.png)", 43},
        {"skadi_move_right", R"(resources\skadi\move\build_char_1012_skadi2_Move_out%04d.png)", 36},
        {"skadi_idle_right", R"(resources\skadi\idle\char_1012_skadi2_Idle_out%04d.png)", 178},
        {"skadi_relax_right", R"(resources\skadi\relax\build_char_1012_skadi2_Relax_out%04d.png)", 98},
        {"skadi_interact_right", R"(resources\skadi\interact\build_char_1012_skadi2_Interact_out%04d.png)", 50},
        {"skadi_sit_right", R"(resources\skadi\sit\build_char_1012_skadi2_Sit_out%04d.png)", 110},
        {"skadi_sleep_right", R"(resources\skadi\sleep\build_char_1012_skadi2_Sleep_out%04d.png)", 56}
    };
    // static const std::vector<AtlasResInfo> atlas_info_list = {
    //     {"skadi_start_right", R"(:/start/resources/skadi/start/char_1012_skadi2_Start_out%04d.png)", 22},
    //     {"skadi_skill_2_begin_right", R"(:/skill_2_begin/resources/skadi/skill_2_begin/char_1012_skadi2_Skill_2_Begin_out%04d.png)", 82},
    //     {"skadi_skill_2_loop_right", R"(:/skill_2_loop/resources/skadi/skill_2_loop/char_1012_skadi2_Skill_2_Loop_out%04d.png)", 69},
    //     {"skadi_fall_right", R"(:/fall/resources/skadi/fall/char_1012_skadi2_Fall_out%04d.png)", 43},
    //     {"skadi_move_right", R"(:/move/resources/skadi/move/build_char_1012_skadi2_Move_out%04d.png)", 36},
    //     {"skadi_idle_right", R"(:/idle/resources/skadi/idle/char_1012_skadi2_Idle_out%04d.png)", 178},
    //     {"skadi_relax_right", R"(:/relax/resources/skadi/relax/build_char_1012_skadi2_Relax_out%04d.png)", 98},
    //     {"skadi_interact_right", R"(:/interact/resources/skadi/interact/build_char_1012_skadi2_Interact_out%04d.png)", 50},
    //     {"skadi_sit_right", R"(:/sit/resources/skadi/sit/build_char_1012_skadi2_Sit_out%04d.png)", 110},
    //     {"skadi_sleep_right", R"(:/sleep/resources/skadi/sleep/build_char_1012_skadi2_Sleep_out%04d.png)", 56}
    // };


    for (const ImageResInfo& info : image_info_list)
    {
        IMAGE* image = new IMAGE();
        image->load(info.path);
        if (!checkImageValid(image)) { throw info.path; }
        *image = image->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_image_pool[info.id] = image;
    }

    for (const AtlasResInfo& info : atlas_info_list)
    {
        Atlas* atlas = new Atlas();
        atlas->load(info.path, info.num_frame);
        for(int i = 0; i < atlas->getSize(); ++i)
        {
            IMAGE* image = atlas->getImage(i);
            if (!checkImageValid(image)) { throw info.path; }
            *image = image->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        m_atlas_pool[info.id] = atlas;
    }

    flipAtlas("skadi_start_right", "skadi_start_left");
    flipAtlas("skadi_skill_2_begin_right", "skadi_skill_2_begin_left");
    flipAtlas("skadi_skill_2_loop_right", "skadi_skill_2_loop_left");
    flipAtlas("skadi_fall_right", "skadi_fall_left");
    flipAtlas("skadi_move_right", "skadi_move_left");
    flipAtlas("skadi_idle_right", "skadi_idle_left");
    flipAtlas("skadi_relax_right", "skadi_relax_left");
    flipAtlas("skadi_interact_right", "skadi_interact_left");
    flipAtlas("skadi_sit_right", "skadi_sit_left");
    flipAtlas("skadi_sleep_right", "skadi_sleep_left");
}

Atlas *ResourcesManager::findAtlas(const std::string &id) const
{
    const auto& it = m_atlas_pool.find(id);
    if (it == m_atlas_pool.end())
    {
        return nullptr;
    }

    return it->second;
}

IMAGE *ResourcesManager::findImage(const std::string &id) const
{
    const auto& it = m_image_pool.find(id);
    if (it == m_image_pool.end())
    {
        return nullptr;
    }

    return it->second;
}

ResourcesManager::ResourcesManager() {}

ResourcesManager::~ResourcesManager() {}

void ResourcesManager::flipImage(IMAGE *src_image, IMAGE *dst_image, int num_h)
{
    int w = src_image->width();
    int h = src_image->height();
    int w_frame = w / num_h;
    *dst_image = IMAGE(w, h);
    // dst_image->scaled(src_image->size(), Qt::IgnoreAspectRatio);
    dst_image->fill(Qt::transparent); // 填充透明背景
    QImage tmp_image = src_image->toImage();
    QPainter painter(dst_image);

    for (int i = 0; i < num_h; ++i)
    {
        int x_left = i * w_frame;
        painter.drawImage(x_left, 0, tmp_image.copy(x_left, 0, w_frame, h).mirrored(true, false));
        //painter.drawPixmap(x_left, 0, (src_image->copy(x_left, 0, w, h)).transformed(QTransform().)));
    }
}

void ResourcesManager::flipImage(const std::string src_id, const std::string dst_id, int num_h)
{
    IMAGE* src_image = m_image_pool[src_id];
    IMAGE* dst_image = new IMAGE();

    flipImage(src_image, dst_image, num_h);

    m_image_pool[dst_id] = dst_image;
}

void ResourcesManager::flipAtlas(const std::string src_id, const std::string dst_id)
{
    Atlas* src_atlas = m_atlas_pool[src_id];
    Atlas* dst_atlas = new Atlas();
    for (int i = 0; i < src_atlas->getSize(); ++i)
    {
        IMAGE image_flipped;
        flipImage(src_atlas->getImage(i), &image_flipped);
        dst_atlas->addImage(image_flipped);
    }
    m_atlas_pool[dst_id] = dst_atlas;
}
