#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>

#include <vector>
#include <QString>
#include <QPixmap>
#include <chrono>

using IMAGE = QPixmap;

class Config
{
public:
    static Config* instance()
    {
        static Config config;
        return &config;
    }

    float character_foot_bottom = 55.f;
    float border_padding = 3.f; // 左右边界收缩

    float row_interval = 0.05f; // 原始fps
    float real_interval = 0.03f; // 应用fps

    float interact_durtion = 2.400000f;
    float relax_durtion = 4.840000f;
    float move_durtion = 1.720000f;
    float sit_durtion = 5.400000f;
    float sleep_durtion = 2.720000f;
    float fall_durtion = 2.040000f;
    float idle_durtion = 8.800000f;
    float skill_2_begin_durtion = 4.000000f;
    float skill_2_loop_durtion = 3.360000f;
    float skill_3_begin_durtion = 4.000000f;
    float skill_3_loop_durtion = 8.800000f;
    float start_durtion = 1.040000f;
private:
    Config() = default;
    ~Config() = default;
};

struct Rect
{
    int x, y;
    int w, h;
};

inline int range_random(int min_num, int max_num)
{
    srand((unsigned int)time(nullptr));
    return min_num + rand() % (max_num - min_num + 1);
}

inline float range_random(float min_num, int max_num)
{
    int range_int_max = 10000;
    int range_int = range_random(0, range_int_max);
    return (max_num - min_num + 1) * range_int / range_int_max + min_num;
}

#endif // UTIL_H
